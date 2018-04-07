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

level_display::level_display(map* level)
{
    this->level = level;
}


void level_display::draw_level()
{
    move(2,0);
    
    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        for (int j = 0; j < LEVEL_WIDTH; j++) {
            switch (level->mapdata.at(i).at(j)) {
                case BREAKABLE_WALL:
                case UNBREAKABLE_WALL:
                case MAP_EDGE:
                    // Should be black or something. and char 35
                    put_colored_ch(NORMAL_WHITE, '#');
                    break;
                case FLOOR:
                    put_colored_ch(NORMAL_WHITE, '.');
                    break;
                case HALL:
                    put_colored_ch(NORMAL_WHITE, '.');
                    break;
                case DOOR:
                    put_colored_ch(NORMAL_GREEN, '/');
                    break;
                case OAKALTER:
                    place_alter(i, j);
                    break;
                case ENEMYALTER:
                    place_alter(i, j);
                    break;
                case DOWNSTAIR:
                    put_colored_ch(NORMAL_WHITE, '<');
                    break;
                case UPSTAIR:
                    put_colored_ch(NORMAL_WHITE, '>');
                    break;
                default:
                    put_colored_ch(VIVID_RED, '?');
                
            }
        }
        move(i+3,0);
    }
    for (int i = 65; i < 97; i++) {
        put_colored_ch(i, 63);
    }
    
    
    
    
}

void level_display::place_alter(int y, int x)
{
    
    for (uint k = 0; k < level->alters.size(); k++) {
        if (level->alters.at(k).x == x && level->alters.at(k).y == y) {
            if (level->alters.at(k).piety > 0) {
                
                if (level->alters.at(k).strength > 1000) {
                    put_colored_ch(BRIGHT_GREEN, '_');
                } else if (level->alters.at(k).strength >= 500) {
                    put_colored_ch(VIVID_GREEN, '_');
                } else {
                    put_colored_ch(NORMAL_GREEN, '_');
                }
            } else {
                if (level->alters.at(k).strength > 1000) {
                    put_colored_ch(BRIGHT_RED, '_');
                } else if (level->alters.at(k).strength >= 500) {
                    put_colored_ch(VIVID_RED, '_');
                } else {
                    put_colored_ch(NORMAL_RED, '_');
                }
            }
            
            
            return;
        }
    }
    put_colored_ch(VIVID_RED, '?');
    
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
    int errcheck = attron(COLOR_PAIR(color));
    char c [2];
    c[0] = ch;
    c[1] = '\0';
    if ( printw(c) != 0  || errcheck != 0) {
        printw("e");
    };
}

