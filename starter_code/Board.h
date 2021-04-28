#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#define BOARD_SIZE 26

#include <vector>
#include "Tile.h"

typedef char Board[BOARD_SIZE][BOARD_SIZE];

class Board {
    public:
        Board();
        void displayTile();

        // int final BOARD_SIZE = 26;

    private:
        
};

#endif // ASSIGN2_BOARD_H