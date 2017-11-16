/*
 * Loads data from the system for use throughout the game
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

#include "statistics.h"
/**
 * @todo write docs... hahahahaha like that's happening. Thanks computer.
 */
class file_manager
{
public:
    statistics* loadStatistics();
    int saveStatistics(statistics* stats);
    
private:
    statistics* newStatistics();
    char* getDataPath();
    char* getStatisticsPath();
    
};
