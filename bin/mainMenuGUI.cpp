#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "atrrfunc.hh"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

void runGraphics();
void drawBackground();
void drawTitleBox();
void drawRobots();
void settingCycle();
const char *scanArcs();
const char *showSource();
const char *disGraphics();
const char *quietMode();
const char *compileOnly();
const char *matchesPlay();
const char *gameDelay();
const char *gameTime();
const char *robotTime();
void drawQuitPlay();
string readInDigit(int n);
void updateDigit(string here, int which);

bool init();
bool loadMedia();
void close();
SDL_Texture *imageTexture(std::string fPath);

SDL_Color white = {255, 255, 255};
SDL_Color black = {0, 0, 0};
SDL_Color red = {255, 0, 0};
const int WWIDTH = 1000;
const int WHEIGHT = 600;

SDL_Texture *texture = NULL;
SDL_Window *window = NULL;
SDL_Renderer *render = NULL;
SDL_Surface *surface = NULL;

TTF_Font *font1 = NULL;
TTF_Font *font2 = NULL;

bool scArcs = true;
bool shSource = false;
bool disGraph = false;
bool quMode = false;
bool compOnly = false;
string matPlay = "Default";
string gaDelay = "Default";
string gaTime = "     16";
string robTime = "Default";

int mTP = 0;
int gD = 0;
int gT = 16;
int rT = 0;

int main(int argc, char *argv[])
{
    runGraphics();
    return 0;
}

void runGraphics()
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
            SDL_Event e;
            bool quit = false;

            font1 = TTF_OpenFont("Averia.ttf", 100);
            font2 = TTF_OpenFont("Averia.ttf", 38);

            int x = 0;
            int y = 0;

            drawBackground();
            drawTitleBox();
            drawRobots();
            settingCycle();
            SDL_RenderPresent(render);

            while (!quit)
            {

                while (SDL_PollEvent(&e) != 0)
                {

                    SDL_GetMouseState(&x, &y);

                    if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        close();
                        quit = true;
                    }
                    //Robot 1
                    else if (x >= 25 && x <= 82 && y >= 102 && y <= 133)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 1 Pressed" << std::endl;
                            }
                        }
                    }
                    //Robot 2
                    else if (x >= 25 && x <= 82 && y >= 172 && y <= 203)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 2 Pressed" << std::endl;
                            }
                        }
                    }
                    //Robot 3
                    else if (x >= 25 && x <= 82 && y >= 242 && y <= 273)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 3 Pressed" << std::endl;
                            }
                        }
                    }
                    //Robot 4
                    else if (x >= 525 && x <= 582 && y >= 102 && y <= 133)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 4 Pressed" << std::endl;
                            }
                        }
                    }
                    //Robot 5
                    else if (x >= 525 && x <= 582 && y >= 172 && y <= 203)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 5 Pressed" << std::endl;
                            }
                        }
                    }
                    //Robot 6
                    else if (x >= 525 && x <= 582 && y >= 242 && y <= 273)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 6 Pressed" << std::endl;
                            }
                        }
                    }
                    //Show scan arcs
                    else if (x >= 30 && x <= 72 && y >= 340 && y <= 375)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Show scan arcs pressed" << std::endl;
                                scArcs = !scArcs;
                                settingCycle();
                                SDL_RenderPresent(render);
                            }
                        }
                    }
                    //Show source
                    else if (x >= 30 && x <= 72 && y >= 385 && y <= 420)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Show source pressed" << std::endl;
                                shSource = !shSource;
                                settingCycle();
                                SDL_RenderPresent(render);
                            }
                        }
                    }
                    //Disable graphics
                    else if (x >= 30 && x <= 72 && y >= 430 && y <= 465)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Disable graphics pressed" << std::endl;
                                disGraph = !disGraph;
                                settingCycle();
                                SDL_RenderPresent(render);
                            }
                        }
                    }
                    //Quiet mode
                    else if (x >= 30 && x <= 72 && y >= 475 && y <= 510)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Quiet mode pressed shhhh" << std::endl;
                                quMode = !quMode;
                                settingCycle();
                                SDL_RenderPresent(render);
                            }
                        }
                    }
                    //Compile only
                    else if (x >= 30 && x <= 72 && y >= 520 && y <= 555)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Compile only pressed" << std::endl;
                                compOnly = !compOnly;
                                settingCycle();
                                SDL_RenderPresent(render);
                            }
                        }
                    }
                    //Matches to play
                    else if (x >= 480 && x <= 522 && y >= 340 && y <= 375)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Matches to play pressed" << std::endl;
                                mTP = atoi(readInDigit(1).c_str());
                                cout << mTP << endl;
                                settingCycle();
                                SDL_RenderPresent(render);
                            }
                        }
                    }
                    //Game Delay
                    else if (x >= 480 && x <= 522 && y >= 385 && y <= 420)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Game Delay pressed" << std::endl;
                                gD = atoi(readInDigit(2).c_str());
                                cout << gD << endl;
                                settingCycle();
                                SDL_RenderPresent(render);
                            }
                        }
                    }
                    //Game Time-Limit
                    else if (x >= 480 && x <= 522 && y >= 430 && y <= 465)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Game Time-Limit pressed" << std::endl;
                                gT = atoi(readInDigit(3).c_str());
                                cout << gT << endl;
                                settingCycle();
                                SDL_RenderPresent(render);
                            }
                        }
                    }
                    //Robot Time-Slice
                    else if (x >= 480 && x <= 522 && y >= 475 && y <= 510)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot Time-Slice pressed" << std::endl;
                                rT = atoi(readInDigit(4).c_str());
                                cout << rT << endl;
                                settingCycle();
                                SDL_RenderPresent(render);
                            }
                        }
                    }
                    //Quit button
                    else if (x >= 50 && x <= 460 && y >= 562 && y <= 587)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "We Quitting" << std::endl;
                                close();
                                quit = true;
                            }
                        }
                    }
                    //Play button
                    else if (x >= 540 && x <= 950 && y >= 562 && y <= 587)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "You boutta get stomped." << std::endl;
                            }
                        }
                    }
                }
            }
        }
    }
}

