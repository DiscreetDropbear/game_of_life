#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include "matrix.h"
#include "graphics.h"

int main(int argc, char * argv[]) {
    
    int windowWidth;
    int windowHeight;
    const int boxWidth = 3;
    std::vector< std::vector< bool > > matrixBuffer; 
    std::vector< std::vector< bool > > matrixBuffer2;
    graphics::SDL_Objects graphicsObjects; 

    /*
     *settup SDL objects
     */

    if( graphics::init(graphicsObjects) == -1){

        printf("SDL could not initiate! SDL error: %s\n", SDL_GetError());
        return -1;
    } 
    
    SDL_RenderPresent(graphicsObjects.renderer);
    graphics::get_usable_window_size(graphicsObjects, &windowWidth, &windowHeight);

    //SDL_GL_GetDrawableSize(graphicsObjects.window, &windowWidth,  
    //            &windowHeight); 
    printf("windowWidth: %d, windowHeight: %d", windowWidth, windowHeight);
    
    //settup matricies 
    matrix::initialize_matrix(matrixBuffer, windowWidth, windowHeight, boxWidth);
    matrix::initialize_matrix(matrixBuffer2, windowWidth, windowHeight, boxWidth);

    //generate random input for first matrix 
    matrix::randomize_matrix(matrixBuffer, 12);

    graphics::display_loop(matrixBuffer, matrixBuffer2, graphicsObjects, boxWidth);    
    
    return 0;
}
