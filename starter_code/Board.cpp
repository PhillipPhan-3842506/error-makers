#include "Board.h"
#define ROWS 6
#define COLS 6


Board::Board(){
    for (int i = 0;i < ROWS;i++) {
        for (int j = 0; j < COLS;j++) {
            std::string empty = "  ";
            board[i][j] = empty;
            boardTiles[i][j] = nullptr;
        }
    }
    std::cout << "board loaded" << std::endl;


}

void Board::display(){
    std::string rowLabels[6] = {"A","B","C","D","E","F"};
    std::cout << "  0  1  2  3  4  5 " << std::endl;
    std::cout << "--------------------" << std::endl;
    for (int i = 0; i < ROWS;i++) {
        std::cout << rowLabels[i] << '|';
        for (int j = 0; j < COLS;j++) {
            if (boardTiles[i][j] != nullptr) {
                std::cout << board[i][j] << boardTiles[i][j]->getTitleDetails();
            }
            else {
                std::cout << board[i][j] << '|';
            }
        }
        std::cout << std::endl;
    }
}