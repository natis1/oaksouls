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
#include "color.h"

#include <iostream>

void level_display::draw_level(std::vector<std::vector<int>> *tiles)
{
    move(2,0);
    
    // TODO: add some goddamn color
    
    
    
    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        for (int j = 0; j < LEVEL_WIDTH; j++) {
            switch (tiles->at(i).at(j)) {
                case BREAKABLE_WALL:
                case FLOOR:
                    put_colored_ch(NORMAL_WHITE, 46);
                    break;
                case UNBREAKABLE_WALL:
                    // Should be black or something. and char 35
                    put_colored_ch(BRIGHT_BLACK, 35);
                    break;
                case HALL:
                    put_colored_ch(BRIGHT_WHITE, 46);
                    break;
                case DOOR:
                    put_colored_ch(NORMAL_GREEN, 43);
                    break;
                default:
                    put_colored_ch(BRIGHT_RED, 63);
                
            }
        }
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

void level_display::set_default_colors()
{
    color c;
    c.initColors();
    
}



void level_display::put_colored_ch(int color, char ch)
{
    attron(COLOR_PAIR(color));
    char c [2];
    c[0] = ch;
    c[1] = '\0';
    if ( printw(c) != 0 ) {
        printw("e");
    };
}

