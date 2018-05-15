#include <vector>
#include "graphics.h"

namespace matrix {
    
    void initialize_matrix( std::vector< std::vector< bool > > &matrix, int windowWidth, int windowHeight, int cellWidth ) {
        
        //temp row
        std::vector< bool > temp;  

        //find number of cells wide and high matrix should be
        int numOfColumns = (windowWidth) / cellWidth;
        int numOfRows = (windowHeight) / cellWidth;
        
        //initialize temp cels to false 
        for(int columns = 0; columns < numOfColumns; columns++)

            temp.push_back(false);
        
        //copy temp vector into main to form each row
        for( int rows = 0; rows < numOfRows; rows++)

            matrix.push_back(temp); 
    }
    
    void randomize_matrix( std::vector< std::vector< bool > > &matrix, int range ) {

        size_t rows = matrix.size();
        size_t columns = matrix[0].size();
        int random_num;
        int i = 0;
        for( size_t currentRow = 0;currentRow< rows; currentRow++ ) {

            for( size_t currentColumn = 0;currentColumn < columns; currentColumn++ ) {
                i += time(NULL);
                srand(time(NULL)+i);
                random_num = rand() % range;
                //printf("%i ", random_num); 
                if(random_num == 1)
                {
                    matrix[currentRow][currentColumn] = true;     
                }           
            } 
        }
    }

    size_t count_alive_neighbours( std::vector< std::vector< bool > > &matrix, size_t currentRow, size_t currentColumn, size_t maxRow, size_t maxColumns ) {

        size_t aliveNeighbours = 0;
        size_t top_row, bottom_row;
        size_t left, right; 

        //get top row 
        if(currentRow == 0) {

            top_row = maxRow;     
        }
        else {

            top_row = currentRow - 1;
        }

        //get bottom row
        if(currentRow == maxRow) {

            bottom_row = 0;
        }
        else {

            bottom_row = currentRow+1;
        } 

        //get left index 
        if(currentColumn == 0)
        {
            left = maxColumns;
        }
        else {
            left = currentColumn-1;
        } 

        //get right index
        if(currentColumn == maxColumns) {

            right = 0;
        }
        else {

            right = currentColumn+1;
        } 
        
        //count currently active cell
        if(matrix[currentRow][currentColumn] == true)
            aliveNeighbours++;

        //top left corner
        if(matrix[top_row][left] == true)
            aliveNeighbours++;

        //top right corner
        if(matrix[top_row][right] == true)
            aliveNeighbours++; 

        //top
        if(matrix[top_row][currentColumn] == true)
            aliveNeighbours++;

        //left
        if(matrix[currentRow][left] == true)
            aliveNeighbours++;

        //right
        if(matrix[currentRow][right] == true)
            aliveNeighbours++; 

        //bottom left
        if(matrix[bottom_row][left] == true)
            aliveNeighbours++;

        //bottom right
        if(matrix[bottom_row][right] == true)
            aliveNeighbours++; 

        // bottom  
        if(matrix[bottom_row][currentColumn] == true)
            aliveNeighbours++;

        return aliveNeighbours;
    } 
    
    void update_matrix( std::vector< std::vector< bool > > &activeMatrix, std::vector< std::vector< bool > > &futureMatrix ) {

        size_t rows = activeMatrix.size();   
        size_t columns = activeMatrix[0].size(); 
        int aliveNeighbours;

        for( size_t currentRow = 0;currentRow < rows; currentRow++ ) {

            for( size_t currentColumn = 0;currentColumn < columns; currentColumn++ ) {

                aliveNeighbours = count_alive_neighbours(activeMatrix, currentRow, currentColumn, rows-1, columns-1); 

                futureMatrix[currentRow][currentColumn] = false;
                //cell is alive and has less than 2 neighbours and dies
                if( aliveNeighbours < 2 )
                    futureMatrix[currentRow][currentColumn] = false;

                //live cell has 2 neigbouring cells so continues living
                else if( aliveNeighbours == 2 && futureMatrix[currentRow][currentColumn] == true )
                    futureMatrix[currentRow][currentColumn] = true;  

                //cell has 3 neighbours it is born or still lives
                else if( aliveNeighbours == 3 )
                    futureMatrix[currentRow][currentColumn] = true; 

                //cell has more than 3 neighbours dies from overcrowding
                else if( aliveNeighbours > 3 )
                    futureMatrix[currentRow][currentColumn] = false;

            } 
        } 
    }

}
