/*
 * Oaksouls ~ A difficult roguelike about a tree spirit.
 * Copyright (C) 2018  Eli Stone eli.stonium+oak@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "binary_tree.h"
#include <stddef.h>
#include <random>
#include <curses.h>

binary_tree::binary_tree()
{
    mapdata.reserve(LEVEL_HEIGHT);
    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        mapdata.push_back(std::vector<int> (LEVEL_WIDTH, 0));
    }
    root = nullptr;
    // In theory this stops impossible to access rooms from generating. Hopefully.
    // This is a really good idea to stop stage2 undefined behavior. Oh dear...
    root = add_node(1, LEVEL_HEIGHT - 1, 1, LEVEL_WIDTH - 1);
    node_build_loop(root);
    
}

void binary_tree::node_build_loop(node *leaf)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    
    int yrange = leaf->y2 - leaf->y1;
    int xrange = leaf->x2 - leaf->x1;
    if (xrange * yrange >= BINARY_TREE_MAX_ROOM_VOLUME) {
        
        // Splits vertically
        if (xrange >= yrange) {
            std::uniform_int_distribution<int> uni( (int)(xrange * (1-BINARY_TREE_MAX_SPLIT_AMT)) + leaf->x1, (xrange * BINARY_TREE_MAX_SPLIT_AMT) + leaf->x1 - 1);
            int newval = uni(rng);
            
            // Starts at the old x1 and goes until hitting the new value
            leaf->left = add_node(leaf->y1, leaf->y2, leaf->x1, newval);
            leaf->right = add_node(leaf->y1, leaf->y2, newval + 1, leaf->x2);
            node_build_loop(leaf->left);
            node_build_loop(leaf->right);
            //connect leaves. Choose a random y value
            std::uniform_int_distribution<int> conpts(leaf->y1, leaf->y2 - 1);
            int goodpt1;
            int goodpt2;
            int point;
            int tries = BINARY_TREE_ROOM_CONNECT_TRIES;
            do {
                goodpt1 = -1;
                goodpt2 = -1;
                point = conpts(rng);
                for (int i = leaf->left->x1; i < leaf->left->x2; i++){
                    if (mapdata.at(point).at(i) >= FLOOR) {
                        goodpt1 = i;
                        break;
                    }
                }
                for (int i = leaf->right->x1; i < leaf->right->x2; i++){
                    if (mapdata.at(point).at(i) >= FLOOR) {
                        goodpt2 = i;
                        break;
                    }
                }
                tries--;
            } while ((goodpt1 == -1 || goodpt2 == -1) && tries > 0 );
            
            if (tries > 0) {
                for (int i = goodpt1; i < goodpt2 + 1; i++) {
                    mapdata.at(point).at(i) = POSSIBLE_HALL;
                }
            } else {
                //std::cerr << "Unable to build connection" << std::endl;
            }
            
        } else {
            std::uniform_int_distribution<int> uni( (int)(yrange * (1-BINARY_TREE_MAX_SPLIT_AMT)) + leaf->y1, (yrange * BINARY_TREE_MAX_SPLIT_AMT) + leaf->y1 - 1);
            int newval = uni(rng);
            
            // Starts at the old x1 and goes until hitting the new value
            leaf->left = add_node(leaf->y1, newval, leaf->x1, leaf->x2);
            leaf->right = add_node(newval + 1, leaf->y2, leaf->x1, leaf->x2);
            node_build_loop(leaf->left);
            node_build_loop(leaf->right);
            //connect leaves. Choose a random x value

            std::uniform_int_distribution<int> conpts(leaf->x1, leaf->x2 - 1);
            int goodpt1;
            int goodpt2;
            int point;
            int tries = BINARY_TREE_ROOM_CONNECT_TRIES;
            do {
                point = conpts(rng);
                goodpt1 = -1;
                goodpt2 = -1;
                for (int i = leaf->left->y1; i < leaf->left->y2; i++){
                    if (mapdata.at(i).at(point) >= FLOOR) {
                        goodpt1 = i;
                        break;
                    }
                }
                for (int i = leaf->right->y1; i < leaf->right->y2; i++){
                    if (mapdata.at(i).at(point) >= FLOOR) {
                        goodpt2 = i;
                        break;
                    }
                }
                tries--;
            } while ((goodpt1 == -1 || goodpt2 == -1) && tries > 0 );
            
            if (tries > 0) {
                for (int i = goodpt1; i < goodpt2 + 1; i++) {
                    mapdata.at(i).at(point) = POSSIBLE_HALL;
                }
            } else {
                //std::cerr << "Unable to build connection" << std::endl;
            }
        }        
        
        
        
    } else {
        // Map code
        
        // Why not just segfault now and save us all some debugging time later?
        if (leaf->x1 > leaf->x2 || leaf->y1 > leaf->y2 || leaf->x2 > LEVEL_WIDTH || leaf->y2 > LEVEL_HEIGHT) {
            clear();
            curs_set(1);
            endwin();
            exit(11);
            
        }
        
        // Tunnel should almost never be true but if it is then
        std::uniform_int_distribution<int> thicknesses( BINARY_TREE_MIN_WALL_THICKNESS, BINARY_TREE_MAX_WALL_THICKNESS);
        int thickness = thicknesses(rng);
        bool tunnel = (((leaf->x1 + thickness * 2 ) >= leaf->x2) || ((leaf->y1 + thickness * 2) >= leaf->y2));
        for (int i = leaf->x1;  i < leaf->x2; i++) {
            for (int j = leaf->y1; j < leaf->y2; j++) {
                if (tunnel) {
                    mapdata.at(j).at(i) = POSSIBLE_HALL;
                }
                else if ((leaf->x1 + thickness <= i) && (leaf->x2 - thickness >= i) && (leaf->y1 + thickness <= j) && (leaf->y2 - thickness >= j)) {
                    mapdata.at(j).at(i) = FLOOR;
                }
            }
        }
        
        
        
        
    }
}


node* binary_tree::add_node(int y1, int y2, int x1, int x2)
{
    return new node{x1, x2, y1, y2, nullptr, nullptr};
}

void binary_tree::delete_tree()
{
    delete_node(root);
    
}

void binary_tree::delete_node(node* leaf)
{
    if (leaf->left != nullptr) {
        delete_node(leaf->left);
    }
    if (leaf->right != nullptr) {
        delete_node(leaf->right);
    }
    free(leaf);
}

int binary_tree::adjacentPoints(int y, int x) {
    int pts = 0;
    for (int i = (y - 1); i < (y + 2); i++) {
        for (int j = (x - 1); j < (x + 2); j++) {
            if ( inBounds(i, j) && (i != y && x != j) && mapdata.at(i).at(j) != 0) {
                pts++;
            }
        }
    }
    return pts;
}

bool binary_tree::inBounds(int y, int x) {
    return ( (y >= 0 && y < LEVEL_HEIGHT) && (x >= 0 && x < LEVEL_WIDTH));
}
