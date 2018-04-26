#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "atrrfunc.hh"
#include "mainMenuGUI.hh"

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
string loadRobotName(string rName, int rNumber);
string robotName(int which);
string updateRobotName(string rName);
void robotReset(int which);
void robotModify(int which);
void robotPrintButtons();
bool statChecker();

bool init();
bool loadMedia();
void close();
SDL_Texture *imageTexture(std::string fPath);

SDL_Color white = {255, 255, 255};
SDL_Color gray = {172, 172, 172};
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

string rStatEdit[7] = {"Scanner  ", "Weapon   ", "Armor    ", "Engine   ", "Heatsinks", "Mines    ", "Shield   "};
int statChanger[7] = {0, 0, 0, 0, 0, 0, 0};
string robotOffID[6];
string robotDisplay[6];

// int main(int argc, char *argv[])
// {
//     runGraphics();
// }

void runGraphics()
{
    cout << "in Menu!" << endl;
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
            cout << "at event" << endl;
            SDL_Event e;
            bool quit = false;

            font1 = TTF_OpenFont("Averia.ttf", 100);
            font2 = TTF_OpenFont("Averia.ttf", 38);
            bool depressed = false;
            int x = 0;
            int y = 0;

            cout << "Going into draw background" << endl;
            drawBackground();
            cout << "Going into title box" << endl;
            drawTitleBox();
            cout << "Going into draw robots" << endl;
            drawRobots();
            cout << "Going into setting" << endl;
            settingCycle();
            cout << "Going into render" << endl;
            SDL_RenderPresent(render);
            while (!quit)
            {
                cout << "in while loop" << endl;

                while (SDL_PollEvent(&e) != 0)
                {
                    SDL_GetMouseState(&x, &y);
                    if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        close();
                        quit = true;
                    }
                    //Robot 1
                    else if (x >= 45 && x <= 82 && y >= 102 && y <= 133)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 1 Pressed" << std::endl;
                                robotOffID[0] = robotName(0);
                            }
                        }
                    }
                    //Robot 2
                    else if (x >= 45 && x <= 82 && y >= 172 && y <= 203)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 2 Pressed" << std::endl;
                                robotOffID[1] = robotName(1);
                            }
                        }
                    }
                    //Robot 3
                    else if (x >= 45 && x <= 82 && y >= 242 && y <= 273)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 3 Pressed" << std::endl;
                                robotOffID[2] = robotName(2);
                            }
                        }
                    }
                    //Robot 4
                    else if (x >= 545 && x <= 582 && y >= 102 && y <= 133)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 4 Pressed" << std::endl;
                                robotOffID[3] = robotName(3);
                            }
                        }
                    }
                    //Robot 5
                    else if (x >= 545 && x <= 582 && y >= 172 && y <= 203)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 5 Pressed" << std::endl;
                                robotOffID[4] = robotName(4);
                            }
                        }
                    }
                    //Robot 6
                    else if (x >= 545 && x <= 582 && y >= 242 && y <= 273)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 6 Pressed" << std::endl;
                                robotOffID[4] = robotName(4);
                            }
                        }
                    }
                    //Robot 1 Remove
                    else if (x >= 8 && x <= 40 && y >= 102 && y <= 115)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 1 Removed" << std::endl;
                                robotReset(0);
                            }
                        }
                    }
                    //Robot 2 Remove
                    else if (x >= 8 && x <= 40 && y >= 172 && y <= 185)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 2 Removed" << std::endl;
                                robotReset(1);
                            }
                        }
                    }
                    //Robot 3 Remove
                    else if (x >= 8 && x <= 40 && y >= 242 && y <= 255)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 3 Removed" << std::endl;
                                robotReset(2);
                            }
                        }
                    }
                    //Robot 4 Remove
                    else if (x >= 508 && x <= 540 && y >= 102 && y <= 115)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 4 Removed" << std::endl;
                                robotReset(3);
                            }
                        }
                    }
                    //Robot 5 Remove
                    else if (x >= 508 && x <= 540 && y >= 172 && y <= 185)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 5 Removed" << std::endl;
                                robotReset(4);
                            }
                        }
                    }
                    //Robot 6 Remove
                    else if (x >= 508 && x <= 540 && y >= 242 && y <= 255)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 6 Removed" << std::endl;
                                robotReset(5);
                            }
                        }
                    }
                    //Robot 1 Edit
                    else if (x >= 8 && x <= 40 && y >= 117 && y <= 130)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 1 Edited" << std::endl;
                                robotModify(0);
                            }
                        }
                    }
                    //Robot 2 Edit
                    else if (x >= 8 && x <= 40 && y >= 187 && y <= 200)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 2 Edited" << std::endl;
                            }
                        }
                    }
                    //Robot 3 Edit
                    else if (x >= 8 && x <= 40 && y >= 257 && y <= 270)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 3 Edited" << std::endl;
                            }
                        }
                    }
                    //Robot 4 Edit
                    else if (x >= 508 && x <= 540 && y >= 117 && y <= 130)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 4 Edited" << std::endl;
                            }
                        }
                    }
                    //Robot 5 Edit
                    else if (x >= 508 && x <= 540 && y >= 187 && y <= 200)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 5 Removed" << std::endl;
                            }
                        }
                    }
                    //Robot 6 Edit
                    else if (x >= 508 && x <= 540 && y >= 257 && y <= 270)
                    {
                        if (e.type == SDL_MOUSEBUTTONUP)
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {
                                std::cout << "Robot 6 Removed" << std::endl;
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
----- DRAW SHAPES AND TEXT -----
*/

/* string loadRobotName(string rName, int rNumber)
{
    int half = 0;
    if (rNumber > 2)
    {
        int half = 500;
        rNumber -= 3;
    }
    SDL_Rect nameSlots;
    nameSlots.x = 95 + half;
    nameSlots.y = 95 + (70 * rNumber);
    nameSlots.w = 390;
    nameSlots.h = 45;


    surface = TTF_RenderText_Solid(font1, rName.c_str(), white);
    texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_RenderCopy(render, texture, NULL, &nameSlots);
    SDL_FreeSurface(surface);

    SDL_RenderPresent(render);
} */

void robotModify(int which)
{
    int x = 0;
    int y = 0;
    robotPrintButtons();
    SDL_Event e;
    bool leave = false;
    while (!leave)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            SDL_GetMouseState(&x, &y);
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
            {
                leave = true;
            }
            else if (x >= 650 && x <= 985 && y >= 485 && y <= 585)
            {
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        cout << "leaving" << endl;
                        leave = true;
                    }
                }
            }
            else if (x >= 330 && x <= 380 && y >= 35 && y <= 85)
            {
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        cout << "stat 1 decreased" << endl;
                        statChanger[0]--;
                        if (statChecker == false)
                        {
                            statChanger[0]++;
                        }
                    }
                }
            }
            else if (x >= 330 && x <= 380 && y >= 115 && y <= 165)
            {
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        cout << "stat 2 decreased" << endl;
                        statChanger[1]++;
                    }
                }
            }
            else if (x >= 330 && x <= 380 && y >= 195 && y <= 245)
            {
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        cout << "stat 3 decreased" << endl;
                        statChanger[2]--;
                    }
                }
            }
            else if (x >= 330 && x <= 380 && y >= 275 && y <= 325)
            {
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        cout << "stat 4 decreased" << endl;
                        statChanger[3]--;
                    }
                }
            }
            else if (x >= 330 && x <= 380 && y >= 355 && y <= 405)
            {
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        cout << "stat 5 decreased" << endl;
                        statChanger[4]--;
                    }
                }
            }
            else if (x >= 330 && x <= 380 && y >= 435 && y <= 485)
            {
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        cout << "stat 6 decreased" << endl;
                        statChanger[5]--;
                    }
                }
            }
            else if (x >= 330 && x <= 380 && y >= 515 && y <= 565)
            {
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        cout << "stat 7 decreased" << endl;
                        statChanger[6]--;
                        robotPrintButtons();
                    }
                }
            }
            else if (x >= 530 && x <= 580 && y >= 35 && y <= 85)
            {
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        cout << "stat 1 increased" << endl;
                        statChanger[0]++;
                    }
                }
            }
            else if (x >= 530 && x <= 580 && y >= 115 && y <= 165)
            {
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        cout << "stat 2 increased" << endl;
                        statChanger[1]++;
                    }
                }
            }
            else if (x >= 530 && x <= 580 && y >= 195 && y <= 245)
            {
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        cout << "stat 3 increased" << endl;
                        statChanger[2]++;
                    }
                }
            }
            else if (x >= 530 && x <= 580 && y >= 275 && y <= 325)
            {
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        cout << "stat 4 increased" << endl;
                        statChanger[3]++;
                    }
                }
            }
            else if (x >= 530 && x <= 580 && y >= 355 && y <= 405)
            {
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        cout << "stat 5 increased" << endl;
                        statChanger[4]++;
                    }
                }
            }
            else if (x >= 530 && x <= 580 && y >= 435 && y <= 485)
            {
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        cout << "stat 6 increased" << endl;
                        statChanger[5]++;
                    }
                }
            }
            else if (x >= 530 && x <= 580 && y >= 515 && y <= 565)
            {
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        cout << "stat 7 increased" << endl;
                        statChanger[6]++;
                        if (statChecker() == false)
                        {
                            statChanger[6]--;
                        }
                        robotPrintButtons();
                    }
                }
            }
        }
    }
}

