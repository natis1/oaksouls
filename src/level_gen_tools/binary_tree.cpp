/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2017  <copyright holder> <email>
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

#define MAX_ROOM_VOLUME 100
#define MAX_SPLIT_AMT 0.8
#define WALL_THICKNESS 1

binary_tree::binary_tree(int y2, int x2)
{
    root=NULL;
    add_node(0, y2, 0, x2, root);    
    
}

binary_tree::~binary_tree()
{
    delete_tree();
}

void binary_tree::node_build_loop(node *leaf)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    
    int yrange = leaf->y2 - leaf->y1;
    int xrange = leaf->x2 - leaf->x1;
    if (xrange * yrange >= MAX_ROOM_VOLUME) {
        
        // Splits vertically
        if (xrange >= yrange) {
            std::uniform_int_distribution<int> uni( (int)(xrange * (1-MAX_SPLIT_AMT)) + leaf->x1, (xrange * MAX_SPLIT_AMT) + leaf->x1 - 1);
            int newval = uni(rng);
            
            // Starts at the old x1 and goes until hitting the new value
            add_node(leaf->y1, leaf->y2, leaf->x1, newval, leaf->left);
            add_node(leaf->y1, leaf->y2, newval + 1, leaf->x2, leaf->right);
            node_build_loop(leaf->left);
            node_build_loop(leaf->right);
            
            //connect leaves. Choose a random y value
            std::uniform_int_distribution<int> conpts(leaf->y1, leaf->y2);
            bool goodpt1;
            bool goodpt2;
            int point;
            do {
                goodpt1 = false;
                goodpt2 = false;
                point = conpts(rng);
                for (int i = leaf->left->x1; i < leaf->left->x2; i++){
                    if (mapdata [point] [i] == 1) {
                        goodpt1 = true;
                        break;
                    }
                }
                for (int i = leaf->right->x1; i < leaf->right->x2; i++){
                    if (mapdata [point] [i] == 1) {
                        goodpt2 = true;
                        break;
                    }
                }
            } while (!goodpt1 && !goodpt2);
            
            for (int i = leaf->x1 + WALL_THICKNESS; i < leaf->x2 - WALL_THICKNESS; i++) {
                mapdata [point] [i] = 1;
            }
            
        } else {
            std::uniform_int_distribution<int> uni( (int)(yrange * (1-MAX_SPLIT_AMT)) + leaf->y1, (yrange * MAX_SPLIT_AMT) + leaf->y1 - 1);
            int newval = uni(rng);
            
            // Starts at the old x1 and goes until hitting the new value
            add_node(leaf->y1, newval, leaf->x1, leaf->x2, leaf->left);
            add_node(newval + 1, leaf->y2, leaf->x1, leaf->x2, leaf->right);
            node_build_loop(leaf->left);
            node_build_loop(leaf->right);
            
            //connect leaves. Choose a random x value
            std::uniform_int_distribution<int> conpts(leaf->x1, leaf->x2);
            bool goodpt1;
            bool goodpt2;
            int point;
            do {
                point = conpts(rng);
                goodpt1 = false;
                goodpt2 = false;
                for (int i = leaf->left->y1; i < leaf->left->y2; i++){
                    if (mapdata [i] [point] == 1) {
                        goodpt1 = true;
                        break;
                    }
                }
                for (int i = leaf->right->y1; i < leaf->right->y2; i++){
                    if (mapdata [i] [point] == 1) {
                        goodpt2 = true;
                        break;
                    }
                }
            } while (!goodpt1 && !goodpt2);
            for (int i = leaf->y1 + WALL_THICKNESS; i < leaf->y2 - WALL_THICKNESS; i++) {
                mapdata [i] [point] = 1;
            }
            
            
        }        
        
        
        
    } else {
        // Map code
        
        // Tunnel should never be true but if it is then
        bool tunnel = (((leaf->x1 + WALL_THICKNESS * 2 ) >= leaf->x2) || ((leaf->y1 + WALL_THICKNESS * 2) >= leaf->y2));
        for (int i = leaf->x1;  i < leaf->x2; i++) {
            for (int j = leaf->y1; j < leaf->y2; j++) {
                if (tunnel || ((leaf->x1 + WALL_THICKNESS <= i) && (leaf->x2 - WALL_THICKNESS >= i) && (leaf->y1 + WALL_THICKNESS <= j) && (leaf->y2 - WALL_THICKNESS >= j))) {
                    mapdata[j] [i] = 1;
                    
                } else {
                    mapdata[j] [i] = 0;
                }
            }
        }
        
        
        
        
    }
}


void binary_tree::add_node(int y1, int y2, int x1, int x2, node *leaf)
{
    leaf->x1 = x1;
    leaf->x2 = x2;
    leaf->y1 = y1;
    leaf->y2 = y2;
}

void binary_tree::delete_tree()
{
    delete_node(root);
    
}

void binary_tree::delete_node(node* leaf)
{
    if (leaf != NULL) {
        delete_node(leaf->left);
        delete_node(leaf->right);
        delete leaf;
    }
}


