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

// Returns true if level complete
bool arena_checkbullets(Arena* arena, Ship* player)
{
  // Check each bullet for a collision against each rock
	// We were going to be clever and do this with the intersections of lines
	// but that raised more issues than it solved, so we'll use a simple bounding 
	// circle, slightly within the perimeter of the asteroid
  
  // For each rock...
  for(int i = arena->rocks.size - 1; i >= 0; i--)
  {
    Asteroid* rock = vector_item(&(arena->rocks), i);
    /// ... and each bullet
    for(int j = player->bullets.size - 1; j >= 0; j--)
    {
      Bullet* bullet = vector_item(&(player->bullets), j);
      // Is the bullet within the bounding circle of the rock?
      double xs = (bullet->x - rock->x);
      xs = xs * xs;
      double ys = (bullet->y - rock->y);
      ys = ys * ys;
      double rs = rock->scale * ROCKRADIUS;
//      printf("Testing %d, %d\n", xs+ys, rs*rs);
      if ((xs + ys) <= (rs * rs))
      {
        // If a collision occurs, remove this bullet
        // do whatever is needed to the rock, and continue 
        // to the next bullet / rock
        vector_remove(&(player->bullets), bullet);
        free(bullet);
        
        if(rock->size == rsLarge)
        {
          Asteroid* newrock = rock_create(rock->x, rock->y, rsMedium);
          vector_add(&(arena->rocks), newrock);
          newrock = rock_create(rock->x, rock->y, rsMedium);
          vector_add(&(arena->rocks), newrock);
        }
        else if(rock->size == rsMedium)
        {
          Asteroid* newrock = rock_create(rock->x, rock->y, rsSmall);
          vector_add(&(arena->rocks), newrock);
          newrock = rock_create(rock->x, rock->y, rsSmall);
          vector_add(&(arena->rocks), newrock);
        }

        // Remove original rock
        vector_remove(&(arena->rocks), rock);
      }
    }
  }
  return arena->rocks.size == 0;
}


