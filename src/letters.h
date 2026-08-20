#ifndef _LETTERS_H_
#define _LETTERS_H_

#include <SDL2/SDL2_gfxPrimitives.h>

typedef struct { int x; int y; } Point;

// UPPERCASE
static const Point lA[3] = {{0,4},{1,0},{2,4}};
static const Point lB[8] = {{0,0},{1,0},{2,1},{1,2},{2,3},{1,4},{0,4},{0,0}};
static const Point lC[4] = {{2,0},{0,0},{0,4},{2,4}};
static const Point lD[7] = {{0,0},{1,0},{2,1},{2,3},{1,4},{0,4},{0,0}};
static const Point lE[7] = {{2,4},{0,4},{0,2},{1,2},{0,2},{0,0},{2,0}};
static const Point lF[6] = {{0,4},{0,2},{1,2},{0,2},{0,0},{2,0}};
static const Point lG[6] = {{1,2},{2,2},{2,4},{0,4},{0,0},{2,0}};
static const Point lH[6] = {{0,0},{0,4},{0,2},{2,2},{2,0},{2,4}};
static const Point lI[2] = {{1,0},{1,4}};
static const Point lJ[5] = {{0,3},{1,4},{2,3},{2,0},{1,0}};
static const Point lK[7] = {{0,0},{0,4},{0,2},{1,2},{2,0},{1,2},{2,4}};
static const Point lL[3] = {{0,0},{0,4},{2,4}};
static const Point lM[5] = {{0,4},{0,0},{1,2},{2,0},{2,4}};
static const Point lN[4] = {{0,4},{0,0},{2,4},{2,0}};
static const Point lO[5] = {{0,0},{2,0},{2,4},{0,4},{0,0}};
static const Point lP[5] = {{0,4},{0,0},{2,0},{2,2},{0,2}};
static const Point lQ[6] = {{1,2},{2,4},{0,4},{0,0},{2,0},{2,4}};
static const Point lR[6] = {{0,4},{0,0},{2,0},{2,2},{1,2},{2,4}};
static const Point lS[6] = {{0,4},{2,4},{2,2},{0,2},{0,0},{2,0}};
static const Point lT[4] = {{0,0},{2,0},{1,0},{1,4}};
static const Point lU[4] = {{0,0},{0,4},{2,4},{2,0}};
static const Point lV[3] = {{0,0},{1,4},{2,0}};
static const Point lW[5] = {{0,0},{0,4},{1,2},{2,4},{2,0}};
static const Point lX[5] = {{0,0},{2,4},{1,2},{0,4},{2,0}};
static const Point lY[7] = {{0,0},{1,2},{2,2},{2,0},{2,4},{1,4},{0,3}};
static const Point lZ[8] = {{0,0},{2,0},{1,2},{2,2},{0,2},{1,2},{0,4},{2,4}};
// LOWERCASE
static const Point la[6] = {{0,1},{2,1},{2,3},{0,3},{0,2},{2,2}};
static const Point lb[5] = {{0,0},{0,3},{2,3},{2,1},{0,1}};
static const Point lc[4] = {{2,1},{0,1},{0,3},{2,3}};
static const Point ld[5] = {{2,0},{2,3},{0,3},{0,1},{2,1}};
static const Point le[6] = {{0,2},{2,2},{2,1},{0,1},{0,3},{2,3}};
static const Point lf[6] = {{2,1},{0,1},{0,2},{1,2},{0,2},{0,4}};
static const Point lg[6] = {{0,4},{2,4},{2,1},{0,1},{0,3},{2,3}};
static const Point lh[5] = {{0,0},{0,3},{0,1},{2,1},{2,3}};
static const Point li[3] = {{1,1},{1,3},{-1, 0}};
static const Point lj[3] = {{1,1},{1,3},{0,4}};
static const Point lk[6] = {{0,0},{0,3},{0,2},{2,0},{1,1},{2,3}};
static const Point ll[3] = {{1,0},{1,3},{2,3}};
static const Point lm[5] = {{0,3},{0,1},{1,2},{2,1},{2,3}};
static const Point ln[5] = {{0,3},{0,1},{1,1},{2,2},{2,3}};

typedef struct {
  int size;
  const Point* points;
} Letter;

static const Letter alphabet[40] = {{3, lA}, {8, lB}, {4, lC}, {7, lD}, {7, lE}, 
																		{6, lF}, {6, lG}, {6, lH}, {2, lI}, {5, lJ}, 
																		{7, lK}, {3, lL}, {5, lM}, {4, lN}, {5, lO},
																		{5, lP}, {6, lQ}, {6, lR}, {6, lS}, {4, lT},
																		{4, lU}, {3, lV}, {5, lW}, {5, lX}, {7, lY}, 
																		{8, lZ}, {6, la}, {5, lb}, {4, lc}, {5, ld},
																		{6, le}, {6, lf}, {6, lg}, {5, lh}, {3, li},
																		{3, lj}, {6, lk}, {3, ll}, {5, lm}, {5, ln}};

void letters_draw(SDL_Renderer* renderer, int ordchar, int scale, int x, int y); 
void letters_drawSentence(SDL_Renderer* renderer, char* sentence, int scale, int x, int y);

#endif
