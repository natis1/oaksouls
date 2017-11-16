/*
 * Defines certain performance settings in OakSouls
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

// All delays in microseconds


// Will increase once redrawing optimizations get built
#define FRAMERATE 60
#define SLOW_FRAMERATE 20
#define SECOND 1000000
#define KBD_POLLING_HZ 1000


#define MAX_REDRAW_DELAY SECOND/FRAMERATE
// For redraws that will take longer and that don't really matter
#define SLOW_REDRAW_DELAY SECOND/SLOW_FRAMERATE

#define KBD_POLLING_DELAY SECOND/KBD_POLLING_HZ

// TODO: create redraw optimizations by only redrawing some stuff.

// Optimization level 1 should do everything possible while still working with any terminal size > 80x24
// Level 2 should only work with properly sized windows
#define REDRAW_OPTIMIZATION_LEVEL 0
