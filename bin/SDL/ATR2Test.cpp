#include <iostream>
#include <string.h>
#include <SDL2/SDL.h>
using namespace std;

const int SECOND = 1000;
const int SCREEN_WIDTH = 639;
const int SCREEN_HEIGHT = 479;



// init ... The init function, it calls the SDL init function.
int init() 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
    {
		return -1;
	}

	return 0;
}

// draw ... Draw a series of lines to the screen to create a triangle.
void draw(SDL_Renderer* Renderer) 
{	
	//Set the draw color...
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	//Clear the screen.
	SDL_RenderClear(Renderer);

	//Setting the actual draw color.
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	//Drawing the lines we want. (-1, 0), (0, 1), (1, 0)
    SDL_Rect mainArena;
    SDL_Rect tankBar;
    SDL_Rect tankStats;
    /*
    {--main arena--}
    
    //format is x1 y1 ,x2 y2
    
    hole(4,4,475,475);
    
    bar(59,2,154,10);
    
    hole(0,0,155,45);
    */

    
    
    mainArena.x = 4;
    mainArena.y = 4;
    mainArena.w = 471;
    mainArena.h = 471;
    
    tankBar.x = 483;
    tankBar.y = 6;
    tankBar.w = 150;
    tankBar.h = 10;
    
    tankStats.x = 480;
    tankStats.y = 4;
    tankStats.w = 155;
    tankStats.h = 45;
    
    SDL_RenderDrawLine(Renderer, 320, 200, 300, 240);
    SDL_RenderDrawLine(Renderer, 300, 240, 340, 240);
    SDL_RenderDrawLine(Renderer, 340, 240, 320, 200);

    /*
        line(ltx[1],lty[1],ltx[2],lty[2]);
        line(ltx[2],lty[2],ltx[3],lty[3]);
        line(ltx[3],lty[3],ltx[1],lty[1]);
        line(ltx[4],lty[4],ltx[5],lty[5]);
    */
    SDL_RenderDrawRect(Renderer, &mainArena);
    SDL_RenderDrawRect(Renderer, &tankBar);
    SDL_RenderDrawRect(Renderer, &tankStats);
	
    
    //Update the Renderer.
	SDL_RenderPresent(Renderer);
}


// createWindowContext ... Creating the window for later use in rendering and stuff.
SDL_Window* createWindowContext(std::string title) 
{
	//Declaring the variable the return later.
	SDL_Window* Window = NULL;

	//Creating the window and passing that reference to the previously declared variable. 
	Window = SDL_CreateWindow("ATR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

	//Returning the newly creted Window context.
	return Window;
}

// createRenderContext ... Creating the rendering context so that I can render things to the Window.
SDL_Renderer* createRendererContext(SDL_Window* Window) 
{
	//Declaring the variable for the Renderer context.
	SDL_Renderer* Renderer = NULL;
	
	//Create the Renderer with the window.
	Renderer = SDL_CreateRenderer(Window, -1, 0);

	//Return the Renderer.
	return Renderer;
}

// main ... The main function, right now it just calls the initialization of SDL.
int main(int argc, char* argv[]) 
{
	//Calling the SDL init stuff.
	init();
  
    
    
    
	//Creating the context for SDL2.
	SDL_Window* Window = createWindowContext("Collision Test!");

	//Creating the rendering context.
	SDL_Renderer* Renderer = createRendererContext(Window);
    
    //Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
    //Drawing!
	draw(Renderer);

    while(!quit)
    {   
        draw(Renderer);
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
		{
            //User requests quit
            if( e.type == SDL_QUIT )
            {
				quit = true;
			}
        }
    }
    
	//Cleaning up everything.
	SDL_Quit();
	return 0;
}
