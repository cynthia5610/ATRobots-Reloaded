#include <iostream>
#include <string.h>
#include <SDL2/SDL.h>


const int SECOND = 1000;
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;


//triangle facing top
int topleftx1       =   ((.02)*(SCREEN_WIDTH));
int toplefty1       =   ((.075)*(SCREEN_HEIGHT));
int topleftx2       =   ((.05)*(SCREEN_WIDTH));
int toplefty2       =   ((.005) * (SCREEN_HEIGHT));
int toprightx1      =   ((.08)*(SCREEN_WIDTH));
int toprighty1      =   ((.075)*(SCREEN_HEIGHT));
int toprightx2      =   ((.05)*(SCREEN_WIDTH));
int toprighty2      =   ((.005) * (SCREEN_HEIGHT));
int topbottomx1     =   ((.02)*(SCREEN_WIDTH));
int topbottomy1     =   ((.075)*(SCREEN_HEIGHT));
int topbottomx2     =   ((.08)*(SCREEN_WIDTH));
int topbottomy2     =   ((.075)*(SCREEN_HEIGHT));

int curTankSpeed = 3;






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

	//Update the Renderer.
	SDL_RenderPresent(Renderer);
}

void moveX(SDL_Renderer* Renderer, int x)
{
    //Set the draw color...
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	
    
    //Clear the screen.
	SDL_RenderClear(Renderer);

	
    
    //Setting the actual draw color.
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    
    //if inside borders
    if((topleftx1 >= (0 + curTankSpeed) && topleftx2 >= (0 + curTankSpeed) && toprightx1 >= (0 + curTankSpeed) && toprightx2 >= (0 + curTankSpeed) && topbottomx1 >= (0 + curTankSpeed) && topbottomx2 >= (0 + curTankSpeed)) && (topleftx1 <= (SCREEN_WIDTH - curTankSpeed) && topleftx2 <= (SCREEN_WIDTH - curTankSpeed) && toprightx1 <= (SCREEN_WIDTH - curTankSpeed) && toprightx2 <= (SCREEN_WIDTH - curTankSpeed) && topbottomx1 <= (SCREEN_WIDTH - curTankSpeed) && topbottomx2 <= (SCREEN_WIDTH - curTankSpeed)))
    {
        //move pixels of triangle
        topleftx1 += x;
        topleftx2 += x;
        toprightx1 += x;
        toprightx2 += x;
        topbottomx1 += x;
        topbottomx2 += x;
    }
    
    //Drawing the triangle UP
	SDL_RenderDrawLine(Renderer, topleftx1,toplefty1,topleftx2,toplefty2);                  
	SDL_RenderDrawLine(Renderer, toprightx1,toprighty1,toprightx2,toprighty2);             
	SDL_RenderDrawLine(Renderer, topbottomx1,topbottomy1,topbottomx2,topbottomy2);  
    //Update the Renderer.
	SDL_RenderPresent(Renderer);
}

void moveY(SDL_Renderer* Renderer, int y)
{
    //Set the draw color...
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	
    
    //Clear the screen.
	SDL_RenderClear(Renderer);

	
    
    //Setting the actual draw color.
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

     toplefty1 += y;
     toplefty2 += y;
     toprighty1 += y;
     toprighty2 += y;
     topbottomy1 += y;
     topbottomy2 += y;
    
    //Drawing the triangle UP
	SDL_RenderDrawLine(Renderer, topleftx1,toplefty1,topleftx2,toplefty2);                  
	SDL_RenderDrawLine(Renderer, toprightx1,toprighty1,toprightx2,toprighty2);             
	SDL_RenderDrawLine(Renderer, topbottomx1,topbottomy1,topbottomx2,topbottomy2);  
    //Update the Renderer.
	SDL_RenderPresent(Renderer);
}

// createWindowContext ... Creating the window for later use in rendering and stuff.
SDL_Window* createWindowContext(std::string title) 
{
	//Declaring the variable the return later.
	SDL_Window* Window = NULL;

	//Creating the window and passing that reference to the previously declared variable. 
	Window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

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
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
		{
            //User requests quit
            if( e.type == SDL_QUIT )
            {
				quit = true;
			}
			else if ( e.key.keysym.sym == SDLK_UP)
            {
                    //Drawing!
                    moveY(Renderer, -curTankSpeed);
            }
            else if ( e.key.keysym.sym == SDLK_DOWN)
            {
                    //Drawing!
                    moveY(Renderer, curTankSpeed);
            }
            else if ( e.key.keysym.sym == SDLK_RIGHT)
            {
                    //move right
                    moveX(Renderer, curTankSpeed);
            }
            else if ( e.key.keysym.sym == SDLK_LEFT)
            {
                    //move right
                    moveX(Renderer, -curTankSpeed);
            }
        }

    }
    
	//Cleaning up everything.
	SDL_Quit();
	return 0;
}
