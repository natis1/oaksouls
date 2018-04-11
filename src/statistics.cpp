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

#include "statistics.h"
#include <string.h>

#define XP_WEIGHT 1.0
#define CREATURE_WEIGHT 250
#define FLOOR_WEIGHT 1000
#define STARTING_AREA 5


void statistics::initStatistics()
{
    strcpy(forestName, "Null");
    strcpy(highestName, "Null");
    forestCreatures = 0;
    forestDeaths = 0;
    forestFloors = 0;
    forestGamesPlayed = 0;
    forestXP = 0;
    highestCreatures = 0;
    highestFloors = 0;
    highestLevel = 0;
    highestXP = 0;
    totalCreatures = 0;
    totalDeaths = 0;
    totalFloors = 0;
    totalGamesPlayed = 0;
    totalXP = 0;
}


int statistics::getForestArea()
{
    // area in square meters.
    return ((forestXP * XP_WEIGHT + forestCreatures * CREATURE_WEIGHT + forestFloors * FLOOR_WEIGHT)/1000) + 5;
}

