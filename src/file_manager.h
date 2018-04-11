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

#include "statistics.h"
#include "options.h"
/**
 * @todo write docs... hahahahaha like that's happening. Thanks computer.
 */
class file_manager
{
public:
    statistics loadStatistics();
    int saveStatistics(statistics stats);
    options loadOptions();
    int saveOptions(options opts);
    
    
    file_manager();
    
private:    
    void getDataPath();
    std::string dataPath = "";
    std::string statsPath = "";
    std::string optionsPath = "";
    std::string savesPath = "";
    
    int makeDirectory(const char* path);
};
