/*
 * Oaksouls ~ A difficult roguelike about a	tree spirit.
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

#include "level_gen.h"
#include "stage2.h"
#include "stage3.h"

void level_gen::binarySpace() {
    binary_tree tr = binary_tree();
    level.mapdata = tr.mapdata;
    cleanup();
    stage2 s2 (&level.mapdata);
    stage3 s3 (&level);
    s3.placeObjectExternal(DOWNSTAIR, FLOOR);
    s3.placeObjectExternal(UPSTAIR, FLOOR);
    s3.placeObjectExternal(OAKALTER, FLOOR);
    s3.placeObjectExternal(OAKALTER, FLOOR);
    s3.placeObjectExternal(OAKALTER, FLOOR);
    s3.placeObjectExternal(ENEMYALTER, FLOOR);
    s3.placeObjectExternal(ENEMYALTER, FLOOR);
    s3.placeObjectExternal(ENEMYALTER, FLOOR);
    
}

void level_gen::cleanup()
{
    
    // make edges walls
    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        level.mapdata.at(i).at(0) = MAP_EDGE;
        level.mapdata.at(i).at(LEVEL_WIDTH - 1) = MAP_EDGE;
    }
    for (int j = 0; j < LEVEL_WIDTH; j++) {
        level.mapdata.at(0).at(j) = MAP_EDGE;
        level.mapdata.at(LEVEL_HEIGHT - 1).at(j) = MAP_EDGE;
    }
    
}
