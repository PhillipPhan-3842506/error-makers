#include "Board.h"
#include <sstream>
#include <algorithm>
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

void Board::load(std::string boardState) {
    std::cout << "boardState: " << boardState << std::endl;
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //split boardState string into multiple strings, store into vector
    std::istringstream ss(boardState);
    std::string token;
    std::vector<std::string> result;
    while (std::getline(ss,token,',')) {
        token.erase(std::remove_if(token.begin(), token.end(), [](unsigned char c){ return std::isspace(c); }),token.end());
        result.push_back(token);
    } 
    for (size_t i = 0;i<result.size()-1;i++) {
        std::string tileDetails = result.at(i).substr(0,2);
        std::string coordinates = result.at(i).substr(3,2);

        char colour = tileDetails[0];
        char shapeAsChar = tileDetails[1];
        int shape = shapeAsChar -'0';

        Tile* tile = new Tile(colour,shape);
        int row = 0;
        for (int i = 0; i < 26;i++) {
            if (coordinates[0] == alphabet[i]) {
                row = i;
            }
        }
        int col = coordinates[1] - '0';
        boardTiles[row][col] = tile;
    }

}

bool Board::placeTile(Tile* tile, int row, int col) {
    //TO DO::VALIDATE PLACEMENT
    if (row < 0 || col < 0 || row >= ROWS || col >= COLS) {
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
    std::string tilesState;
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string space = ", ";

    for(int i = 0; i < getBoardTileRow(); i++){
        for(int j = 0; j< getBoardTileCol(); j++){
            //if tile at i and j is not nullptr, add the tile to tilestate string
            if(boardTiles[i][j] != nullptr){
                tilesState = tilesState + boardTiles[i][j]->getTitleDetails() + "@" + alphabet[i] + std::to_string(j) + space;
            } 
//            else{
                // tilesState = tilesState + "  ";
            // }
            // boardState += tilesState+"|";
        }
    }
    
    return tilesState;
}