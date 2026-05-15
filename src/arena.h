/*
*
* Disasteroids - Copyright 2024 Stephen Branley.
*
* This file is part of Disasteroids.
*
* Disasteroids is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License,
* or (at your option) any later version.
*
* Disasteroids is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Foobar. If not, see <https://www.gnu.org/licenses/>.
*
*/


#ifndef _ARENA_H_
#define _ARENA_H_

#include "resourcefactory.h"
#include "bonus.h"
#include "app.h"
#include "vector.h"
#include "rock.h"
#include "ship.h"
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <math.h>

#define MAXBULLETS 10
#define NUMEXPLOSIONS 40

typedef unsigned char byte;

typedef struct
{
  long bonuscounter;
  int bonuscount;
  int bulletcount;
  int level;
  Uint32 lastbonus;
  Uint32 counter;
  ResourceFactory* factory;
	Vector rocks;
} Arena;

void arena_initlevel(Arena* arena, int level);
void arena_drawrocks(Arena* arena, SDL_Renderer* renderer);
void arena_moverocks(Arena* arena);
bool arena_checkbullets(Arena* arena, Ship* player);

#endif