/*
----- DRAW SHAPES -----
*/
void drawBackground()
{
    SDL_SetRenderDrawColor(render, 172, 172, 172, 255);
    SDL_Rect temp;
    temp.x = 0;
    temp.y = 0;
    temp.w = 1000;
    temp.h = 600;

    SDL_RenderFillRect(render, &temp);
}

void drawTitleBox()
{
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_Rect titleBox;
    titleBox.x = 5;
    titleBox.y = 5;
    titleBox.w = 990;
    titleBox.h = 70;

    SDL_Rect titleText;
    titleText.x = 230;
    titleText.y = 15;
    titleText.w = 540;
    titleText.h = 50;

    SDL_RenderFillRect(render, &titleBox);

    surface = TTF_RenderText_Solid(font1, "AT-Robots Reloaded", white);
    texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_RenderCopy(render, texture, NULL, &titleText);
    SDL_FreeSurface(surface);
}

void drawRobots()
{
    const char *robNum;
    int half = 0;
    int height = 0;
    for (int i = 0; i < 6; i++)
    {
        if (i == 3)
        {
            half = 500;
            height = 0;
        }
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_Rect temp;
        temp.x = 90 + half;
        temp.y = 90 + (70 * height);
        temp.w = 385;
        temp.h = 55;

        SDL_Rect temp2;
        temp2.x = 45 + half;
        temp2.y = 102 + (70 * height);
        temp2.w = 37;
        temp2.h = 31;

        SDL_Rect temp3;
        temp3.x = 8 + half;
        temp3.y = 102 + (70 * height);
        temp3.w = 12;
        temp3.h = 31;

        SDL_Rect temp4;
        temp4.x = 50 + half;
        temp4.y = 107 + (70 * height);
        temp4.w = 15;
        temp4.h = 21;
        switch (i)
        {
        case 0:
            robNum = "1";
            break;
        case 1:
            robNum = "2";
            break;
        case 2:
            robNum = "3";
            break;
        case 3:
            robNum = "4";
            break;
        case 4:
            robNum = "5";
            break;
        case 5:
            robNum = "6";
            break;
        }
        SDL_RenderFillRect(render, &temp);
        SDL_RenderDrawRect(render, &temp2);
        SDL_RenderDrawRect(render, &temp3);
        SDL_RenderDrawLine(render, 13 + half, 109 + (70 * height), 13 + half, 126 + (70 * height));
        surface = TTF_RenderText_Solid(font1, "R", black);
        texture = SDL_CreateTextureFromSurface(render, surface);
        SDL_RenderCopy(render, texture, NULL, &temp4);
        SDL_FreeSurface(surface);
        surface = TTF_RenderText_Solid(font1, robNum, red);
        texture = SDL_CreateTextureFromSurface(render, surface);
        temp4.x = 60 + half;
        SDL_RenderCopy(render, texture, NULL, &temp4);
        SDL_FreeSurface(surface);
        height++;
    }
}

