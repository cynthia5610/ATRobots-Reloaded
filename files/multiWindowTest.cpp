#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <sstream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
void close();

SDL_Window *window = NULL;
SDL_Renderer *render = NULL;
SDL_Texture *texture = NULL;
SDL_Surface *surface = NULL;