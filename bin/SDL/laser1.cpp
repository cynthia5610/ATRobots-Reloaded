
#include <iostream>
#include <string.h>
#include <SDL2/SDL.h>


const int SECOND = 1000;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
//triangle facing top
int leftx1       =   ((.02)*(SCREEN_WIDTH));
int lefty1       =   ((.075)*(SCREEN_HEIGHT));
int rightx2      =   ((.05)*(SCREEN_WIDTH));
int righty2      =   ((.005) * (SCREEN_HEIGHT));
int bottomx2     =   ((.08)*(SCREEN_WIDTH));
int bottomy2     =   ((.075)*(SCREEN_HEIGHT));










// init ... The init function, it calls the SDL init function.
int init() 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
    {
		return -1;
	}

	return 0;
}

void drawUP(SDL_Renderer* Renderer) 
{	

    
	//Set the draw color...
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	
    
    //Clear the screen.
	SDL_RenderClear(Renderer);

	
    
    //Setting the actual draw color.
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    
	//Drawing the triangle UP
    SDL_RenderDrawLines(renderer, points, POINTS_COUNT);


    
	//Update the Renderer.
	SDL_RenderPresent(Renderer);
}



void rotateLeft(SDL_Renderer* Renderer, int x, int y) 
{	
	//Set the draw color...
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	
    
    //Clear the screen.
	SDL_RenderClear(Renderer);

	
    
    //Setting the actual draw color.
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    
    topleftx1 += x;
    topleftx2 += x;
    toprightx1 += x;
    toprightx2 += x;
    topbottomx1 -= x;
    topbottomx2 -= x;
        
    toplefty1 -= y;
    toplefty2 -= y;
    toprighty1 -= y;
    toprighty2 -= y;
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
    bool quit = 0;
    //Event handler
	SDL_Event e;
	//Creating the context for SDL2.
	SDL_Window* Window = createWindowContext("Laser Test");

	//Creating the rendering context.
	SDL_Renderer* Renderer = createRendererContext(Window);

    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
				quit = true;
			}
            if ( e.key.keysym.sym == SDLK_SPACE)
            {
                    //Drawing!
                    drawUP(Renderer);
            }
            if ( e.key.keysym.sym == SDLK_a)
            {
                    //Drawing!
                    rotateLeft(Renderer, 1, 1);
            }
            if ( e.key.keysym.sym == SDLK_d)
            {
                    //Drawing!
                    drawUP(Renderer);
            }

        }
    }


    
	//Cleaning up everything.
	SDL_Quit();
	return 0;
}
