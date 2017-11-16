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
#include <stdlib.h>

#include "file_manager.h"


int file_manager::saveStatistics(statistics* stats)
{
    char* statfile = getDataPath();
    strcat(statfile, "/globalstats");
    std::ofstream ofs(statfile, std::ios::binary);
    ofs.write((char *)stats, sizeof(stats));
    
    //TODO: Error checking
    return 0;
}


statistics* file_manager::loadStatistics()
{
    char* statfile = getDataPath();
    strcat(statfile, "/globalstats");
    struct stat s;
    if ( stat(statfile, &s) != 0) {
        statistics* blankStats = newStatistics();
        saveStatistics(blankStats);
        return blankStats;
    } else {
        statistics* stats;
        std::ifstream ifs(statfile, std::ios::binary);
        ifs.read((char *)&stats, sizeof(stats));
        return stats;
    }
}

statistics* file_manager::newStatistics()
{
    statistics stats;
    statistics* st2 = &stats;
    return st2;
}

char* file_manager::getDataPath()
{
    char* localdata = getenv("HOME");
    strcat(localdata, "/.local/share/oaksouls");
    struct stat s;
    if ( stat(localdata, &s) != 0) {
        int err = mkdir(localdata, 0775);
        if (err != 0) {
            exit(err);
        }
    }
    return localdata;
}

char* file_manager::getStatisticsPath()
{
    char* statfile = getDataPath();
    strcat(statfile, "/globalstats");
    return statfile;
}