void settingCycle()
{
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_Rect lowerHalf;
    lowerHalf.x = 5;
    lowerHalf.y = 332;
    lowerHalf.w = 990;
    lowerHalf.h = 263;

    SDL_RenderFillRect(render, &lowerHalf);

    SDL_SetRenderDrawColor(render, 172, 172, 172, 255);

    int half = 0;
    int height = 0;
    int spHalf = 0;
    const char *button;
    const char *setting;
    const char *option;
    for (int i = 0; i < 9; i++)
    {
        if (i == 5)
        {
            spHalf = 500;
            half = 450;
            height = 0;
        }
        SDL_Rect temp;
        temp.x = 30 + half;
        temp.y = 340 + (45 * height);
        temp.w = 42;
        temp.h = 35;

        SDL_RenderFillRect(render, &temp);

        switch (i)
        {
        case 0:
            button = "A";
            setting = "Show scan arcs:   ";
            option = scanArcs();
            break;
        case 1:
            button = "S";
            setting = "Show source:      ";
            option = showSource();
            break;
        case 2:
            button = "G";
            setting = "Disable Graphics: ";
            option = disGraphics();
            break;
        case 3:
            button = "Q";
            setting = "Quiet mode:       ";
            option = quietMode();
            break;
        case 4:
            button = "C";
            setting = "Compile only:     ";
            option = compileOnly();
            break;
        case 5:
            button = "M";
            setting = "Matches to play:  ";
            //option = addfront(const_cast<char*>(matPlay.c_str()), 7);
            option = matPlay.c_str();
            break;
        case 6:
            button = "D";
            setting = "Game Delay:       ";
            option = gaDelay.c_str();
            break;
        case 7:
            button = "L";
            setting = "Game Time-Limit:  ";
            option = gaTime.c_str();
            break;
        case 8:
            button = "T";
            setting = "Robot Time-Slice: ";
            option = robTime.c_str();
            break;
        }

        SDL_Rect temp2;
        temp2.x = 40 + half;
        temp2.y = 342 + (45 * height);
        temp2.w = 22;
        temp2.h = 31;

        surface = TTF_RenderText_Solid(font1, button, red);
        texture = SDL_CreateTextureFromSurface(render, surface);
        SDL_RenderCopy(render, texture, NULL, &temp2);
        SDL_FreeSurface(surface);

        SDL_Rect temp3;
        temp3.x = 80 + half;
        temp3.y = 342 + (45 * height);
        temp3.w = 250;
        temp3.h = 31;

        surface = TTF_RenderText_Solid(font1, setting, white);
        texture = SDL_CreateTextureFromSurface(render, surface);
        SDL_RenderCopy(render, texture, NULL, &temp3);
        SDL_FreeSurface(surface);

        SDL_Rect temp4;
        temp4.x = 335 + spHalf;
        temp4.y = 342 + (45 * height);
        temp4.w = 100;
        temp4.h = 31;

        surface = TTF_RenderText_Solid(font1, option, white);
        texture = SDL_CreateTextureFromSurface(render, surface);
        SDL_RenderCopy(render, texture, NULL, &temp4);
        SDL_FreeSurface(surface);

        height++;
    }
    drawQuitPlay();
}

