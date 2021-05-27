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
    
    for (size_t i = 0;i<result.size();i++) {
        std::string tileDetails = result.at(i).substr(0,2);
        std::string coordinates = result.at(i).substr(3);
        char colour = tileDetails[0];
        char shapeAsChar = tileDetails[1];
        int shape = shapeAsChar -'0';

        Tile* tile = new Tile(colour,shape);
        char row1 = coordinates.at(0);
        int rowAsInt = row1 - 65;
        std::string col1 = coordinates.substr(1);
        int colAsInt = std::stoi(col1);
        placeTile(tile, rowAsInt, colAsInt);
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

void Board::display(int toggle1, int toggle2)
{
    /*std::cout<<"Calling...."<<std::endl;
    if(numTiles == 0)
    {
        resizeCol = resizeRow = 2;
    }*/
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
                std::cout<<setColorTile(boardTiles[i][j] ->colour, toggle1);
                std::cout << boardTiles[i][j] ->colour <<setShape(boardTiles[i][j] ->shape, toggle2);
                std::cout<<"\033[38;5;15m"<< '|';
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

std::string Board::setColorTile(char code, int toggle1)
{
    std::string literal = "";
    if(toggle1!=0)
    {
        if(code=='R')
        {
            literal = "\033[38;5;9m";
        }
        else if(code=='O')
        {
            literal = "\033[38;5;208m";
        }
        else if(code=='Y')
        {
            literal = "\033[38;5;11m";
        }
        else if(code=='G')
        {
            literal = "\033[38;5;10m";
        }
        else if(code=='B')
        {
            literal = "\033[38;5;12m";
        }
        else if(code=='P')
        {
            literal = "\033[38;5;63m";
        }
    }
    return literal;
}

std::string Board::setShape(int shape, int toggle2)
{
    std::string literal = "";
    if(toggle2!=0)
    {
        if(shape==1)
        {
            literal = "\u25CF";
        }
        else if(shape ==2)
        {
            literal = "\u2727";
        }
        else if(shape == 3)
        {
            literal = "\u2662";
        }
        else if(shape==4)
        {
            literal = "\u25A0";
        }
        else if(shape==5)
        {   
            literal = "\u2734";
        }
        else if(shape ==6)
        {
            literal = "\u2731";
        }
    }
    else
    {
        if(shape==1)
        {
            literal = "1";
        }
        else if(shape ==2)
        {
            literal = "2";
        }
        else if(shape == 3)
        {
            literal = "3";
        }
        else if(shape==4)
        {
            literal = "4";
        }
        else if(shape==5)
        {   
            literal = "5";
        }
        else if(shape ==6)
        {
            literal = "6";
        }
    }
    return literal;
}