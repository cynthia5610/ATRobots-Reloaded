#ifndef __MAINMENUGUI_HH__
#define __MAINMENUGUI_HH__

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

extern void runGraphics();
extern void drawBackground();
extern void drawTitleBox();
extern void drawRobots();
extern void settingCycle();
extern const char *scanArcs();
extern const char *showSource();
extern const char *disGraphics();
extern const char *quietMode();
extern const char *compileOnly();
extern const char *matchesPlay();
extern const char *gameDelay();
extern const char *gameTime();
extern const char *robotTime();
extern void drawQuitPlay();
extern string readInDigit(int n);
extern void updateDigit(string here, int which);
extern string loadRobotName(string rName, int rNumber);
extern string robotName(int which);
extern string updateRobotName(string rName);
extern void robotReset(int which);
extern void robotModify(int which);
extern void robotPrintButtons();
extern bool statChecker();
extern bool init();
extern bool loadMedia();
extern void close();

#endif
