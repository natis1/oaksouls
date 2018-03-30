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
    if (LEVEL_GEN_OPTIMIZATION <= 0) {
        for (int i = 1; i < LEVEL_HEIGHT - 1; i++) {
            for (int j = 1; j < LEVEL_WIDTH - 1; j++) {
                if (mapdata->at(i).at(j) >= FLOOR && isHallway(i, j)) {
                    mapdata->at(i).at(j) = HALL;
                } else if (mapdata->at(i).at(j) > FLOOR) {
                    mapdata->at(i).at(j) = FLOOR;
                }
            }
        }
    } else {
        for (int i = 1; i < LEVEL_HEIGHT - 1; i++) {
            for (int j = 1; j < LEVEL_WIDTH - 1; j++) {
                if (mapdata->at(i).at(j) >= POSSIBLE_HALL && isHallway(i, j)) {
                    mapdata->at(i).at(j) = HALL;
                } else if (mapdata->at(i).at(j) > FLOOR) {
                    mapdata->at(i).at(j) = FLOOR;
                }
            }
        }
    }
}



bool stage2::isHallway(int y, int x)
{
    return ( (mapdata->at(y-1).at(x) >= FLOOR && mapdata->at(y+1).at(x) >= FLOOR && mapdata->at(y).at(x-1) < FLOOR && mapdata->at(y).at(x+1) < FLOOR) ||
             (mapdata->at(y-1).at(x) < FLOOR && mapdata->at(y+1).at(x) < FLOOR && mapdata->at(y).at(x-1) >= FLOOR && mapdata->at(y).at(x+1) >= FLOOR));
}

void stage2::doorGen()
{
    for (int i = 1; i < LEVEL_HEIGHT - 1; i++) {
        for (int j = 1; j < LEVEL_WIDTH - 1; j++) {
            if (mapdata->at(i).at(j) == HALL) {                
                if ((double) rand() / (RAND_MAX) < STAGE2_DOOR_CHANCE) {
                    mapdata->at(i).at(j) = DOOR;
                }
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
    std::vector<hallway> h = findAllHallways();
    
    for (uint i = 0; i < h.size(); i++) {
        if ((double) rand() / (RAND_MAX) < STAGE2_DOOR_CHANCE) {
            int numpoints = h.at(i).p.size();
            std::uniform_int_distribution<int> uni(1, numpoints);
            int ptnum = uni(rng) - 1;
            // uhhhhhhh, wtf was I thinking with these var names
            mapdata->at(h.at(i).p.at(ptnum).y).at(h.at(i).p.at(ptnum).x) = DOOR;
            
        }
    }
    
}

stage2::hallway stage2::findHallway(int y, int x)
{
    stage2::hallway h;
    h.minY = INT32_MAX;
    h.maxY = 0;
    h.minX = INT32_MAX;
    h.maxX = 0;
//     point startingPt;
//     startingPt.y = y; startingPt.x = x;
    h.p.push_back({y, x});
    uint counter = 0;
    
    // I'm really worried about this part producing undefined behavior when optimized.
    // It just doesn't seem right what I'm doing.
    
    while (counter < h.p.size()) {
        bool l = false; bool r = false; bool u = false; bool d = false;
        
        // Ok technically this is undefined behavior if you allow the edges of your map to be halls. Then it should rightfully segfault.
        if (mapdata->at(h.p.at(counter).y).at(h.p.at(counter).x - 1) == HALL) {
            l = true;
        }
        if (mapdata->at(h.p.at(counter).y).at(h.p.at(counter).x + 1) == HALL) {
            r = true;
        }
        // y + 1 actually moves you down. Weird world we live in where the origin is in the top left and x and y are reversed.
        if (mapdata->at(h.p.at(counter).y + 1).at(h.p.at(counter).x) == HALL) {
            d = true;
        }
        if (mapdata->at(h.p.at(counter).y - 1).at(h.p.at(counter).x) == HALL) {
            u = true;
        }
        
        // This might be an optimization but it might be unnessisary because compilers are smart.
        if (d || u || l || r) {
            for (uint i = 0; i < h.p.size(); i++) {
                point p = h.p.at(i);
                
                // shit code that probably works. Lol nope.
                if (d && p.y == h.p.at(counter).y + 1 && p.x == h.p.at(counter).x ) d = false;
                if (u && p.y == h.p.at(counter).y - 1 && p.x == h.p.at(counter).x ) u = false;
                if (r && p.x == h.p.at(counter).x + 1 && p.y == h.p.at(counter).y ) r = false;
                if (l && p.x == h.p.at(counter).x - 1 && p.y == h.p.at(counter).y ) l = false;
            }
        }
        if (d) h.p.push_back({(h.p.at(counter).y + 1), h.p.at(counter).x});
        
        if (u) h.p.push_back({(h.p.at(counter).y - 1), h.p.at(counter).x});
        
        if (r) h.p.push_back({h.p.at(counter).y, (h.p.at(counter).x + 1)});
        
        if (l) h.p.push_back({h.p.at(counter).y, (h.p.at(counter).x - 1)});
        
        counter++;
    }
    
    // This might be another stupid optimization. idk anymore. send help.
    for (uint i = 0; i < h.p.size(); i++) {
        if (h.minY > h.p.at(i).y) h.minY = h.p.at(i).y;
        if (h.maxY < h.p.at(i).y) h.maxY = h.p.at(i).y;
        if (h.minX > h.p.at(i).x) h.minX = h.p.at(i).x;
        if (h.maxX < h.p.at(i).x) h.maxX = h.p.at(i).x;
    }
    
    return h;
}

std::vector<stage2::hallway> stage2::findAllHallways()
{
    std::vector<stage2::hallway> h;
    
    // Insane 4 dimensional for loop to find all hallways in 2D. WTF
    for (int i = 0; i < LEVEL_HEIGHT - 1; i++) {
        for (int j = 0; j < LEVEL_WIDTH - 1; j++) {
            if (mapdata->at(i).at(j) == HALL) {
                bool addHall = true;
                for (uint x = 0; x < h.size(); x++) {
                    // Could these intersect? Possibly a huge optimization but I'm not quite sure yet
                    if (i >= h.at(x).minY && i <= h.at(x).maxY && j >= h.at(x).minX && j <= h.at(x).maxX) {
                        for (uint y = 0; y < h.at(x).p.size(); y++) {
                            if (h.at(x).p.at(y).y == i && h.at(x).p.at(y).x == j) {
                                addHall = false;
                                break;
                            }
                        }
                        
                    }
                    if (!addHall) break;
                }
                if (addHall) {
                    h.push_back(findHallway(i, j));
                }
                
            }
        }
    }
    
    
    
    return h;
}
