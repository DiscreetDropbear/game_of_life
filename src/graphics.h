#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SDL2/SDL.h>
#include <vector>
#include <string>

namespace graphics {
    
    
    struct SDL_Objects {

        SDL_Window * window;
        SDL_Renderer *renderer;
        SDL_Event event;
        bool Failure;
    };
    
    /*
     * present any errors using the provided stream
     */
    void Print_SDL_Error(std::ostream &, std::string &);

    /*
     * Initialize SDL_Objects struct with needed SDL_Objects
     */ 
    SDL_Objects init(SDL_Objects &, int windowWidth, int windowHeight);

    /*
     * sets the background to black to avoid any previous images from showing up
     */
    void initialize_background(SDL_Renderer * renderer, int windowWidth, int windowHeight);

    /*
     * render squares(cells) into window using matrixBuffer
     * nextMatrix to check for cells that were either alive or dead last time 
     * saving the need to re-render them as an optimisation
     *
     */ 
    void print_matrix(SDL_Renderer * renderer,  std::vector< std::vector< bool > > &, std::vector< std::vector< bool > > &, int);

    
    /*
     * Main loop of program
     *
     * calls functions to calculate  
     *   
     */
    void display_loop( std::vector< std::vector< bool > > &, std::vector< std::vector< bool > > &, SDL_Objects &, int);
    
    
}
#endif
