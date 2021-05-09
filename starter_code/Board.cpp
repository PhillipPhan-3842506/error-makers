#include "Board.h"
#define ROWS 26
#define COLS 26


Board::Board(){
    for (int i = 0;i < ROWS;i++) {
        for (int j = 0; j < COLS;j++) {
            std::string empty = "  ";
            board[i][j] = empty;
        }
    }
    boardTiles.assign(26, std::vector<Tile*>(26));
}   

bool Board::placeTile(Tile* tile, int row, int col) {
    //TO DO::VALIDATE PLACEMENT
    if (row < 0 || col < 0 || row > ROWS || col > COLS) {
        std::cout << "row or col is out of bounds" << std::endl;
    }
    else {
        boardTiles[row][col] = tile;
        return true;
    }

    return false;
}

int Board::getBoardTileRow() {
    return this->boardTiles.size();
}

int Board::getBoardTileCol() {
    return this->boardTiles[0].size();
}

void Board::display(){
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::cout << "  ";
    for (int count = 0; count < ROWS;count++) {

        if (count > 9) {
            std::cout << count << " ";
        }
        else {
            std::cout << count << "  ";
        }
    }
    std::cout << "\n ----------------------------------------------------------"
    << "---------------------"
    << std::endl;
    // std::cout << "-"*50 << std::endl;
    for (int i = 0; i < ROWS;i++) {
        std::cout << alphabet[i] << '|';
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

//std::string Board::DisplayTotring(){

//again
std::string Board::displayBoardStateToString(){
    std::string boardState;
    std::string tilesState;
    for(int i = 0; i < getBoardTileRow(); i++){
        for(int j = 0; j< getBoardTileCol(); j++){
            //if tile at i and j is not nullptr, add the tile to tilestate string
            if(boardTiles[i][j] != nullptr){
                tilesState = tilesState + boardTiles[i][j]->getTitleDetails();
            } 
            else{
                tilesState = tilesState + "  ";
            }
            boardState += tilesState+"|";
        }
        boardState += "/n";
    }
    return boardState;
}