bool statChecker()
{
    int totalSum;
    totalSum = statChanger[0] + statChanger[1] + statChanger[2] + statChanger[3] + statChanger[4] + statChanger[5] + statChanger[6];
    if (totalSum < 13 && statChanger[0] < 6 && statChanger[1] < 6 && statChanger[2] < 6 && statChanger[3] < 6 && statChanger[4] < 6 && statChanger[5] < 6 && statChanger[6] < 6)
    {
        cout << "returning true" << endl;
        return true;
    }
    else
    {
        cout << "returning false" << endl;
        return false;
    }
}

void robotPrintButtons()
{
    const char *tempStat;
    SDL_Rect clear;
    clear.x = 0;
    clear.y = 0;
    clear.w = 1000;
    clear.h = 600;
    SDL_SetRenderDrawColor(render, 172, 172, 172, 255);
    SDL_RenderFillRect(render, &clear);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    for (int i = 0; i < 7; i++)
    {
        SDL_Rect temp;
        temp.x = 35;
        temp.y = 35 + (80 * i);
        temp.w = 200;
        temp.h = 50;

        SDL_Rect minusBox;
        minusBox.x = 330;
        minusBox.y = 35 + (80 * i);
        minusBox.w = 50;
        minusBox.h = 50;

        SDL_Rect minus;
        minus.x = 335;
        minus.y = 55 + (80 * i);
        minus.w = 40;
        minus.h = 10;

        SDL_Rect numberBox;
        numberBox.x = 430;
        numberBox.y = 35 + (80 * i);
        numberBox.w = 50;
        numberBox.h = 50;

        SDL_Rect plusBox;
        plusBox.x = 530;
        plusBox.y = 35 + (80 * i);
        plusBox.w = 50;
        plusBox.h = 50;

        SDL_Rect plus1;
        plus1.x = 535;
        plus1.y = 55 + (80 * i);
        plus1.w = 40;
        plus1.h = 10;

        SDL_Rect plus2;
        plus2.x = 550;
        plus2.y = 40 + (80 * i);
        plus2.w = 10;
        plus2.h = 40;

        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderFillRect(render, &temp);
        SDL_RenderFillRect(render, &minusBox);
        SDL_RenderFillRect(render, &numberBox);
        SDL_RenderFillRect(render, &plusBox);
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        SDL_RenderFillRect(render, &minus);
        SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
        SDL_RenderFillRect(render, &plus1);
        SDL_RenderFillRect(render, &plus2);
        surface = TTF_RenderText_Solid(font1, rStatEdit[i].c_str(), white);
        texture = SDL_CreateTextureFromSurface(render, surface);
        SDL_RenderCopy(render, texture, NULL, &temp);
        surface = TTF_RenderText_Solid(font1, to_string(statChanger[i]).c_str(), gray);
        texture = SDL_CreateTextureFromSurface(render, surface);
        SDL_RenderCopy(render, texture, NULL, &numberBox);
        SDL_FreeSurface(surface);
    }
    SDL_Rect info1;
    info1.x = 650;
    info1.y = 35;
    info1.w = 180;
    info1.h = 50;

    SDL_Rect info2;
    info2.x = 650;
    info2.y = 115;
    info2.w = 180;
    info2.h = 50;

    SDL_Rect info3;
    info3.x = 880;
    info3.y = 35;
    info3.w = 70;
    info3.h = 50;

    SDL_Rect info4;
    info4.x = 880;
    info4.y = 115;
    info4.w = 70;
    info4.h = 50;

    SDL_Rect rButton;
    rButton.x = 650;
    rButton.y = 485;
    rButton.w = 335;
    rButton.h = 100;
    surface = TTF_RenderText_Solid(font1, "Points Left:", black);
    texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_RenderCopy(render, texture, NULL, &info1);
    surface = TTF_RenderText_Solid(font1, "Points Used:", black);
    texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_RenderCopy(render, texture, NULL, &info2);
    surface = TTF_RenderText_Solid(font1, "12", black);
    texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_RenderCopy(render, texture, NULL, &info3);
    surface = TTF_RenderText_Solid(font1, "0", black);
    texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_RenderCopy(render, texture, NULL, &info4);
    SDL_FreeSurface(surface);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderFillRect(render, &rButton);
    surface = TTF_RenderText_Solid(font1, "Return", gray);
    texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_RenderCopy(render, texture, NULL, &rButton);

    SDL_RenderPresent(render);
}

