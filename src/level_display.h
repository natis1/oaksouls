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

#pragma once

#include <curses.h>
#include <vector>
#include "level_gen_tools/level_gen_defines.h"

/**
 * How this is going to work:
 * 
 * Top two lines for stats
 * next 20 lines for map, status, etc.
 * Bottom 2+ lines for message log
 * 
 * 
 */
class level_display
{
public:
    level_display(map *level);
    void draw_level();
    void draw_items();
    void draw_stats();
    void draw_messages();
    void set_default_colors();
private:
    map *level;
    void put_colored_ch(int color, char ch);
    void place_alter(int y, int x);
    
};
