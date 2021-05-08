#include "Board.h"
#define ROWS 6
#define COLS 6


Board::Board(){
    for (int i = 0;i < ROWS;i++) {
        for (int j = 0; j < COLS;j++) {
            std::string empty = "  ";
            board[i][j] = empty;
        }
    }
    std::cout << "board loaded" << std::endl;

    boardTiles.assign(6, std::vector<Tile*>(6));
}   

bool Board::placeTile(Tile* tile, int row, int col) {
    //TO DO::VALIDATE PLACEMENT
    if (row < 0 || col < 0 || row > ROWS || col > COLS) {
        std::cout << "row or col is out of bounds" << std::endl;
    }
    else {
        boardTiles[row-1][col] = tile;
        return true;
    }

    return false;
}

void Board::display(){
    std::string rowLabels[6] = {"A","B","C","D","E","F"};
    std::cout << "  0  1  2  3  4  5 " << std::endl;
    std::cout << "--------------------" << std::endl;
    for (int i = 0; i < ROWS;i++) {
        std::cout << rowLabels[i] << '|';
        for (int j = 0; j < COLS;j++) {
            if (boardTiles[i][j] != nullptr) {
                board[i][j] = boardTiles[i][j]->getTitleDetails();
                std::cout << board[i][j] << '|';
            }
            else {
                std::cout << board[i][j] << '|';
            }
        }
        std::cout << std::endl;
    }
}

Tile* Board :: getTilefromBoard(int x, int y)
{

    return this ->boardTiles[x][y];
}