const char *scanArcs()
{
    if (scArcs == true)
    {
        return "Yes     ";
    }
    else
    {
        return "No      ";
    }
}
const char *showSource()
{
    if (shSource == true)
    {
        return "Yes     ";
    }
    else
    {
        return "No      ";
    }
}

const char *disGraphics()
{
    if (disGraph == true)
    {
        return "Yes     ";
    }
    else
    {
        return "No      ";
    }
}

const char *quietMode()
{
    if (quMode == true)
    {
        return "Yes     ";
    }
    else
    {
        return "No      ";
    }
}

const char *compileOnly()
{
    if (compOnly == true)
    {
        return "Yes     ";
    }
    else
    {
        return "No      ";
    }
}

/* const char *matchesPlay(){

}

const char *gameDelay(){

}

const char *gameTime(){

}

const char *robotTime(){

} */

string readInDigit(int n)
{
    SDL_Event e;
    string inputNumbers;
    bool leave = false;
    while (!leave)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_RETURN)
            {
                leave = true;
                return inputNumbers;
            }
            if (e.type == SDL_TEXTINPUT && e.key.keysym.sym != SDLK_BACKSPACE)
            {
                inputNumbers += e.text.text;
                updateDigit(inputNumbers, n);
            }
            if (e.key.keysym.sym == SDLK_BACKSPACE)
            {
                if (e.type == SDL_KEYDOWN)
                {
                    inputNumbers = inputNumbers.substr(0, inputNumbers.size() - 1);
                    updateDigit(inputNumbers, n);
                    cout << "running once" << endl;
                }
            }
        }
    }
}

void updateDigit(string here, int which)
{
    string tempHere = here;
    for (int i = tempHere.length(); i < 7; i++)
    {
        tempHere = " " + tempHere;
    }
    switch (which)
    {
    case 1:
        matPlay = tempHere.c_str();
        break;
    case 2:
        gaDelay = tempHere.c_str();
        break;
    case 3:
        gaTime = tempHere.c_str();
        break;
    case 4:
        robTime = tempHere.c_str();
        break;
    }
    settingCycle();
    SDL_RenderPresent(render);
}

void drawQuitPlay()
{
    SDL_Rect temp;
    temp.x = 50;
    temp.y = 562;
    temp.w = 410;
    temp.h = 25;

    SDL_Rect temp2;
    temp2.x = 230;
    temp2.y = 560;
    temp2.w = 50;
    temp2.h = 27;

    SDL_Rect temp3;
    temp3.x = 540;
    temp3.y = 562;
    temp3.w = 410;
    temp3.h = 25;

    SDL_Rect temp4;
    temp4.x = 720;
    temp4.y = 562;
    temp4.w = 12;
    temp4.h = 25;

    SDL_Rect temp5;
    temp5.x = 732;
    temp5.y = 562;
    temp5.w = 38;
    temp5.h = 25;

    SDL_SetRenderDrawColor(render, 172, 172, 172, 255);
    SDL_RenderFillRect(render, &temp);

    surface = TTF_RenderText_Solid(font1, "Quit", black);
    texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_RenderCopy(render, texture, NULL, &temp2);

    SDL_RenderFillRect(render, &temp3);

    surface = TTF_RenderText_Solid(font1, "P", red);
    texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_RenderCopy(render, texture, NULL, &temp4);

    surface = TTF_RenderText_Solid(font1, "lay", black);
    texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_RenderCopy(render, texture, NULL, &temp5);
    SDL_FreeSurface(surface);
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
