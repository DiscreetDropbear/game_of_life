#include <SDL2/SDL.h>
#include <iostream>
#include "graphics.h"
#include "matrix.h"
#include <stdlib.h>

namespace graphics {
    
    void Print_SDL_Error(std::ostream &stream, std::string errorMessage) {

        stream << errorMessage << ": SDL Error: " << SDL_GetError() << std::endl;
    } 

    int init(SDL_Objects& graphicsObjects) {
        
        int windowWidth;
        int windowHeight;        

        /*
         *  Initialize SDL
         *  if error:
         *      print to terminal and exit with Failure field set
         */ 

        if( SDL_Init(SDL_INIT_VIDEO) ) {

            printf("SDL could not initialize! SDL error: %s\n", SDL_GetError());
            return -1;        
        }
        
        
        /*
         *  Initialize SDL_window object
         *  if error:
         *      print to terminal and exit with Failure field set true
         */

        graphicsObjects.window = SDL_CreateWindow( "Conways Game Of Life", 0, 0, 0, 0, 
                SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS);

        if(graphicsObjects.window == NULL) {
            Print_SDL_Error(std::cout, "couldn't create window");
            return -1;
        }
        
        //get active display size and set window size correctly 
        if(get_display_size(graphicsObjects, &windowWidth, &windowHeight) < 0){
            return -1; 
        }
        if( windowWidth > 0 && windowHeight > 0){
//            SDL_SetWindowSize(graphicsObjects.window, windowWidth, windowHeight);
        }

        /*
         * Initialize SDL_renderer object
         * if error:
         *      print to terminal and exit with Failure field set true
         */ 
        graphicsObjects.renderer = SDL_CreateRenderer( graphicsObjects.window, -1, SDL_RENDERER_ACCELERATED);

        if( graphicsObjects.renderer == NULL ) {

            Print_SDL_Error(std::cout, "failed to get renderer for window");

            return -1; 
        } 

        /*
         *  SUCCESSFULLY INITIALIZED
         */

        initialize_background(graphicsObjects.renderer, windowWidth, windowHeight);

        return 1; 
    }
    
    int get_usable_window_size(SDL_Objects &graphicsObjects, int*width, int*height){
        
        int windowWidth = 0;
        int windowHeight = 0;
        if(get_display_size(graphicsObjects, &windowWidth, &windowHeight) < 0){
            return -1;
        }
        
        int topBorder = 0;
        int leftBorder = 0;
        int rightBorder = 0;
        int bottomBorder = 0; 
        int positionX = 0;
        int positionY = 0; 

        if(SDL_GetWindowBordersSize(graphicsObjects.window, &topBorder, &leftBorder,
                    &bottomBorder, &rightBorder) < 0){
            Print_SDL_Error(std::cout, "failed to get window border size.");
            return -1;
        }

        SDL_GetWindowPosition(graphicsObjects.window, &positionX, &positionY);

        windowHeight -= (positionY + topBorder + bottomBorder);
        windowWidth -= (leftBorder + rightBorder);

        *width = windowWidth;
        *height = windowHeight;

        return 1;
    }

    int get_display_size(SDL_Objects &graphicsObjects, int *width, int *height){
 
        /* find the active display so we can find the size of the display the 
         * window is currently in
         */ 
        SDL_DisplayMode displayMode;
        int windowDisplayIndex = SDL_GetWindowDisplayIndex(graphicsObjects.window); 
        if(windowDisplayIndex < 0){
            Print_SDL_Error(std::cout, "error getting active display index.");
            return -1;
        }
                 
        if(SDL_GetCurrentDisplayMode(windowDisplayIndex, &displayMode) != 0){
            Print_SDL_Error(std::cout, "error getting active display mode info.");
            return -1;
        }

        *width = displayMode.w;
        *height = displayMode.h;
        
       return 1; 
    }

    void initialize_background(SDL_Renderer * renderer, int windowWidth, int windowHeight){

        SDL_Rect rect;

        //settup width and height 
        rect.w = windowWidth;
        rect.h = windowHeight; 

        //set up start position
        rect.y = 0;  
        rect.x = 0;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderPresent(renderer);
    }

    void display_loop( std::vector< std::vector< bool > > &matrixBuffer, std::vector< std::vector< bool > > &matrixBuffer2, SDL_Objects &graphicsObjects, int boxWidth) {
        
        //
        bool quit = false;
          
        //used to swap matricies from being current matrix
        //to future matrix on each iteration
        bool switchMatrix = true;
        
        /*
         * infinite display loop
         * exit when SDL_QUIT event is received(window is closed)
         * 
         */ 
        while(!quit) {
            
            //get SDL_event
            while( SDL_PollEvent( &graphicsObjects.event ) != 0 ) {

                if(graphicsObjects.event.type == SDL_QUIT)
                {
                    quit = true;
                }
            } 

            /*
             *  alternate matricies      
             */  
            if(switchMatrix) { 
                //print matrixBuffer
                print_matrix(graphicsObjects.renderer, matrixBuffer, matrixBuffer2, boxWidth);        

                //next iteration is stored in matrixBuffer2
                matrix::update_matrix(matrixBuffer, matrixBuffer2); 

            } 
            else {
                //print matrixBuffer2 
                print_matrix(graphicsObjects.renderer, matrixBuffer2, matrixBuffer, boxWidth);

                //next iteration is stored in matrixBuffer
                matrix::update_matrix(matrixBuffer2, matrixBuffer); 

            }

            //next iteration through loop switch matrix positions
            switchMatrix = !switchMatrix;

            //SDL_RenderClear( renderer ); 
            SDL_Delay(150);
        }    
        
        //clean up
        SDL_DestroyWindow( graphicsObjects.window );
        SDL_Quit();
    }
    
    

    void print_matrix(SDL_Renderer * renderer,  std::vector< std::vector< bool > > &matrixBuffer, std::vector< std::vector< bool > > &nextMatrix, int boxWidth) {

        /*
         * settup rectangle for drawing
         */ 

        SDL_Rect rect;

        //settup width and height 
        rect.w = boxWidth;
        rect.h = boxWidth; 

        //set up start position
        rect.y = 0;  
        rect.x = 0;
        
        /*
         * loop over matrix and render cells as appropriate
         */

        size_t rows = matrixBuffer.size();
        size_t columns = matrixBuffer[0].size();
        
        //loop over each row
        for( size_t currentRow = 0; currentRow < rows; currentRow++ ) {

            //reset to the first column 
            rect.x = 0; 

            for( size_t currentColumn = 0;currentColumn < columns; currentColumn++ ) {

                //if cell is alive set color to white
                if( matrixBuffer[currentRow][currentColumn] == true ) {
                    int red = 255;//rand() % 256;
                    int green = 255;//rand() % 256;
                    int blue = 255; //rand() % 256;
                     
                    SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
                }
                
                //if cell was dead in last iteration don't redraw it
                else if(nextMatrix[currentRow][currentColumn] == false) {
                    rect.x += boxWidth;
                    continue;
                }

                //if cell is dead set color to black 
                else{

                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                } 

                //draw square
                SDL_RenderFillRect(renderer, &rect);

                //draw white ouline
                //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                //SDL_RenderDrawRect(renderer, &rect);
                
                //set to draw cell in next column
                rect.x += boxWidth; 
            }
            
            //set to draw cell's in next row
            rect.y += boxWidth; 
        }

        SDL_RenderPresent(renderer);
    }
}
