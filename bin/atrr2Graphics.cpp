#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <climits> //FOR INT_MAX

#include "types.hh"
#include "atrrfunc.hh"
#include "filelib.hh"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

void graph_mode(bool on);
void toggle_graphix();
bool graph_check();
void robot_graph();
void update_armor();
void update_heat();
void update_lives();
void update_cycle_window();
void setscreen();
void draw_robot(int n);
void begin_window(); //starts up window

void setColor(int h);
void drawTriangles();
void robotStats();
bool validatePos(int robPosX[], int robPosY[], int currentLoaded);

bool init();
bool loadMedia();
void close();
SDL_Texture *imageTexture(std::string fPath);

SDL_Color white = {255, 255, 255};
string robotTest = "Testing";
const int WWIDTH = 1280;
const int WHEIGHT = 720;
int numRobots = 36;
bool runTriangles = true;

SDL_Texture *texture = NULL;
SDL_Window *window = NULL;
SDL_Renderer *render = NULL;
SDL_Surface *surface = NULL;


int main(int argc, char *args[])
{
    if (!init())
    {
        std::cout << "Failed to Initialize" << endl;
    }
    else
    {
        if (!loadMedia())
        {
            std::cout << "Failed to initialize" << endl;
        }
        else
        {
            bool quit = false;

            SDL_Event e;

            SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
            SDL_Rect test;
            test.x = 20;
            test.y = 13;
            test.h = 694;
            test.w = 694;

            SDL_RenderDrawRect(render, &test);

            if (runTriangles == true)
            {
                drawTriangles();
            }

            robotStats();

            SDL_RenderPresent(render);

            while (!quit)
            {

                while (SDL_PollEvent(&e) != 0)
                {

                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }
            }
        }
    }
}

void drawTriangles()
{
    int positionX[numRobots];
    int positionY[numRobots];
    srand(time(NULL));

    for (int i = 0; i < numRobots; i++)
    {
        bool validPos = false;
        while (validPos == false)
        {
            
            positionX[i] = rand() % 650;
            positionY[i] = rand() % 650;
            cout << positionX[i] << endl;
            cout << positionY[i] << endl;
            if (validatePos(positionX, positionY, i) == true)
            {
                setColor(i);
                SDL_RenderDrawLine(render, positionX[i] + 30, positionY[i] + 18, positionX[i] + 25, positionY[i] + 28);
                SDL_RenderDrawLine(render, positionX[i] + 30, positionY[i] + 18, positionX[i] + 35, positionY[i] + 28);
                SDL_RenderDrawLine(render, positionX[i] + 25, positionY[i] + 28, positionX[i] + 35, positionY[i] + 28);
                cout << "in while loop" << endl;
                validPos = true;
            }
        }
        cout << i << endl;
    }
    runTriangles = false;
}

void setColor(int h){
    switch(h){
        case 0: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;             // #873600 Brown
        case 1: SDL_SetRenderDrawColor(render, 20, 90, 50, 255); break;             // #145a32 Dark Green
        case 2: SDL_SetRenderDrawColor(render, 86, 101, 115, 255); break;           // #566573 Medium Gray
        case 3: SDL_SetRenderDrawColor(render, 91, 44, 111, 255); break;            // #5b2c6f Dark Purple
        case 4: SDL_SetRenderDrawColor(render, 211, 84, 0, 255); break;             // #D35400 Medium Orange
        case 5: SDL_SetRenderDrawColor(render, 69, 179, 157, 255); break;           // #45B39D Cyan
        case 6: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;             // #873600 Brown
        case 7: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;             // #873600 Brown
        case 8: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;             // #873600 Brown
        case 9: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;             // #873600 Brown
        case 10: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 11: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 12: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 13: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 14: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 15: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 16: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 17: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 18: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 19: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 20: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 21: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 22: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 23: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 24: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 25: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 26: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 27: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 28: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 29: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 30: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 31: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 32: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 33: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 34: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        case 35: SDL_SetRenderDrawColor(render, 135, 54, 0, 255); break;            // #873600 Brown
        
    }
}

void robotStats(){
    SDL_Rect stats;
    TTF_Font *font = TTF_OpenFont("Averia.ttf", 32);
    int half = 0;
    int l = 0;
    for(int s = 0; s < numRobots; s++){
        if (s == 18){
            half = 275;
            l = 0;
        }

        stats.x = 747 + half;
        stats.y = 22 + 38 * l;
        stats.w = 225;
        stats.h = 35;
        setColor(s);
        SDL_RenderDrawRect(render, &stats);
        surface = TTF_RenderText_Solid(font, robotTest.c_str(), white);
        texture = SDL_CreateTextureFromSurface(render, surface);
        SDL_RenderCopy(render, texture, NULL, &stats);
        l++;
    }
}


bool validatePos(int robPosX[], int robPosY[], int currentLoaded)
{
    bool tempC = true;
    if (currentLoaded == 0)
    {
        return true;
    }
    else
    {
        for (int x = 0; x < currentLoaded; x++)
        {
            if (robPosX[x] - robPosX[currentLoaded] <= 15 && robPosX[x] - robPosX[currentLoaded] >= -15 && robPosY[x] - robPosY[currentLoaded] <= 15 && robPosY[x] - robPosY[currentLoaded] >= -15)
            {
                return false;
            }
            cout << "in for loop" << endl;
        }
        return true;
    }
}

/*
----- GRAPHICS FUNCTIONS ----
*/

bool init()
{
    bool success = true;

    TTF_Init();
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        window = SDL_CreateWindow("ATRobots Reloaded", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WWIDTH, WHEIGHT, 0);
        if (window == NULL)
        {
            std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                std::cout << "SDL_image Error:" << IMG_GetError() << std::endl;
                success = false;
            }

            render = SDL_CreateRenderer(window, -1, 0);
            if (render == NULL)
            {
                std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
                success = false;
            }
        }
    }
    return success;
}

bool loadMedia()
{
    return true;
}

void close()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture *imageTexture(std::string fPath)
{
    SDL_Texture *nTexture = NULL;

    SDL_Surface *loadedSurface = IMG_Load(fPath.c_str());
    if (loadedSurface == NULL)
    {
        std::cout << "Unable to load image " << fPath << "! SDL_Image Error " << SDL_GetError() << std::endl;
    }
    else
    {
        nTexture = SDL_CreateTextureFromSurface(render, loadedSurface);
        if (nTexture == NULL)
        {
            std::cout << "Unable to create texture from " << fPath << "! SDL Error " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(loadedSurface);
    }

    return nTexture;
}

void graph_mode(bool on)
{
    return;
}

void toggle_graphix()
{
    //	graph_mode(!graphix);
    //	if(!graphix)
    //    {
    //		cout << "Match " << played << "/" << matches << ", Battle in progress..." << endl;
    //	}
    return;
}

bool graph_check(int n)
{
    return false; // Set to false to not use graphics
}

void robot_graph(int n)
{
    return;
}

void update_armor(int n)
{
    return;
}

void update_heat(int n)
{
    return;
}

void update_lives(int n)
{
    return;
}

void update_cycle_window()
{
    //    if(!graphix)
    //    {
    //    cout << "\r" << "Match " << played << "/" << matches << ", Cycle: " << zero_pad(game_cycle,9);
    //    }
    //    else
    //    {
    //        cout << endl;
    //    }
    //    return;
}

void setscreen()
{
    return;
}

void draw_robot(int n)
{
    return;
}

void begin_window()
{
    setscreen();
    return;
}