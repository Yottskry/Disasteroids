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


#include "ship.h"

double findC(double dy, double dx, int py, int px)
{
  return py - ((dy / dx)*px);
}

int ship_drawship(Ship* player, SDL_Renderer* renderer)
{

  double rbearing = player->shipBearing * (PI / 180);
	double nextx = player->length * sin(rbearing);
	double nexty = player->length * cos(rbearing);
	nextx = player->x + nextx;
	nexty = player->y + nexty; 

	double wbearing = (player->shipBearing + player->sweep) * (PI / 180);
	double rightx = player->wingspan * sin(wbearing);
	double righty = player->wingspan * cos(wbearing);
	rightx = player->x + rightx;
	righty = player->y + righty;

	double lbearing = (player->shipBearing - player->sweep) * (PI / 180);
	double leftx = player->wingspan * sin(lbearing);
	double lefty = player->wingspan * cos(lbearing);
	leftx = player->x + leftx;
	lefty = player->y + lefty;

	thickLineRGBA(renderer, player->x, player->y, (int)rightx, (int)righty, 2, 255, 255, 255, 255);
	thickLineRGBA(renderer, player->x, player->y, (int)leftx, (int)lefty, 2, 255, 255, 255, 255);
	thickLineRGBA(renderer, (int)leftx, (int)lefty, (int)nextx, (int)nexty, 2, 255, 255, 255, 255);
	thickLineRGBA(renderer, (int)rightx, (int)righty, (int)nextx, (int)nexty, 2, 255, 255, 255, 255);

	ship_drawbullets(player, renderer);	
	//if(player->engineon)
	ship_drawengine(player, renderer);

  return 0;
}

int ship_moveship(Ship* player)
{
	// Take the current speed and create a vector
	double wbearing = player->thrustBearing * (PI / 180.00);
	double dx = player->thrust * sin(wbearing);
	double dy = player->thrust * cos(wbearing);

	double nbearing = player->shipBearing * (PI / 180);
	double ddx = player->velocity * sin(nbearing);
	double ddy = player->velocity * cos(nbearing);

	player->ddx = ddx;
	player->ddy = ddy;

	player->x = player->x + (int)(dx + ddx);
	player->y = player->y + (int)(dy + ddy);

	// Bearing is the new angle of travel
	// Thrust is the new length of the hypotenuse
	if(dy+ddy == 0)
		player->thrustBearing = 0;
	else
		player->thrustBearing = atan((dx + ddx) / (dy + ddy));

	if(sin(player->thrustBearing) == 0)
		player->thrust = player->thrust + player->velocity;
	else
		player->thrust = (dx + ddx) / sin(player->thrustBearing);

	// Trouble is, thrust is directional, so it won't necessarily be set to MAXSPEED but -MAXSPEED
	if(abs(player->thrust) > MAXSPEED)
	{
		if(player->thrust < 0)
			player->thrust = -MAXSPEED;
		else 
			player->thrust = MAXSPEED;
	}

	player->thrustBearing = player->thrustBearing * (180  / PI);

	if(player->y < 0)
		player->y = SCREENH + player->y;

	if(player->y > SCREENH)
		player->y = player->y - SCREENH;

	if(player->x < 0)
		player->x = SCREENW + player->x;

	if(player->x > SCREENW)
		player->x = player->x - SCREENW;

	ship_movebullets(player);

  return 0;
}

void ship_reset(Ship* player, ResourceFactory* factory)
{
//  player->warpenabled = false;
//  player->state = plNormal;
//  player->w = psNormal;
//  player->speed = 0;
//  player->targetspeed = 0;
//  af_setanimation(factory, &(player->sprite),"bat", 1, NULL, NULL, NULL);
}

void ship_createbullet(Ship* player)
{
	Bullet* bullet = malloc(sizeof(Bullet));
	bullet->x = player->x;
	bullet->y = player->y;
	bullet->speed = 8;

	// Work out dx/dy from shipBearing
	bullet->dx = bullet->speed * sin(player->shipBearing * (PI / 180));
	bullet->dy = bullet->speed * cos(player->shipBearing * (PI / 180));
  bullet->m = (dy / dx);
  bullet->c = findC(bullet->dy, bullet->dx, bullet->y, bullet->x);
  
  bullet->distance = 0;
	vector_add(&(player->bullets), (void*)bullet);
}

