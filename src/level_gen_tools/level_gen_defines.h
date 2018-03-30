/*
 * Oaksouls ~ A difficult roguelike about a	tree spirit.
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
#define LEVEL_WIDTH 80
#define LEVEL_HEIGHT 20

/*
 * Level gen optimization 0 assumes that floors are not characterized into halls/possible halls at all and uses heuristics to find these.
 * Level gen optimization 1 assumes that all halls are either halls or possible halls and applies heuristics to only halls.
 * Level gen optimization 2 assumes that all halls are halls. If this level generation optimization generates possible halls, it is a bug and display renderer will draw bugged tiles.
 * 
 * TODO: Change this to at least 1 before releasing the game.
 * 
 */
#define LEVEL_GEN_OPTIMIZATION 0

// Wall objects and other wall related stuff are <= 10. This means you can find walls just by finding tiles <= 10


#define UNBREAKABLE_WALL -1
#define MAP_EDGE -1


// Breakable wall and wall-like objects are between 0 and 10
#define BREAKABLE_WALL 0
#define WALLTRAP 1

#define FLOOR 11
// For level generators that aren't sure if what they are making is actually hallway
#define POSSIBLE_HALL 12
// For level generators that are sure that they are making a hallway.
#define HALL 13

// Objects that appear on floor are > 20. This means that you can find floors just by finding tiles >= 11
#define DOOR 21
#define UPSTAIR 22
#define DOWNSTAIR 23
#define OAKALTER 30
#define ENEMYALTER 31


// constants for binary tree stage1 method
#define BINARY_TREE_MAX_ROOM_VOLUME 150
#define BINARY_TREE_MAX_SPLIT_AMT 0.8
#define BINARY_TREE_MIN_WALL_THICKNESS 1
#define BINARY_TREE_MAX_WALL_THICKNESS 2
#define BINARY_TREE_ROOM_CONNECT_TRIES 10

// constants for stage2 generation
#define STAGE2_DOOR_CHANCE 1
#define STAGE2_SMART_DOORS true
