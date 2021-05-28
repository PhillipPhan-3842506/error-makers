#include "Board.h"
#include <sstream>
#include <algorithm>
#include "TileCodes.h"
#include "Player.h"
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
        boardTiles[rowAsInt][colAsInt] = tile;
        // placeTile(tile, rowAsInt, colAsInt);
    }
    // if (result.size() == 1) {
    //     std::string tileDetails = result.at(0).substr(0,2);
    //     std::string coordinates = result.at(0).substr(3);
    //     char colour = tileDetails[0];
    //     char shapeAsChar = tileDetails[1];
    //     int shape = shapeAsChar -'0';

    //     Tile* tile = new Tile(colour,shape);

    //     int row = 0;
    //     for (int i = 0; i < 26;i++) {
    //         if (coordinates[0] == alphabet[i]) {
    //             row = i;
    //         }
    //     }

    //     //if coordinate is only 1 digit number
    //     //eg. C3 then length is 2 so only have to check 1st index
    //     if (coordinates.length() == 2) {
    //         //if col is 0, it doesn't calculate correctly,
    //         std::cout << coordinates[1] << std::endl;
    //         if (coordinates[1] == '0') {
    //             std::cout << "coordinate = 0" << std::endl;
    //             int col = 0;
    //             boardTiles[row][col] = tile;
    //             std::cout << "row: " << row << "col: " << col << std::endl;

    //         }
    //         else {
    //             int col = coordinates[1] - '0';
    //             boardTiles[row][col] = tile;
    //             std::cout << "row: " << row << "col: " << col << std::endl;
    //         }


    //     } else {
    //         int col = (coordinates[1]-'0')*10 + (coordinates[2]-'0');
    //         boardTiles[row][col] = tile;
    //         std::cout << "row: " << row << "col: " << col << std::endl;
    //     }
    //     numTiles++;

    // } else {
    //     for (size_t i = 0;i<result.size();i++) {
    //         std::string tileDetails = result.at(i).substr(0,2);
    //         std::string coordinates = result.at(i).substr(3);

    //         char colour = tileDetails[0];
    //         char shapeAsChar = tileDetails[1];
    //         int shape = shapeAsChar -'0';

    //         Tile* tile = new Tile(colour,shape);
    //         int row = 0;
    //         for (int i = 0; i < 26;i++) {
    //             if (coordinates[0] == alphabet[i]) {
    //                 row = i;
    //             }
    //         }
    //         //if coordinate is only 1 digit number
    //         //eg. C3 then length is 2 so only have to check 1st index
    //         if (coordinates.length() == 5) {
    //             int col = coordinates[1] - '0';
    //             boardTiles[row][col] = tile;

    //         } else {
    //             int col = (coordinates[1]-'0')*10 + (coordinates[2]-'0');
    //             boardTiles[row][col] = tile;
    //         }
    //         numTiles++;
    //     }
    // }

}

bool Board::placeTile(Tile* tile, int row, int col) {
    bool returnValue = false;

    if (validatePlaceTile(tile,row,col,false)) {
        boardTiles[row][col] = tile;
        numTiles++;
        returnValue = true;
    }

    return returnValue;
}

bool Board::validatePlaceTile(Tile* tile, int row, int col,bool ai) {
    bool returnValue = false;
    if (row < 0 || col < 0 || row >= ROWS || col >= COLS) {
        std::cout << "row or col is out of bounds" << std::endl;

    }
    else if (getTilefromBoard(row, col)!=nullptr) {
        if (!ai)
            std::cout << "invalid move" << std::endl;
    }
    else if (checkBoardTile(row, col) == false) {
        if (!ai)
            std::cout << "invalid move" << std::endl;
    }
    else if (!(compareTilesRow(tile, row, col)==true && compareTilesCol(tile, row, col) == true)){
        if (!ai)
            std::cout << "invalid move" << std::endl;
    } else {
        returnValue = true;
    }
    return returnValue;
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
                std::cout << colourTile(board[i][j]);
            }
            else {
                std::cout << board[i][j] << '|';
            }
        }
        std::cout << std::endl;
    }
}
std::string Board::colourTile(std::string s) {
    std::string returnString = "";
    if (s[0] == RED) {
        returnString = "\033[91m" + unicodeTile(s) + s[1] + "\033[0m" + '|';
    }
    else if (s[0] == ORANGE) {
        returnString = "\033[38;2;255;163;0m" + unicodeTile(s) + s[1] + "\033[0m" + '|';
    }
    else if (s[0] == YELLOW) {
        returnString = "\x1b[38;5;226m" + unicodeTile(s) + s[1] + "\x1b[0m" + '|';
    }
    else if (s[0] == GREEN) {
        returnString = "\x1b[92m" + unicodeTile(s) + s[1] + "\x1b[0m" + '|';
    }
    else if (s[0] == BLUE) {
        returnString = "\x1b[94m" + unicodeTile(s) + s[1] + "\x1b[0m" + '|';
    }
    else if (s[0] == PURPLE) {
        returnString = "\x1b[95m" + unicodeTile(s) + s[1] + "\x1b[0m" + '|';
    }
    return returnString;
}