void ship_movebullets(Ship* player)
{
	for(int i = player->bullets.size - 1; i >= 0; i--)
	{
		Bullet* bullet = vector_item(&(player->bullets), i);
		bullet->x = bullet->x + bullet->dx;
		bullet->y = bullet->y + bullet->dy;

		if(bullet->x > SCREENW)
    {
			bullet->x = 0;
      bullet->c = findC(bullet->dy, bullet->dx, bullet->y, bullet->x);
    }		
    if(bullet->y > SCREENH)
    {
			bullet->y = 0;
      bullet->c = findC(bullet->dy, bullet->dx, bullet->y, bullet->x);
    }
		if(bullet->x < 0)
    {
			bullet->x = SCREENW;
      bullet->c = findC(bullet->dy, bullet->dx, bullet->y, bullet->x);
    }
		if(bullet->y < 0)
    {
			bullet->y = SCREENH;
      bullet->c = findC(bullet->dy, bullet->dx, bullet->y, bullet->x);
    }
		bullet->distance = bullet->distance + abs(bullet->speed);
		if(bullet->distance > SCREENW - 100)
		{
			vector_remove(&(player->bullets), (void*)bullet);
      //printf("Bullet count: %d\n", player->bullets.size);
			free(bullet);
		}
	}	
}

void ship_drawbullets(Ship* player, SDL_Renderer* renderer)
{
	for(int i = 0; i < player->bullets.size; i++)
	{
		Bullet* bullet = vector_item(&(player->bullets), i);
		//rectangleRGBA(renderer, bullet->x - 2, bullet->y - 2, bullet->x + 2, bullet->y + 2, 255, 255, 255, 255);
		filledCircleRGBA(renderer, bullet->x, bullet->y, 9, 188, 188, 255, 60);
		filledCircleRGBA(renderer, bullet->x, bullet->y, 5, 188, 225, 255, 100);
		filledCircleRGBA(renderer, bullet->x, bullet->y, 2, 255, 255, 255, 255);
    //printf("Bullet %d distance %d\n", i, bullet->distance);
	}
}

void ship_drawengine(Ship* player, SDL_Renderer* renderer)
{
	for(int i = 0; i < MAXPARTICLES; i++)
	{
		if(player->trail[i].alpha > 0)
        {
            if(i < 5)
			    filledCircleRGBA(renderer, player->trail[i].x, player->trail[i].y, 2, 255, 255, 255, player->trail[i].alpha);
            else if(i < 10)
			    filledCircleRGBA(renderer, player->trail[i].x, player->trail[i].y, 2, 252, 148, 3, player->trail[i].alpha);
            else
			    filledCircleRGBA(renderer, player->trail[i].x, player->trail[i].y, 2, player->trail[i].r, 100, 100, player->trail[i].alpha);
        }
		player->trail[i].x += player->trail[i].dx;
		player->trail[i].y += player->trail[i].dy;
		player->trail[i].displacement += abs(player->trail[i].speed);
		if(player->trail[i].alpha >= 15)
			player->trail[i].alpha -= 15;
		else
			player->trail[i].alpha = 0;

		if((player->trail[i].displacement > 80) || (player->trail[i].alpha == 0))
		{
			double randspeed = (rand() % MAXPARTICLESPEED) + 4;
			double randangle = (rand() % ENGINESPREAD) - (ENGINESPREAD / 2);
			player->trail[i].x = player->x;
			player->trail[i].y = player->y;
			player->trail[i].displacement = 0;	
			player->trail[i].dx = -(randspeed * sin((player->shipBearing+randangle) * (PI / 180)));
			player->trail[i].dy = -(randspeed * cos((player->shipBearing+randangle) * (PI / 180)));
			if(player->engineon)
				player->trail[i].alpha = 255;
			else
				player->trail[i].alpha = 0;
			player->trail[i].speed = randspeed;
		}

	}

}

// Reset the particle positions
void ship_startengine(Ship* player)
{
	for(int i = 0; i < MAXPARTICLES; i++)
	{
		double randspeed = (rand() % MAXPARTICLESPEED) + 4;
		double randangle = (rand() % ENGINESPREAD) - (ENGINESPREAD / 2);
		player->trail[i].x = player->x;
		player->trail[i].y = player->y;
		player->trail[i].displacement = 0;	
		player->trail[i].dx = -(randspeed * sin((player->shipBearing+randangle) * (PI / 180)));
		player->trail[i].dy = -(randspeed * cos((player->shipBearing+randangle) * (PI / 180)));
		player->trail[i].alpha = 255;
		player->trail[i].speed = randspeed;
		player->trail[i].r = 200 + (rand() % 50);
	}
	player->engineon = true;
}
