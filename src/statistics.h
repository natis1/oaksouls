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

#pragma once

#include <string>

/**
 * @todo write docs
 */
class statistics
{
public:
    
    void initStatistics();
    int getForestArea();
    
    //Most successful savegame stats
    char forestName[20];
    long forestXP;
    // Number of enemies killed on characters that made it back alive successfully
    int forestCreatures;
    int forestGamesPlayed;
    int forestDeaths;
    int forestFloors;
    
    // Single run stats for best successful single run
    char highestName[20];
    long highestXP;
    int highestCreatures;
    int highestLevel;
    int highestFloors;
    
    // Total stats
    long totalXP;
    int totalCreatures;
    int totalGamesPlayed;
    int totalDeaths;
    int totalFloors;
    
};
