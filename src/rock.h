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


#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#define MAXBRICKPARTICLES 255
#define BRICKDECAY 15
#define EXPLOSIONPARTICLES 200
#define BRICKSPEED 3
#define BRICKSCORE 10

#define ROCKNODES 10

#include "resourcefactory.h"
#include "sparkle.h"
#include <stdbool.h>
#include <SDL2/SDL2_gfxPrimitives.h>

typedef enum { rsSmall = 1, rsMedium = 2, rsLarge = 4 } RockSize;
typedef enum { eNone = 0, eLeft = 1, eRight = 2, eTop = 4, eBottom = 8, eTopLeft = 16, eTopRight = 32, eBottomLeft = 64, eBottomRight = 128 } Edge;

extern const Sint16 asteroidx[];
extern const Sint16 asteroidy[];

typedef struct
{
  Uint32 startdelay;
  Uint32 starttime;
  bool isdead;
  Sparkle particles[EXPLOSIONPARTICLES];
  int x;
  int y;
  SDL_Color color;
} Explosion;

typedef struct
{
	Sint16* xposn;
	Sint16* yposn;
	int x;
	int y;
	double dx;
	double dy;  
  int bearing;
  int speed;
  bool isdead;
	double scale;
  RockSize size;
  Sparkle particles[MAXBRICKPARTICLES];
} Asteroid;

Asteroid* rock_create(int x, int y, RockSize size);
void rock_draw(Asteroid* rock, SDL_Renderer* renderer);
void rock_move(Asteroid* rock);
void rock_destroy(Asteroid* rock);

#endif
