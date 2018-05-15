#include <SDL2/SDL.h>
#include <iostream>
#include "graphics.h"
#include "matrix.h"

namespace graphics {
    
    void Print_SDL_Error(std::ostream &stream, std::string errorMessage) {

        stream << errorMessage << ": SDL Error: " << SDL_GetError() << std::endl;
    } 

    SDL_Objects init(SDL_Objects& graphicsObjects, int windowWidth = 0, int windowHeight = 0) {
        
        /*
         *  Initialize SDL
         *  if error:
         *      print to terminal and exit with Failure field set
         */ 

        if( SDL_Init(SDL_INIT_VIDEO) ) {

            printf("SDL could not initialize! SDL error: %s\n", SDL_GetError());

            graphicsObjects.Failure = true; 

            return graphicsObjects;        
        }
        
        
        /*
         *  Initialize SDL_window object
         *  if error:
         *      print to terminal and exit with Failure field set true
         */

        graphicsObjects.window = SDL_CreateWindow( "Conways Game Of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);

        if(graphicsObjects.window == NULL) {

            Print_SDL_Error(std::cout, "couldn't create window");

            graphicsObjects.Failure = true; 

            return graphicsObjects;
        } 

        
        /*
         * Initialize SDL_renderer object
         * if error:
         *      print to terminal and exit with Failure field set true
         */ 
        graphicsObjects.renderer = SDL_CreateRenderer( graphicsObjects.window, -1, SDL_RENDERER_ACCELERATED);

        if( graphicsObjects.renderer == NULL ) {

            Print_SDL_Error(std::cout, "failed to get renderer for window");

            graphicsObjects.Failure = true;

            return graphicsObjects; 
        } 

        
        /*
         *  SUCCESSFULLY INITIALIZED
         */
         
        //make sure failure field is set to false
        graphicsObjects.Failure = false;

        return graphicsObjects; 
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
            SDL_Delay(300);
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
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
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
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &rect);
                
                //set to draw cell in next column
                rect.x += boxWidth; 
            }
            
            //set to draw cell's in next row
            rect.y += boxWidth; 
        }

        SDL_RenderPresent(renderer);
    }

}

