/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2017  <copyright holder> <email>
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

#include "statistics.h"

#define XP_WEIGHT 1.0
#define CREATURE_WEIGHT 250
#define FLOOR_WEIGHT 1000
#define STARTING_AREA 5

statistics::statistics::statistics()
{
    forestName = "Null";
    highestName = "Null";
}


int statistics::getForestArea()
{
    // area in square meters.
    return ((forestXP * XP_WEIGHT + forestCreatures * CREATURE_WEIGHT + forestFloors * FLOOR_WEIGHT)/1000) + 5;
}

