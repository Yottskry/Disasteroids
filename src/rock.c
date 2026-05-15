#include "rock.h"
#include <math.h>

const Sint16 asteroidx[] = { -20, -10, 0, 10, 20, 20, 10, -10, -20, -20 };
const Sint16 asteroidy[] = { 10, 20, 20, 20, 20, -10, -20, -20, -10, 10 };

Asteroid* rock_create(int x, int y, RockSize size)
{
  Asteroid* rock = malloc(sizeof(Asteroid));
  rock->size = size;
  rock->speed = (rand() % 5) + 1;
  rock->bearing = (rand() % 360);
  printf("Bearing %d\n", rock->bearing);
  if(rock->bearing % 90 == 0)
      rock->bearing = rock->bearing + 10;
  double rbearing = rock->bearing * (M_PI / 180);
	rock->x = x;
	rock->y = y;
	rock->dx = rock->speed * sin(rbearing);  
	rock->dy = rock->speed * cos(rbearing);
	rock->xposn = malloc(sizeof(Sint16) * ROCKNODES);
	rock->yposn = malloc(sizeof(Sint16) * ROCKNODES);
	rock->scale = (double)size / 2;
	for(int i = 0; i < ROCKNODES; i++)
	{
		rock->xposn[i] = (asteroidx[i] * rock->scale) + rock->x;
		rock->yposn[i] = (asteroidy[i] * rock->scale) + rock->y;
//		printf("%d ", rock->xposn[i]);
//    printf("\n");
	}

  return rock;
}
 
void rock_draw(Asteroid* rock, SDL_Renderer* renderer)
{
	//filledPolygonRGBA(renderer, rock->xposn, rock->yposn, ROCKNODES, 200, 200, 255, 255);
	
	for(int i = 0; i < ROCKNODES; i++)
	{
		int j = i+1;
		if(j == ROCKNODES)
			j = 0;
		thickLineRGBA(renderer, rock->xposn[i], rock->yposn[i], rock->xposn[j], rock->yposn[j], 2, 255, 255, 255, 255);		
	}

	//polygonRGBA(renderer, rock->xposn, rock->yposn, ROCKNODES, 255, 255, 255, 255);
	
}

void rock_move(Asteroid* rock)
{
	rock->x += rock->dx;
	rock->y += rock->dy;

	if(rock->x > SCREENW)
		rock->x = 0;
	if(rock->x < 0)
		rock->x = SCREENW;
	if(rock->y > SCREENH)
		rock->y = 0;
	if(rock->y < 0)
		rock->y = SCREENH;

	for(int i = 0; i < ROCKNODES; i++)
	{
		rock->xposn[i] = (asteroidx[i] * rock->scale) + rock->x;
		rock->yposn[i] = (asteroidy[i] * rock->scale) + rock->y;
	//	printf("%d ", rock->xposn[i]);
	}
/*
	for(int i = 0; i < ROCKNODES; i++)
	{
		rock->xposn[i] += rock->dx;
		rock->yposn[i] += rock->dy;
	}*/
}

void rock_destroy(Asteroid* rock)
{
  free(rock);
}