void robotReset(int which)
{
    for (int i = which; i < 5; i++)
    {
        robotDisplay[i] = robotDisplay[i + 1];
        robotOffID[i] = robotOffID[i + 1];
    }
    robotDisplay[5] = "";
    robotOffID[5] = "";
    drawRobots();
    SDL_RenderPresent(render);
}

string robotName(int which)
{
    SDL_Event e;
    string inputRobotName;
    bool leave = false;
    string compString;
    string editedString;
    while (!leave)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
            {
                leave = true;
                return inputRobotName;
            }
            if (e.type == SDL_TEXTINPUT && e.key.keysym.sym != SDLK_BACKSPACE)
            {
                cout << "getting to here" << endl;
                inputRobotName += e.text.text;
                editedString = updateRobotName(inputRobotName);
                robotDisplay[which] = editedString;
                drawRobots();
                SDL_RenderPresent(render);
            }
            if (e.key.keysym.sym == SDLK_BACKSPACE)
            {
                if (e.type == SDL_KEYDOWN)
                {
                    inputRobotName = inputRobotName.substr(0, inputRobotName.size() - 1);
                    editedString = updateRobotName(inputRobotName);
                    robotDisplay[which] = editedString;
                    drawRobots();
                    SDL_RenderPresent(render);
                }
            }
        }
    }
}

