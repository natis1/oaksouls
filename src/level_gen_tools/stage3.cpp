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


stage3::stage3(std::vector<std::vector<int> >* mapdata)
{
    this->mapdata = mapdata;
    
    concatPoints();
    
}




void stage3::concatPoints()
{
    
    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        for (int j = 0; j < LEVEL_WIDTH; j++) {
            if (mapdata->at(i).at(j) >= FLOOR) {
                floors.push_back( {i, j} );
                
            } else {
                walls.push_back( {i, j} );
            }
        }
    }
    
    
    
    
}
