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

#include "level_display.h"

void level_display::draw_level(std::vector<std::vector<int>> *tiles)
{
    move(2,0);
    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        char c [LEVEL_WIDTH + 1];
        for (int j = 0; j < LEVEL_WIDTH; j++) {
            if (tiles->at(i).at(j) == 0) {
                c [j] = 35;
            } else {
                c [j] = 45 + tiles->at(i).at(j);
            }
        }
        c [LEVEL_WIDTH] = '\0';
        printw(c);
        move(i+3,0);
    }
    
    
    
}


//For items on the level not the level itself.
void level_display::draw_items()
{
    
    
    
}


void level_display::draw_messages()
{
    
    
    
}


void level_display::draw_stats()
{
    
    
    
}
