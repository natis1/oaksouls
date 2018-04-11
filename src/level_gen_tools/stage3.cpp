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

#include "stage3.h"
#include "level_gen.h"
#include <random>



stage3::stage3(map *level)
{
    this->level = level;
    
    concatPoints();
    
}




void stage3::concatPoints()
{
    
    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        for (int j = 0; j < LEVEL_WIDTH; j++) {
            if (level->mapdata.at(i).at(j) == FLOOR) {
                floors.push_back( {i, j} );
                
            } else if (level->mapdata.at(i).at(j) == BREAKABLE_WALL || level->mapdata.at(i).at(j) == UNBREAKABLE_WALL) {
                walls.push_back( {i, j} );
            }
        }
    }
    
}

void stage3::addAlter(int piety)
{
    point p;
    
    if (piety > 0) {
        p = placeObject(OAKALTER, FLOOR);
    } else {
        p = placeObject(ENEMYALTER, FLOOR);
    }
    alter a;
    a.piety = piety;
    a.x = p.x;
    a.y = p.y;
    if (piety > 0) {
        a.strength = piety;
    } else {
        a.strength = -piety;
    }
    
    
    this->level->alters.push_back(a);
}

void stage3::addExit(int level)
{
    point p;
    // Not the best naming convention.
    if (this->level->level < level) {
        p = placeObject(DOWNSTAIR, FLOOR);
    } else {
        p = placeObject(UPSTAIR, FLOOR);
    }
    
    
    levelExit e;
    e.level = level;
    e.x = p.x;
    e.y = p.y;
    this->level->exits.push_back(e);
    
    
    
}



stage3::point stage3::placeObject(int objID)
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
    while (level->mapdata.at(y).at(x) != FLOOR || level->mapdata.at(y).at(x) != HALL || level->mapdata.at(y).at(x) != BREAKABLE_WALL || level->mapdata.at(y).at(x) != UNBREAKABLE_WALL);
    
    return placeObject(objID, y, x);
}


stage3::point stage3::placeObject(int objID, int featureType)
{
    if (featureType == FLOOR) {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> dist(0, floors.size() - 1);
        int i = dist(rng);
        return placeObject(objID, floors.at(i).y, floors.at(i).x);
    } else if (featureType == BREAKABLE_WALL) {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> dist(0, walls.size() - 1);
        int i = dist(rng);
        return placeObject(objID, walls.at(i).y, walls.at(i).x);
    }
    return {-1, -1};
}

stage3::point stage3::placeObject(int objID, int y, int x)
{
    int locID = level->mapdata.at(y).at(x);
    level->mapdata.at(y).at(x) = objID;
    if (removePoint(locID, y, x) != 0) {
        //log error
        
    }
    
    return {y, x};
}

int stage3::removePoint(int pointID, int y, int x)
{
    if (pointID == FLOOR) {
        for (uint i = 0; i < floors.size(); i++) {
            if ( floors.at(i).y == y && floors.at(i).x == x) {
                
                // Here's hoping this actually works for vectors holding structs.
                floors.erase( floors.begin() + i );
                return 0;
            }
        }
        
    } else if (pointID == BREAKABLE_WALL || pointID == UNBREAKABLE_WALL) {
        for (uint i = 0; i < walls.size(); i++) {
            if ( walls.at(i).y == y && walls.at(i).x == x) {
                walls.erase( walls.begin() + i );
                return 0;
            }
        }
    } else {
        return 0;
    }
    
    return 1;
}

void stage3::placeObjectExternal(int objID)
{
    placeObject(objID);
}

void stage3::placeObjectExternal(int objID, int featureType)
{
    placeObject(objID, featureType);
}

void stage3::placeObjectExternal(int objID, int y, int x)
{
    placeObject(objID, y, x);
}
