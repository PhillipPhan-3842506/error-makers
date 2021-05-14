#include "GameEngine.h"
#include "Tile.h"
#include "Player.h"
#include "Bag.h"
#include "Board.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#define NUMBER_OF_PLAYERS 2 

//This constructor is for making a new game
GameEngine::GameEngine(std::string playerNames[],int numberOfPlayers) {
    // for (int i = 0; i < NUMBER_OF_PLAYERS;++i) {
    //     // Player* player = new Player(playerNames[i]);
    //     // playerList[i] = player;
    //     playerList[i] = new Player(playerNames[i]);
    // }
    // playerList[0] = new Player(playerNames[0]);
    // playerList[1] = new Player(playerNames[1]);
    playerListVector.push_back(new Player(playerNames[0]));
    playerListVector.push_back(new Player(playerNames[1]));
    setupGame();
}

//This constructor is for continue a game after a saved game file is loaded
GameEngine::GameEngine(std::string playerNames[], int player1Score, std::string player1Hand,
        std::string player2Hand, int player2Score, std::string boardShape, 
        std::string boardState, std::string tileBagString, std::string currentPlayerName) {
            
    for (int i = 0; i < NUMBER_OF_PLAYERS;i++) {
        Player* player = new Player(playerNames[i]);
        playerListVector.push_back(player);
        //if the playername is the current player, make the current player equal to the player
        if (getPlayer(i)->getPlayerName() == currentPlayerName) {
            currentPlayer = i;
        }

    }

    //set player 1 score + hand
    getPlayer(0)->updatePlayerScore(player1Score);
    //set player 2 score
    getPlayer(1)->updatePlayerScore(player2Score);

    std::istringstream ssPlayer1(player1Hand);
    std::istringstream ssPlayer2(player2Hand);
    std::string tokenPlayer1;
    std::string tokenPlayer2;
    std::vector<std::string> resultPlayer1;
    std::vector<std::string> resultPlayer2;

    //set player 1 hand
    while (std::getline(ssPlayer1,tokenPlayer1,',')) {
        resultPlayer1.push_back(tokenPlayer1);
    }
    for (size_t i = 0;i<resultPlayer1.size();i++) {

        char colour = resultPlayer1.at(i).substr(0,1)[0];
        int shape = std::stoi(resultPlayer1.at(i).substr(1));
        Tile* tile = new Tile(colour,shape);
        getPlayer(0)->addTileToPlayerHand(tile);
    }

    //set player 2 hand
    while (std::getline(ssPlayer2,tokenPlayer2,',')) {
        resultPlayer2.push_back(tokenPlayer2);
    }
    for (size_t i = 0;i<resultPlayer2.size();i++) {

        char colour = resultPlayer2.at(i).substr(0,1)[0];
        int shape = std::stoi(resultPlayer2.at(i).substr(1));
        Tile* tile = new Tile(colour,shape);
        getPlayer(1)->addTileToPlayerHand(tile);
    }

    //create bag from tileBagString
    bag = new Bag(tileBagString);


    board.load(boardState);
    playGame();



}

GameEngine::~GameEngine() {

}

void GameEngine::start() {
    std::cout << "Play game" << std::endl;

    // setupGame();
    // playGame();
}
/**
 * 
 * This method is responsible for setting up the game.
 * It does the following:
 *  creates the bag for the game, with a random order after calling shuffle
 *  this order remains the same for the current game Engine
 * 
 *  loops 2 times through the players it takes 6 tiles from the bag and giving them to the player hand
 * 
 * */
void GameEngine::setupGame() {
    currentPlayer = 0;
    //set up board
    // board.display();

    std::cout << "---------------------------" << std::endl;
    bag = new Bag();
    bag->getTileBag()->shuffle();

    //loops through players, assigns them 6 tiles each
    for (int i = 0; i < 2; i++) {
        //give 6 tiles per player
        for (int tiles = 0; tiles < 6; tiles++) {
            Tile* tileToAdd = bag->getOneTile();
            getPlayer(i)->addTileToPlayerHand(tileToAdd);
            //as player picked a tile from the front, remove the tile
            bag->getTileBag()->deleteTile(tileToAdd);

        }
        // std::cout << playerList[i]->getPlayerName() << " has : " << std::endl;
        // playerList[i]->getPlayerHand()->printToString();

    }
    // std::cout << "bag contains : " << std::endl;
    bag->getTileBag()->printToString();

    playGame();
}

