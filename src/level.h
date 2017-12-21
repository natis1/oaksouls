/*
 * This program allows for the generation of dungeons of arbitrary size
 * Copyright (C) 2017  Eli Stone
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

#include <vector>
#include "level_gen_tools/level_gen_defines.h"


class level
{
public:
    level(int type = 0, int difficulty = 1);
protected:
    int tiles [LEVEL_HEIGHT] [LEVEL_WIDTH];
    int type;
    int difficulty;
private:
    // Build a level with two integers. Allows for potentially multiple kinds of dungeons.
    void generateFloor();
};