std::string Board::unicodeTile(std::string s) {
    std::string returnString = "";
    char shapeAsChar = s[1];
    int shape = shapeAsChar -'0';
    if (shape == CIRCLE) {
        returnString = "\u25CF";
    }
    else if(shape == STAR_4) {
        returnString = "\u2726";    
    }
    else if (shape == DIAMOND) {
        returnString = "\u25C6";   
    }
    else if (shape == SQUARE) {
        returnString = "\u25A0";  
    }
    else if (shape == STAR_6) {
        returnString = "\u2605";  
    }
    else if (shape == CLOVER) {
        returnString = "\u2618";  
    }
    // std::cout << "return string is" << returnString << std::endl;
    return returnString;

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

bool Board::compareTilesCol(Tile* tile, int x, int y)
{
    std::vector<Tile*> colTileCollection;
    Tile* colTile;
    bool flag = true;

    int col = y+1;
    if(col < 26)
    {
        while(col < 26 && getTilefromBoard(x,col)!=nullptr)
        {
            colTile = getTilefromBoard(x,col);
            colTileCollection.push_back(colTile);
            col++;
        }
    }
    col = y-1;
    if(col>=0)
    {
        while(col >= 0 && getTilefromBoard(x,col)!=nullptr)
        {
            colTile = getTilefromBoard(x,col);
            colTileCollection.push_back(colTile);
            col--;
        }
    }
    //To check whether the collections conatins any duplicate entries
    const int size = colTileCollection.size();
    int i = 0, j=0;
    while(flag == true && i< size-1)
    {
        j = i+1;
        while(flag == true && j< size)
        {
            if(colTileCollection[i]->colour == colTileCollection[j] ->colour && colTileCollection[i] ->shape == colTileCollection[j] ->shape)
            {
                flag = false;
            }
            j++;
        }
        i++;
    }
    //Checking whether the tile is placable
    i = 0;
    while(flag == true && i< size)
    {
        if(!(colTileCollection[i]->colour == tile ->colour || colTileCollection[i] ->shape == tile ->shape) || (colTileCollection[i]->colour == tile ->colour && colTileCollection[i] ->shape == tile ->shape))
        {
            flag = false;
        }
        i++;
    }
    return flag;
}

bool Board::compareTilesRow(Tile* tile, int x , int y)
{
    std::vector<Tile*> rowTileCollection;
    bool flag = true;
    Tile* rowTile;

    int row = x+1;
    if(row < 26)
    {
        while(row < 26 && getTilefromBoard(row,y)!=nullptr)
        {
            rowTile = getTilefromBoard(row,y);
            rowTileCollection.push_back(rowTile);
            row++;
        }
    }
    row = x-1;
    if(row >= 0)
    {
        while(row >=0 && getTilefromBoard(row,y)!=nullptr)
        {
            rowTile = getTilefromBoard(row,y);
            rowTileCollection.push_back(rowTile);
            row--;
        }
    }
    //To check whether the collections conatins any duplicate entries
    const int size = rowTileCollection.size();
    int i = 0, j=0;
    while(flag == true && i< size-1)
    {
        j = i+1;
        while(flag == true && j< size)
        {
            if(rowTileCollection[i]->colour == rowTileCollection[j] ->colour && rowTileCollection[i] ->shape == rowTileCollection[j] ->shape)
            {
                flag = false;
            }
            j++;
        }
        i++;
    }
    //Checking whether the tile is placable
    i = 0;
    while(flag == true && i< size)
    {
        if(!(rowTileCollection[i]->colour == tile ->colour || rowTileCollection[i] ->shape == tile ->shape) || (rowTileCollection[i]->colour == tile ->colour && rowTileCollection[i] ->shape == tile ->shape))
        {
            flag = false;
        }
        i++;
    }
    return flag;
}

bool Board::checkBoardTile(int x, int y)
{
    bool flag = false;
    if(getNumTiles()==0)
    {
        //Checking ehther any tile exists
        flag = true;
    }
    else
    {
        if(((x+1) < 26 && getTilefromBoard(x+1,y)!=nullptr))
        {
            flag = true;
        }
        else if(((x-1) >= 0 && getTilefromBoard(x-1, y)!=nullptr))
        {
            flag = true;
        }
        else if(((y+1) < 26 && getTilefromBoard(x,y+1)!=nullptr))
        {
            flag = true;
        }
        else if(((y-1) >= 0 && getTilefromBoard(x,y-1)!=nullptr))
        {
            flag = true;
        }
    }
    return flag;
}