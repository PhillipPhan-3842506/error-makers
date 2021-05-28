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
        void display();
        bool placeTile(Tile* tile, int row, int col);
        Tile* getTilefromBoard(int x, int y);
        int getBoardTileRow();
        int getBoardTileCol();
        // int final BOARD_SIZE = 26;
        std::string displayBoardStateToString();
        int getNumTiles();
        std::string colourTile(std::string s);
        std::string unicodeTile(std::string s);
        bool compareTilesCol(Tile* tile, int x, int y);
        bool compareTilesRow(Tile* tile, int x , int y);
        bool checkBoardTile(int x, int y);
        bool validatePlaceTile(Tile* tile, int row, int col,bool ai);
    private:
        // Tile* boardTiles[BOARD_SIZE][BOARD_SIZE];
        std::vector< std::vector<Tile*> > boardTiles;
        std::string board[BOARD_SIZE][BOARD_SIZE];
        int numTiles;
};

#endif // ASSIGN2_BOARD_H