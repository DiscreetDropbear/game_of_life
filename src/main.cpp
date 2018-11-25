#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include "matrix.h"
#include "graphics.h"

int main(int argc, char * argv[]) {
         
    int windowHeight = 1030, windowWidth = 1900 ;
    int boxWidth = 5;
    
    std::vector< std::vector< bool > > matrixBuffer; 
    std::vector< std::vector< bool > > matrixBuffer2;
    
    /*
     * settup matricies and randomize the input
     */

    //settup matricies 
    matrix::initialize_matrix(matrixBuffer, windowWidth, windowHeight, boxWidth);
    matrix::initialize_matrix(matrixBuffer2, windowWidth, windowHeight, boxWidth);

    //generate random input for first matrix 
    matrix::randomize_matrix(matrixBuffer, 10);
    
    /*
     *settup SDL objects
     */
    graphics::SDL_Objects graphicsObjects; 
    graphics::init(graphicsObjects, windowWidth, windowHeight); 
    
    //if setup with no errors start display_loop    
    if(!graphicsObjects.Failure) {

        graphics::display_loop(matrixBuffer, matrixBuffer2, graphicsObjects, boxWidth);    
    }
    else {

        return 1;
    }

    return 0;
}
