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
#include <random>



/**
 * @todo write docs
 */
class stage2
{
public:
    stage2(std::vector<std::vector<int>> *mapdata);
    std::vector<std::vector<int>> *mapdata;
    
    
private:
    
    struct point {
        int y;
        int x;
    };
    
    struct hallway {
        std::vector<point> p;
        
        int minX;
        int minY;
        int maxX;
        int maxY;
    };
    void hallwayScan();
    hallway findHallway(int y, int x);
    std::vector<hallway> findAllHallways();
    bool isHallway(int y, int x);
    void smartDoorGen();
    void doorGen();
};
