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
    numTiles = 0;
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
        if (token != "") {
           result.push_back(token);
        }
    } 
    if (result.size() == 1) {
        std::string tileDetails = result.at(0).substr(0,2);
        std::string coordinates = result.at(0).substr(3);
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

        //if coordinate is only 1 digit number
        //eg. C3 then length is 2 so only have to check 1st index
        if (coordinates.length() == 2) {
            //if col is 0, it doesn't calculate correctly,
            std::cout << coordinates[1] << std::endl;
            if (coordinates[1] == '0') {
                std::cout << "coordinate = 0" << std::endl;
                int col = 0;
                boardTiles[row][col] = tile;
                std::cout << "row: " << row << "col: " << col << std::endl;

            }
            else {
                int col = coordinates[1] - '0';
                boardTiles[row][col] = tile;
                std::cout << "row: " << row << "col: " << col << std::endl;
            }


        } else {
            int col = (coordinates[1]-'0')*10 + (coordinates[2]-'0');
            boardTiles[row][col] = tile;
            std::cout << "row: " << row << "col: " << col << std::endl;
        }
        numTiles++;

    } else {
        for (size_t i = 0;i<result.size();i++) {
            std::string tileDetails = result.at(i).substr(0,2);
            std::string coordinates = result.at(i).substr(3);

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
            //if coordinate is only 1 digit number
            //eg. C3 then length is 2 so only have to check 1st index
            if (coordinates.length() == 5) {
                int col = coordinates[1] - '0';
                boardTiles[row][col] = tile;

            } else {
                int col = (coordinates[1]-'0')*10 + (coordinates[2]-'0');
                boardTiles[row][col] = tile;
            }
            numTiles++;
        }
    }

}

bool Board::placeTile(Tile* tile, int row, int col) {
    //TO DO::VALIDATE PLACEMENT
    if (row < 0 || col < 0 || row >= ROWS || col >= COLS) {
        std::cout << "row or col is out of bounds" << std::endl;
    }
    else {
        boardTiles[row][col] = tile;
        numTiles++;
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
    if (x < 0 || y < 0 || x >= 26 || y >= 26) {
        return nullptr;
    }
    else {
       return this ->boardTiles[x][y];
    }
}

int Board:: getNumTiles()
{
    return numTiles;
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