//The acutally gameplay
void GameEngine::playGame() {
    //prompt current player to go
    board.display();
    std::cout << getPlayer(currentPlayer)->getPlayerName() << ", it's your turn now" << std::endl;
    //display the score of each player
    for (int i = 0; i < NUMBER_OF_PLAYERS; i ++){
    std::cout << "score for " << getPlayer(i)->getPlayerName() << ": " << getPlayer(i)->getPlayerScore() << std::endl;
    }
    //display the current board

    //display the tiles in current player's hand
    std::cout << "Your hand is: " <<
    getPlayer(currentPlayer)->getPlayerHand()->printToString() << std::endl;
    
    playerMove();
//    switchRound();
}

//the function to switch turn bewteen players
void GameEngine::switchRound(){
    currentPlayer++;
    currentPlayer = currentPlayer%2;
    
    //check if the bag is empty
    if(tilebag.size() == 0){
        std::cout << "Game Over !" << std::endl;
        std::string playerWin = "";
        int winScore = 0;
        for (int i = 0; i < NUMBER_OF_PLAYERS; i++){
        //print scores for every player  
            std::cout << "Score for " << getPlayer(i)->getPlayerName() << ": " << getPlayer(i)->getPlayerScore() << std::endl;
        //if a current player's score is higher the highest recorded
        if (getPlayer(i)->getPlayerScore() > winScore){
            playerWin = getPlayer(i)->getPlayerName();
            winScore = getPlayer(i)->getPlayerScore();
        }
        }
        std::cout << playerWin << " IS THE WINNER !!!!!" << std::endl;
        std::cout << "Congratulations!" << std::endl;
        }
        else{
            std::cout << "board state to string " << board.displayBoardStateToString() << std::endl;
            playGame();            
        }
}
// " place XX at XX"
void GameEngine::playerMove(){
    bool correctInput = false;
    std::string move = "";
//check input correct
    while (correctInput == false){
//store user input as 4 strings
        std::cout << "> ";
        std::getline(std::cin, move);
        //std::cout << "\n " << std::endl;
        //std::cout << "place substring: " << move.substr(0,5) << std::endl;
        //std::cout << "at substring: " << move.substr(9,2) << std::endl;
        //std::cout << "tileColour substring: " << move.substr(6,2) << std::endl;
        //std::cout << "row/col substring: " << move.substr(12,2) << std::endl;

        
        if(move.substr(0,5).compare("place") == 0 && move.substr(9,2).compare("at")==0 && isdigit(move.substr(13)[0]) ){
            //store tile values
            char tileColour = move.at(6);
            char tileShape = move.at(7);
            int intTileShape = tileShape -'0';

            // std::cout << tileColour << std::endl;
            // std::cout << tileShape  << std::endl;

            //store input as tile
            Tile* selectedTile = getPlayer(currentPlayer)->getPlayerHand()->getTileWithColourShape(tileColour, intTileShape);
            //store board values
            std::string rowNames = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            char row = move.at(12);
            std::size_t find = rowNames.find_first_of(row);
            int rowAsInt = find;

            std::string col = move.substr(13);
            int colAsInt = std::stoi(col);

            std::cout << "Placing at  : " << rowAsInt << "," << colAsInt << std::endl;
            // if (row == 'A') {
            //     rowAsInt = 1;
            // } else if(row == 'B') {
            //     rowAsInt = 2;
            // } else if (row == 'C') {
            //     rowAsInt = 3;
            // } else if (row == 'D') {
            //     rowAsInt = 4;
            // } else if (row == 'E') {
            //     rowAsInt = 5;
            // } else if (row == 'F') {
            //     rowAsInt = 6;
            // }
            // else {
            //     std::cout << "row doesn't exist" << std::endl;
            //     rowAsInt = -99999;
            // }

            //place the selectedTile to the board
            //validating the placement of tiles

            if(checkBoardTile(rowAsInt, colAsInt) == false)
            {
                std::cout<<"Invalid move"<<std::endl;
            }
            else if(!(compareTilesRow(selectedTile, rowAsInt, colAsInt)==true && compareTilesCol(selectedTile, rowAsInt, colAsInt) == true))
            {
                std::cout<<"Invalid move"<<std::endl;
            }
            /*
                For second conditions uncomment the below line and add suitable conditions...
                compareTilesRow(selectedTile, rowAsInt, colAsInt);
            */
            else if (board.placeTile(selectedTile,rowAsInt,colAsInt) == true) 
            {
                //remove the selectedTile from the playerHand
                getPlayer(currentPlayer)->removeTileFromPlayerHand(selectedTile);
                //add a new tile to the playerHand
                getPlayer(currentPlayer)->addTileToPlayerHand(bag->getOneTile());
                //getPlayer(currentPlayer)->getPlayerScore()+(calculateScore(rowAsInt,colAsInt) -> get player current score, and add the new calculated score
                getPlayer(currentPlayer)->updatePlayerScore(calculateScore(rowAsInt,colAsInt));
                std::cout << getPlayer(currentPlayer)->getPlayerScore() << std::endl;
                //Applying Win/Lose
                if(bag ->getTileBag() ->size() == 0)
                {
                    this ->applyWinLose();
                    std::cout << "You just finished playing a dumb game bro" << std::endl;
                }
                else
                {
                    switchRound();
                }
                correctInput = true;
            }

            // todo store input as board
        }
        else if(move.substr(0,7).compare("replace") == 0){
            char ReTileColour = move.at(8);
            char ReTileShape = move.at(9);
            int intReTileShape = ReTileShape -'0';

            Tile* tileToRemove = new Tile(ReTileColour,intReTileShape);
            
            //add the tile to the end of the bag, delete from player hand
            bag->getTileBag()->addBack(tileToRemove);
            getPlayer(currentPlayer)->removeTileFromPlayerHand(tileToRemove);
            //get a tile from front, add to player hand
            Tile* tileToAdd = bag->getOneTile();
            getPlayer(currentPlayer)->addTileToPlayerHand(tileToAdd);
            bag->getTileBag()->deleteTile(tileToAdd);
            getPlayer(currentPlayer)->getPlayerHand()->printToString();
            switchRound();
            correctInput = true;

        }
        //save as file
        else if (move.substr(0,4).compare("save")==0 && move.substr(5,2).compare("as") == 0){
            //get filename
            std::string saveFile = move.substr(8, move.length() - 8);
            
            //std::cout << outFile << std::endl;
            std::cout << "saving" << std::endl;
            GameEngine::saveGame(saveFile);
        }
        else if(move.substr(0,4).compare("quit")==0){
            std::cout << "You just finished playing a dumb game bro" << std::endl;
            correctInput = true;
        }
        else if(std::cin.eof()){
            std::cout << "EOF" << std::endl;
            correctInput = true;
        }
        else {
            std::cout << "Invalid input" << std::endl;
        }
        
    }
}

