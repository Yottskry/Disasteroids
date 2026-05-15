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


#ifndef _SHIP_H_
#define _SHIP_H_

#include "resourcefactory.h"
#include "vector.h"
#include "sparkle.h"
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

//typedef enum { psNormal = 79, psLong = 120, psShort = 60 } Playersize;
//typedef enum { plNormal, plShort, plLong, plSticky, plLaser } Playerstate;

#define PI 3.14159265358979323846
#define MAXSPEED 12
#define MAXPARTICLES 15
#define MAXPARTICLESPEED 12
#define ENGINESPREAD 30

typedef struct
{
	int x;
	int y;
	int distance;
	int speed;
	int dx;	// Calculate these on creating the bullet so we
	int dy;	// aren't constantly performing trig
  double m; // dy/dx
  double c; // as in y = mx + c
} Bullet;

typedef struct
{
  int x;
  int y;
	double ddx;
	double ddy;
  double maxspeed;
  double speed;
	double thrust;
	double velocity;
  double shipBearing;
	double thrustBearing;
	bool engineon;
  int score;
  int lives;
	int length;
	int wingspan;
	int sweep;
	double bulletspeed;
	Vector bullets;
	Sparkle trail[MAXPARTICLES];
  //Sprite sprite;
} Ship;

double findC(double dy, double dx, int py, int px);
int ship_drawship(Ship* player, SDL_Renderer* renderer);
int ship_moveship(Ship* player);
void ship_reset(Ship* player, ResourceFactory* factory);
void ship_createbullet(Ship* player);
void ship_movebullets(Ship* player);
void ship_drawbullets(Ship* player, SDL_Renderer* renderer);
void ship_drawengine(Ship* player, SDL_Renderer* renderer);
void ship_startengine(Ship* player);

#endif // _SHIP_H_
