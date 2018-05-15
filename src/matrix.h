#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

namespace matrix {

    /*
     * figure out the rows and columns needed in matrix and
     * initialize each to false.
     */ 
    void initialize_matrix( std::vector< std::vector< bool > > &, int, int, int);

    /*
     * randomly turn cells on and off for a random patern
     */ 
    void randomize_matrix( std::vector< std::vector< bool > > &, int); 

    /*
     * given a cell return the number of neighbours that are alive
     */
    size_t count_alive_neighbours( std::vector< std::vector< bool > > &, size_t , size_t , size_t , size_t );
    
    /*
     * take each cell and find the number of alive neighbours
     * apply conways game of life rules to decide if the cell
     * is alive or dead.
     */
    void update_matrix( std::vector< std::vector< bool > > &, std::vector< std::vector< bool > > & );
}

#endif