void GameEngine::saveGame(std::string saveFile){
    std::ofstream saveGameFile (saveFile + ".save");
    for (int i = 0; i < NUMBER_OF_PLAYERS; i ++){
        std::string playerHand = getPlayer(i)->getPlayerHand()->printToString();
        saveGameFile << getPlayer(i)->getPlayerName() << std::endl;
        saveGameFile << getPlayer(i)->getPlayerScore() << std::endl;
        saveGameFile << playerHand << std::endl;
    }

    saveGameFile << board.getBoardTileRow() << "," << board.getBoardTileCol() << std::endl;

    std::string currentBag = bag->getTileBag()->printToString();
    //saveGameFile << board.display() << std::endl;
    saveGameFile << board.displayBoardStateToString() << std::endl;
    saveGameFile << currentBag << std::endl;

    //convert board into string

    saveGameFile << getPlayer(currentPlayer)->getPlayerName() << std::endl;

    saveGameFile.close();
    std::cout << "Game successfully saved" << std::endl;
}


bool GameEngine::compareTilesRow(Tile* tile, int x , int y)
{
    int count = 0;
    bool flag = true;
    Tile* rowTile;

    int row = x+1;
    if(count == 0 && row < 26)
    {
        while(count ==0 && row < 26 && this->board.getTilefromBoard(row,y)!=nullptr)
        {
            rowTile = this->board.getTilefromBoard(row,y);
            if(!(rowTile->colour == tile ->colour || rowTile ->shape == tile ->shape) || (rowTile->colour == tile ->colour && rowTile ->shape == tile ->shape))
            {
                flag = false;
                count = 1;
            }
            row++;
        }
    }
    row = x-1;
    if(count == 0 && row >= 0)
    {
        while(count == 0 && this->board.getTilefromBoard(row,y)!=nullptr)
        {
            rowTile = this->board.getTilefromBoard(row,y);
            if(!(rowTile->colour == tile ->colour || rowTile ->shape == tile ->shape) || (rowTile->colour == tile ->colour && rowTile ->shape == tile ->shape))
            {
                flag = false;
                count = 1;
            }
            row--;
        }
    }
    //std::cout<<"End case: "<<flag<<std::endl;
    return flag;
}
bool GameEngine::compareTilesCol(Tile* tile, int x, int y)
{
    /*
        this method is not fully implemented follow the above method structure to fully implement it
    */
    int count = 0;
    Tile* colTile;
    bool flag = true;

    int col = y+1;
    if(count == 0 && col < 26)
    {
        while(count == 0 && col < 26 && this->board.getTilefromBoard(x,col)!=nullptr)
        {
            colTile = this->board.getTilefromBoard(x,col);
            if(!(colTile->colour == tile ->colour || colTile ->shape == tile ->shape) || (colTile->colour == tile ->colour && colTile ->shape == tile ->shape))
            {
                flag = false;
                count = 1;
            }
            col++;
        }
    }
    col = y-1;
    if(col>=0)
    {
        while(col >= 0 && this->board.getTilefromBoard(x,col)!=nullptr)
        {
            colTile = this->board.getTilefromBoard(x,col);
            if(!(colTile->colour == tile ->colour || colTile ->shape == tile ->shape) || (colTile->colour == tile ->colour && colTile ->shape == tile ->shape))
            {
                flag = false;
                count = 1;
            }
            col--;
        }
    }
    return flag;
}