string updateRobotName(string rName)
{
    cout << "updating robot" << endl;
    string tempHere = rName;
    for (int i = tempHere.length(); i < 20; i++)
    {
        tempHere = " " + tempHere;
    }
    return tempHere;
}

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

        SDL_Rect nameSlots;
        nameSlots.x = 95 + half;
        nameSlots.y = 105 + (70 * height);
        nameSlots.w = 390;
        nameSlots.h = 25;

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
        temp3.w = 32;
        temp3.h = 13;

        SDL_Rect temp4;
        temp4.x = 50 + half;
        temp4.y = 107 + (70 * height);
        temp4.w = 15;
        temp4.h = 21;

        SDL_Rect temp5;
        temp5.x = 8 + half;
        temp5.y = 117 + (70 * height);
        temp5.w = 32;
        temp5.h = 13;
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
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderFillRect(render, &temp);
        SDL_RenderDrawRect(render, &temp2);
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        SDL_RenderFillRect(render, &temp3);
        SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
        SDL_RenderFillRect(render, &temp5);
        //SDL_RenderDrawLine(render, 13 + half, 109 + (70 * height), 13 + half, 126 + (70 * height));
        surface = TTF_RenderText_Solid(font1, "R", black);
        texture = SDL_CreateTextureFromSurface(render, surface);
        SDL_RenderCopy(render, texture, NULL, &temp4);
        SDL_FreeSurface(surface);
        surface = TTF_RenderText_Solid(font1, robNum, red);
        texture = SDL_CreateTextureFromSurface(render, surface);
        temp4.x = 60 + half;
        SDL_RenderCopy(render, texture, NULL, &temp4);
        SDL_FreeSurface(surface);
        cout << robotDisplay[i] << endl;
        surface = TTF_RenderText_Solid(font1, robotDisplay[i].c_str(), gray);
        texture = SDL_CreateTextureFromSurface(render, surface);
        SDL_RenderCopy(render, texture, NULL, &temp);
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
    string compString;
    while (!leave)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN))
            {
                leave = true;
                return inputNumbers;
            }
            if (e.type == SDL_TEXTINPUT)
            {
                compString = e.text.text;
                if (compString == "0" || compString == "1" || compString == "2" || compString == "3" || compString == "4" || compString == "5" || compString == "6" || compString == "7" || compString == "8" || compString == "9")
                {
                    if (inputNumbers.length() > 0 || compString != "0")
                    {
                        inputNumbers += e.text.text;
                        updateDigit(inputNumbers, n);
                    }
                }
            }
            if (e.key.keysym.sym == SDLK_BACKSPACE)
            {
                if (e.type == SDL_KEYDOWN)
                {
                    inputNumbers = inputNumbers.substr(0, inputNumbers.size() - 1);
                    updateDigit(inputNumbers, n);
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
            /*             int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                std::cout << "SDL_image Error:" << IMG_GetError() << std::endl;
                success = false;
            } */

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
