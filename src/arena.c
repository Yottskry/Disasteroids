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


#include "arena.h"
#include "config.h"
//#include <assert.h>
//#ifndef _WIN32
//#include <dirent.h>
//#else
//#include <windows.h>
//#endif // WIN32

void arena_initlevel(Arena* arena, int level)
{
  int small = level % 2 == 0 ? 0 : 1;
  int large = level % 2 == 0 ? ((level - 1) / 2) + 1 : (level / 2) + 1;

  printf("Level %d. %d large, %d small\n", level, large, small);

	for(int i = 0; i < large; i++)
	{
    int x = rand() % 1024;
    int y = rand() % 768;
		Asteroid* rock = rock_create(x, y, rsLarge);
		vector_add(&(arena->rocks), rock);
	}

	for(int i = 0; i < small; i++)
	{
    int x = rand() % 1024;
    int y = rand() % 768;
		Asteroid* rock = rock_create(x, y, rsMedium);
		vector_add(&(arena->rocks), rock);
	}
}

void arena_drawrocks(Arena* arena, SDL_Renderer* renderer)
{
  for(int i = 0; i < arena->rocks.size; i++)
  {
    Asteroid* rock = vector_item(&(arena->rocks), i);
    rock_draw(rock, renderer);
  }
}

void arena_moverocks(Arena* arena)
{
  for(int i = 0; i < arena->rocks.size; i++)
  {
    Asteroid* rock = vector_item(&(arena->rocks), i);
    rock_move(rock);
  }
}

bool arena_checkbullets(Arena* arena, Ship* player)
{
  // Check each bullet for a collision against each rock
  // Do this with the intersection of two lines:
  // One being each edge of the rock, and the other
  // being the line between the bullet start position
  // and the bullet end position
  for(int j = 0; j < player->bullets.size; j++)
  {
    Bullet* b = (Bullet*)(vector_item(&(player->bullets), j));
    double dy = b->dy;
    double dx = b->dx;
    double c = b->c; //findC(dy, dx, b->y, b->x);
    //printf("dy %f dx %f\n", dy, dx);
    printf("y = %fx + %f\n", b->m, c);
    for(int i = 0; i < arena->rocks.size; i++)
    {
      Asteroid* rock = vector_item(&(arena->rocks), i);
      for(int k = 0; k < ROCKNODES; k++)
      {
        int l = k+1;
        if(k == ROCKNODES-1)
          l = 0;
        int pt1y = rock->yposns[k];
        int pt1x = rock->xposns[k];
        int pt2y = rock->yposns[l];
        int pt2x = rock->xposns[l];
        double nodec = findC(pt1y - pt2y, pt1x - pt2x, pt1y, pt1x);

        // Solve as simultaneous equations for X and Y
        // allowing for cases where dx == 0
      }
    }
  }
  return false;
}


