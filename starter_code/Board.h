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
        void load(std::string boardState);
        void display(int toggle1, int toggle2);
        void calcReSize();
        bool placeTile(Tile* tile, int row, int col);
        Tile* getTilefromBoard(int x, int y);
        int getBoardTileRow();
        int getBoardTileCol();
        // int final BOARD_SIZE = 26;
        std::string setColorTile(char code, int toggle1);
        std::string setShape(int shape, int toggle2);
        std::string displayBoardStateToString();
        int getNumTiles();

    private:
        // Tile* boardTiles[BOARD_SIZE][BOARD_SIZE];
        std::vector< std::vector<Tile*> > boardTiles;
        std::string board[BOARD_SIZE][BOARD_SIZE];
        int numTiles;
        int resizeRow;
        int resizeCol;
};

#endif // ASSIGN2_BOARD_H