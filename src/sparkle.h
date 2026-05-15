#ifndef _SPARKLE_H_
#define _SPARKLE_H_

#include <SDL2/SDL.h>

typedef struct
{
  int x;
  int y;
  Uint16 alpha;
  Uint32 r;
  int dx;
  int dy;
	double displacement;
	double speed;
} Sparkle;

#endif
