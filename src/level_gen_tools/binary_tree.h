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

#pragma once
#include <random>
#include "level_gen_defines.h"

struct node {
    int x1;
    int x2;
    int y1;
    int y2;
    node *left;
    node *right;
};

class binary_tree {
public:
    /**
     * Default constructor
     */
    binary_tree(int y2, int x2);

    /**
     * Destructor
     */
    ~binary_tree();
    int mapdata [LEVEL_HEIGHT] [LEVEL_WIDTH];
    
private:
    void add_node(int y1, int y2, int x1, int x2, node *leaf);
    void delete_tree();
    void delete_node(node *leaf);
    void node_build_loop(node *leaf);
    node *root;
};