Player* GameEngine::getPlayer(int index) {
    return playerListVector.at(index);
}

bool GameEngine::checkBoardTile(int x, int y)
{
    bool flag = false;
    if(board.getNumTiles()==0)
    {
        //Checking ehther any tile exists
        flag = true;
    }
    else
    {
        if(((x+1) < 26 && this->board.getTilefromBoard(x+1,y)!=nullptr))
        {
            flag = true;
        }
        else if(((x-1) >= 0 && this->board.getTilefromBoard(x-1, y)!=nullptr))
        {
            flag = true;
        }
        else if(((y+1) < 26 && this->board.getTilefromBoard(x,y+1)!=nullptr))
        {
            flag = true;
        }
        else if(((y-1) >= 0 && this->board.getTilefromBoard(x,y-1)!=nullptr))
        {
            flag = true;
        }
    }
    //std::cout<<"Directions calculated: "<<flag<<std::endl;
    return flag;
}

// (x+1,y) right
// (x-1, y) left
// (x,y+1) up
// (x,y-1) down
// calculating the score a player get in his turn ( one turn only )
int GameEngine::calculateScore(int x, int y){
    int score;
    int up = 0;         bool upDone = false;
    int down = 0;       bool downDone = false;
    int right = 0;      bool rightDone = false;
    int left = 0;       bool leftDone = false;
//Checking up side one by one if there's any tile to score
    while(upDone == false){
        if(this->board.getTilefromBoard(x, y+1)!=nullptr){
            up = 2;
            if(this->board.getTilefromBoard(x, y+2)!=nullptr){
                up = 3;
                if(this->board.getTilefromBoard(x, y+3)!=nullptr){
                    up = 4;
                    if(this->board.getTilefromBoard(x, y+4)!=nullptr){
                        up = 5;
                        if(this->board.getTilefromBoard(x, y+5)!=nullptr){
                            up = 12;
                            std::cout << "Qwirkle !!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
                    }
            else{
            upDone = true;
        }
        }
            else{
            upDone = true;
        }
        }
            else{
            upDone = true;
        }
        }
            else{
            upDone = true;
        }
        }
            else{
            upDone = true;
    }
}
//Checking left side one by one if there's any tile to score
    while(leftDone == false){
        if(this->board.getTilefromBoard(x-1, y)!=nullptr){
            left = 2;
            if(this->board.getTilefromBoard(x-2, y)!=nullptr){
                left = 3;
                if(this->board.getTilefromBoard(x-3, y)!=nullptr){
                    left = 4;
                    if(this->board.getTilefromBoard(x-4, y)!=nullptr){
                        left = 5;
                        if(this->board.getTilefromBoard(x-5, y)!=nullptr){
                            left = 12;
                            std::cout << "Qwirkle !!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
                    }
            else{
                leftDone = true;
        }
        }
            else{
                leftDone = true;
    
        }
        }
            else{
                leftDone = true;
    
        }
        }
            else{
                leftDone = true;
    
        }
        }
            else{
                leftDone = true;
    
    }
}
//Checking right side one by one if there's any tile to score
    while(rightDone == false){
        if(this->board.getTilefromBoard(x+1,y)!=nullptr){
            right = 2;
            if(this->board.getTilefromBoard(x+2,y)!=nullptr){
                right = 3;
                if(this->board.getTilefromBoard(x+3,y)!=nullptr){
                    right = 4;
                    if(this->board.getTilefromBoard(x+4,y)!=nullptr){
                        right = 5;
                        if(this->board.getTilefromBoard(x+5,y)!=nullptr){
                            right = 12;
                            std::cout << "Qwirkle !!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
                    }
            else{
            rightDone = true;
        }
        }
            else{
            rightDone = true;
        }
        }
            else{
            rightDone = true;
        }
        }
            else{
            rightDone = true;
        }
        }
            else{
            rightDone = true;
    }
}
//Checking down side one by one if there's any tile to score
    while(downDone == false){
        if(this->board.getTilefromBoard(x,y-1)!=nullptr){
            down = 2;
            if(this->board.getTilefromBoard(x,y-2)!=nullptr){
                down = 3;
                if(this->board.getTilefromBoard(x,y-3)!=nullptr){
                    down = 4;
                    if(this->board.getTilefromBoard(x,y-4)!=nullptr){
                        down = 5;
                        if(this->board.getTilefromBoard(x,y-5)!=nullptr){
                            down = 12;
                            std::cout << "Qwirkle !!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
                    }
            else{
            downDone = true;
        }
        }
            else{
            downDone = true;
        }
        }
            else{
            downDone = true;
        }
        }
            else{
            downDone = true;
        }
        }
            else{
            downDone = true;
    }
}
//The score of one turn
    score = up + down + left + right;
    std::cout << "calculated score" << score << std::endl;
    return score;
}

void GameEngine::applyWinLose()
{
    const int player1 = this ->currentPlayer;
    int player2 = player1;
    player2++;
    player2 = player2 %2;
    Player* p1 = getPlayer(player1);
    Player* p2 = getPlayer(player2);

    if(p1 ->getPlayerScore() > p2 ->getPlayerScore())
    {
        std::cout<<"Player: "<<p1 ->getPlayerName()<<" won by "<<(p1 ->getPlayerScore() - p2 ->getPlayerScore())<<" points!!!"<<std::endl;
    }
    else if(p1 ->getPlayerScore() < p2 ->getPlayerScore())
    {
        std::cout<<"Player: "<<p2 ->getPlayerName()<<" won by "<<(p2 ->getPlayerScore() - p1 ->getPlayerScore())<<" points!!!"<<std::endl;
    }
    else
    {
        std::cout<<"Game ended up in a Draw!!!"<<std::endl;
    }
}