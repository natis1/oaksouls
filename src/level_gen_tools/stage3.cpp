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

#include "stage3.h"
#include "level_gen.h"
#include <random>



stage3::stage3(std::vector<std::vector<int> >* mapdata)
{
    this->mapdata = mapdata;
    
    concatPoints();
    
}




void stage3::concatPoints()
{
    
    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        for (int j = 0; j < LEVEL_WIDTH; j++) {
            if (mapdata->at(i).at(j) == FLOOR) {
                floors.push_back( {i, j} );
                
            } else if (mapdata->at(i).at(j) == BREAKABLE_WALL || mapdata->at(i).at(j) == UNBREAKABLE_WALL) {
                walls.push_back( {i, j} );
            }
        }
    }
    
}

void stage3::placeObject(int objID)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> heightDist(1, (LEVEL_HEIGHT - 1));
    std::uniform_int_distribution<int> widthDist(1, (LEVEL_WIDTH - 1));
    int y = 0;
    int x = 0;
    do {
        y = heightDist(rng);
        x = widthDist(rng);
    }
    while (mapdata->at(y).at(x) != FLOOR || mapdata->at(y).at(x) != HALL || mapdata->at(y).at(x) != BREAKABLE_WALL || mapdata->at(y).at(x) != UNBREAKABLE_WALL);
    
    placeObject(objID, y, x);
    
}


void stage3::placeObject(int objID, int featureType)
{
    if (featureType == FLOOR) {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> dist(0, floors.size() - 1);
        int i = dist(rng);
        placeObject(objID, floors.at(i).y, floors.at(i).x);
    } else if (featureType == BREAKABLE_WALL) {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> dist(0, walls.size() - 1);
        int i = dist(rng);
        placeObject(objID, walls.at(i).y, walls.at(i).x);
    }
    
}

void stage3::placeObject(int objID, int y, int x)
{
    int locID = mapdata->at(y).at(x);
    mapdata->at(y).at(x) = objID;
    if (removePoint(locID, y, x) != 0) {
        //log error
        
    }
}

int stage3::removePoint(int pointID, int y, int x)
{
    if (pointID == FLOOR) {
        for (int i = 0; i < floors.size(); i++) {
            if ( floors.at(i).y == y && floors.at(i).x == x) {
                //floors.erase( {&floors.at.(i), floors} );
                
            }
        }
        
    } else if (pointID == BREAKABLE_WALL || pointID == UNBREAKABLE_WALL) {
        for (int i = 0; i < floors.size(); i++) {
            if ( floors.at(i).y == y && floors.at(i).x == x) {
                //floors.erase( {&floors.at.(i), floors} );
                
            }
        }
    }
    
    
}
