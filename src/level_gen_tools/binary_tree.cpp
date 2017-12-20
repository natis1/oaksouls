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
    int yrange = leaf->y2 - leaf->y1;
    int xrange = leaf->x2 - leaf->x1;
    if (xrange * yrange >= MAX_ROOM_VOLUME) {
        
        if (xrange >= yrange) {
            std::uniform_int_distribution<int> uni( (int)(xrange * (1-MAX_SPLIT_AMT)) + leaf->x1, (xrange * MAX_SPLIT_AMT) + leaf->x1 - 1);
            int newval = uni(rn);
            
            // Starts at the old x1 and goes until hitting the new value
            add_node(leaf->y1, leaf->y2, leaf->x1, newval, leaf->left);
            add_node(leaf->y1, leaf->y2, newval + 1, leaf->x2, leaf->right);
            node_build_loop(leaf->left);
            node_build_loop(leaf->right);
        } else {
            std::uniform_int_distribution<int> uni( (int)(yrange * (1-MAX_SPLIT_AMT)) + leaf->y1, (yrange * MAX_SPLIT_AMT) + leaf->y1 - 1);
            int newval = uni(rn);
            
            // Starts at the old x1 and goes until hitting the new value
            add_node(leaf->y1, newval, leaf->x1, leaf->x2, leaf->left);
            add_node(newval + 1, leaf->y2, leaf->x1, leaf->x2, leaf->right);
            node_build_loop(leaf->left);
            node_build_loop(leaf->right);
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


