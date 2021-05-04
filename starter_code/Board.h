#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#define BOARD_SIZE 26

#include <vector>
#include "Tile.h"
#include <iostream>

// typedef char Board[BOARD_SIZE][BOARD_SIZE];

class Board {
    public:
        Board();
        void displayTile();
        void display();

        // int final BOARD_SIZE = 26;

    private:
        Tile* boardTiles[BOARD_SIZE][BOARD_SIZE];
        std::string board[BOARD_SIZE][BOARD_SIZE];
};

#endif // ASSIGN2_BOARD_H