/*
 * Loads savegames and stuff for Oak Souls
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


#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

#include "file_manager.h"

file_manager::file_manager()
{
    getDataPath();
    getStatisticsPath();
}


int file_manager::saveStatistics(statistics stats)
{
    std::cerr << "stat file location is " << statsPath << " and data file is " << dataPath << std::endl;
    std::ofstream ofs(statsPath, std::ios::binary);
    ofs.write((char *)&stats, sizeof(stats));
    
    //TODO: Error checking
    return 0;
}


statistics file_manager::loadStatistics()
{
    struct stat s;
    if ( stat(statsPath.c_str(), &s) != 0) {
        statistics blankStats;
        blankStats.initStatistics();
        saveStatistics(blankStats);
        return blankStats;
    } else {
        statistics stats;
        std::ifstream ifs(statsPath, std::ios::binary);
        ifs.read((char *)&stats, sizeof(stats));
        return stats;
    }
}

void file_manager::getDataPath()
{
    dataPath = getenv("HOME");
    dataPath = dataPath + "/.local/share/oaksouls";
    std::cerr << dataPath << " is current path" << std::endl;
    struct stat s;
    if ( stat(dataPath.c_str(), &s) != -1) {
        if (!S_ISDIR(s.st_mode)) {
            std::cerr << dataPath << " is corrupted, cannot be read, or is not a directory. Error:" << stat(dataPath.c_str(), &s) << std::endl;
        }
    } else {
        std::cerr << "Save directory not found, rebuilding." << std::endl;
        int err = mkdir(dataPath.c_str(), 0775);
        if (err != 0) {
            std::cerr << "Unable to make save directory... for some reason" << std::endl;
        }
    }
}

void file_manager::getStatisticsPath()
{
    statsPath = dataPath + "/globalstats";
}


