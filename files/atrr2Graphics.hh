#ifndef __ATRR2GRAPHICS_HH__
#define __ATRR2GRAPHICS_HH__

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <climits>

#include "types.hh"
#include "atrrfunc.hh"
#include "filelib.hh"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

extern void runGraphics();
extern void setColor(int h);
extern void drawTriangles();
extern void robotStats();
extern bool validatePos(int robPosX[], int robPosY[], int currentLoaded);

extern bool init();
extern bool loadMedia();
extern void close();
extern SDL_Texture *imageTexture(std::string fPath);

#endif
