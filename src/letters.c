#include "letters.h"

void letters_draw(SDL_Renderer* renderer, int ordchar, int scale, int x, int y)
{
  Letter l = alphabet[ordchar];
  for(int i = 0; i < l.size - 1; i++)
  {
		int ix = l.points[i+1].x;
		int iy = l.points[i+1].y;
		// If final point is negative, it's a dot
		if(ix>=0 && iy>=0)
	    thickLineRGBA(renderer, x + (l.points[i].x * scale), y + (l.points[i].y * scale), x + (l.points[i+1].x * scale), y + (l.points[i+1].y * scale), 2, 255, 255, 255, 255);
		else
		{
			filledCircleRGBA(renderer, x + ((-1 * ix) * scale), y + ((-1 * iy) * scale), 1, 255, 255, 255, 255);
		}
  }
  //Point p = 
  //polygonRGBA(renderer, 
}

void letters_drawSentence(SDL_Renderer* renderer, char* sentence, int scale, int x, int y)
{
  int spacing = 3 * scale;
  int i = 0;

  while(sentence[i] > 0)
  {
		int ordchar = (int)sentence[i];
		if(ordchar < 91)
			ordchar -= 65;
		else
			ordchar -= 71;

    letters_draw(renderer, ordchar, scale, x + (i*spacing), y);
    i++;
  }
}
