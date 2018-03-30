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

#pragma once

#include <vector>
#include "level_gen_defines.h"

/**
 * @todo write docs
 */
class stage3
{
public:
    
    stage3(map *level);
    map *level;
    
    void addExit(int level);
    void addAlter(int piety);
    
    
    // For external object placing. DO NOT USE WITH SPECIAL OBJECTS OR THEY WON'T BE SET PROPERLY.
    void placeObjectExternal(int objID, int featureType);
    void placeObjectExternal(int objID);
    void placeObjectExternal(int objID, int y, int x);
   

    
private:
    
    struct point {
        int y;
        int x;
    };
    
    // Do not call place functions for special objects or they will never be allocated.
    
    // place an object, overriding whatever feature was there before- might be useful for water or something
    point placeObject(int objID);
    
    // place an object on a feature of a certain type.
    point placeObject(int objID, int featureType);
    
    // place an object on a preset location
    point placeObject(int objID, int y, int x);
    
    void isFloor(int y, int x);
    void concatPoints();
    int removePoint(int pointID, int y, int x);
    
    
    
    std::vector<stage3::point> floors;
    std::vector<stage3::point> walls;
};
