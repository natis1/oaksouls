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

#include "stage2.h"


stage2::stage2(std::vector<std::vector<int> >* mapdata)
{
    this->mapdata = mapdata;
    if (LEVEL_GEN_OPTIMIZATION <= 1) hallwayScan(); 
    
    if (STAGE2_SMART_DOORS) {
        smartDoorGen();
    } else {
        doorGen();
    }
    
    
}

void stage2::hallwayScan()
{
    if (LEVEL_GEN_OPTIMIZATION == 0) {
        for (int i = 1; i < LEVEL_HEIGHT - 1; i++) {
            for (int j = 1; j < LEVEL_WIDTH - 1; j++) {
                if (mapdata->at(i).at(j) >= FLOOR && isHallway(i, j)) {
                    mapdata->at(i).at(j) = HALL;
                }
            }
        }
    } else {
        for (int i = 1; i < LEVEL_HEIGHT - 1; i++) {
            for (int j = 1; j < LEVEL_WIDTH - 1; j++) {
                if (mapdata->at(i).at(j) >= POSSIBLE_HALL && isHallway(i, j)) {
                    mapdata->at(i).at(j) = HALL;
                }
            }
        }
    }
}



bool stage2::isHallway(int y, int x)
{
    return ( (mapdata->at(y-1).at(x) != 0 && mapdata->at(y+1).at(x) != 0 && mapdata->at(y).at(x-1) == 0 && mapdata->at(y).at(x+1) == 0) ||
             (mapdata->at(y-1).at(x) == 0 && mapdata->at(y+1).at(x) == 0 && mapdata->at(y).at(x-1) != 0 && mapdata->at(y).at(x+1) != 0));
}

void stage2::doorGen()
{
    for (int i = 1; i < LEVEL_HEIGHT - 1; i++) {
        for (int j = 1; j < LEVEL_WIDTH - 1; j++) {
            if (mapdata->at(i).at(j) >= FLOOR && isHallway(i, j)) {
                mapdata->at(i).at(j) = HALL;
                
                if ((double) rand() / (RAND_MAX) < STAGE2_DOOR_CHANCE) {
                    mapdata->at(i).at(j) = DOOR;
                }
                
            } else {
                mapdata->at(i).at(j) = FLOOR;
            }
            
        }
    }
    
}

/*
 * Like normal door generation except doors only generate once per hallway, if at all.
 * 
 * Hallways are found using the "battleship" method- with the added assumption that hallways can curve.
 */


void stage2::smartDoorGen()
{
    std::random_device rd;
    std::mt19937 rng(rd());
//    std::uniform_int_distribution<int> dist(0, 9);
    
    for (int i = 1; i < LEVEL_HEIGHT - 1; i++) {
        for (int j = 1; j < LEVEL_WIDTH - 1; j++) {
            if (mapdata->at(i).at(j) >= FLOOR && isHallway(i, j)) {
                mapdata->at(i).at(j) = HALL;
                
                if ((double) rand() / (RAND_MAX) < STAGE2_DOOR_CHANCE) {
                    mapdata->at(i).at(j) = DOOR;
                }
                
            } else {
                mapdata->at(i).at(j) = FLOOR;
            }
            
        }
    }
    
}
