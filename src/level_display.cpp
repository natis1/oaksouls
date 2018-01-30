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
    
    // TODO: add some goddamn color
    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        char c [LEVEL_WIDTH + 1];
        for (int j = 0; j < LEVEL_WIDTH; j++) {
            switch (tiles->at(i).at(j)) {
                case BREAKABLE_WALL:
                case FLOOR:
                    c [j] = 35 + tiles->at(i).at(j);
                    break;
                case UNBREAKABLE_WALL:
                    // Should be black or something. and char 35
                    c [j] = 34;
                    break;
                case HALL:
                    c [j] = 95; // _
                    break;
                case DOOR:
                    c [j] = 43; // +
                    break;
                c [j] = 63; // ?
                
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
