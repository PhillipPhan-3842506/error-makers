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

bool ai_in_game = false;

//This constructor is for making a new game
GameEngine::GameEngine(std::string playerNames[],int numberOfPlayers, bool ai) {
    //if program had --ai, then create an player and set the player to an ai, else just create player like normal
    ai_in_game = ai;
    if (ai_in_game) {
        Player* player1 = new Player(playerNames[0]);
        Player* ai = new Player("ai");
        ai->setisAI(true);
        playerListVector.push_back(player1);
        playerListVector.push_back(ai);

    } else {
        for (int i = 0; i < numberOfPlayers;++i) {
            playerListVector.push_back(new Player(playerNames[i]));
        }
    }
    setupGame();
}

//This constructor is for continue a game after a saved game file is loaded
GameEngine::GameEngine(std::string playerNames[], int player1Score, std::string player1Hand,
        std::string player2Hand, int player2Score, std::string boardShape, 
        std::string boardState, std::string tileBagString, std::string currentPlayerName, bool ai) {
            
    ai_in_game = ai;
    for (int i = 0; i < NUMBER_OF_PLAYERS;i++) {
        Player* player = new Player(playerNames[i]);
        playerListVector.push_back(player);
        //if the playername is the current player, make the current player equal to the player
        if (getPlayer(i)->getPlayerName() == currentPlayerName) {
            currentPlayer = i;
        }

    }

    //set player 1 score + hand
    getPlayer(0)->setPlayerScore(player1Score);
    //set player 2 score
    getPlayer(1)->setPlayerScore(player2Score);

    if (ai_in_game) {
      getPlayer(1)->setisAI(true);
    }
    //set player 2 as AI as AI is the second player always

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
    delete bag;
    delete getPlayer(0);
    delete getPlayer(1);
}

GameEngine::~GameEngine() {
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
    bag->getTileBag()->printToString(false);
    std::cin.ignore();
    playGame();
    delete bag;
    delete getPlayer(0);
    delete getPlayer(1);
}

//The acutally gameplay
void GameEngine::playGame() {
    //prompt current player to go
    std::cout << std::endl;
    board.display();
    std::cout << getPlayer(currentPlayer)->getPlayerName() << ", it's your turn now" << std::endl;
    //display the score of each player
    for (int i = 0; i < NUMBER_OF_PLAYERS; i ++){
    std::cout << "score for " << getPlayer(i)->getPlayerName() << ": " << getPlayer(i)->getPlayerScore() << std::endl;
    }
    //display the current board

    //display the tiles in current player's hand
    std::cout << "Your hand is: " <<
    getPlayer(currentPlayer)->getPlayerHand()->printToString(false) << std::endl;
    playerMove();
//    switchRound();
}

//the function to switch turn bewteen players
void GameEngine::switchRound(){
    currentPlayer++;
    currentPlayer = currentPlayer%2;
    playGame(); 
}

// " place XX at XX"
void GameEngine::playerMove(){
    bool correctInput = false;
    std::string move = "";
    if (getPlayer(currentPlayer)->getisAI() == true) {
        std::cout << "ai turn" << std::endl;
        aiPlace();
    }
    else {
    //check input correct
        while (correctInput == false){
    //store user input as 4 strings
            std::cout << "> ";
            std::getline(std::cin, move);
            if (move == "help") {
                std::cout << "You are in the player move. \n"
                << "You can place a tile by typing -> place <tile> at <location> \n"
                << "You can replace a tile by typing -> replace <tile> \n"
                << "You can save the game by typing -> save <filename> \n"
                << "You can quit the game by typing -> 'quit' \n" << std::endl;
            }
            //Input Validation
            else if((move.length()==14 || move.length() == 15) && (move.substr(0,5).compare("place") == 0 && move.substr(9,2).compare("at")==0 && isdigit(move.substr(13)[0]))){
                //store tile values
                char tileColour = move.at(6);
                char tileShape = move.at(7);
                int intTileShape = tileShape -'0';

                if (getPlayer(currentPlayer)->getPlayerHand()->getTileWithColourShape(tileColour,intTileShape) != nullptr) {
                    //store input as tile
                    Tile* selectedTile = getPlayer(currentPlayer)->getPlayerHand()->getTileWithColourShape(tileColour, intTileShape)->tile;
                    //store board values
                    std::string rowNames = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                    char row = move.at(12);
                    std::size_t find = rowNames.find_first_of(row);
                    int rowAsInt = find;

                    std::string col = move.substr(13);
                    int colAsInt = std::stoi(col);

                    //place the selectedTile to the board
                    //validating the placement of tiles
                    if (board.placeTile(selectedTile,rowAsInt,colAsInt) == true) 
                    {
                        //remove the selectedTile from the playerHand
                        getPlayer(currentPlayer)->removeTileFromPlayerHand(selectedTile);
                        //add a new tile to the playerHand
                        if (bag->getTileBag()->size() != 0) {
                            Tile* newTile = bag->getOneTile();
                            getPlayer(currentPlayer)->addTileToPlayerHand(newTile);
                            bag->getTileBag()->deleteTile(newTile);
                        }

                        //getPlayer(currentPlayer)->getPlayerScore()+(calculateScore(rowAsInt,colAsInt) -> get player current score, and add the new calculated score
                        getPlayer(currentPlayer)->updatePlayerScore(calculateScore(rowAsInt,colAsInt));
                        //Applying Win/Lose
                        if(getPlayer(currentPlayer) ->getPlayerHand()->size() == 0)
                        {
                            getPlayer(currentPlayer) ->updatePlayerScore(6);//Bonus!!!
                            this ->applyWinLose();
                            // std::cout << "You just finished playing a dumb game bro" << std::endl;
                        }
                        else
                        {
                            switchRound();
                        }
                        correctInput = true;
                        
                    }
                } else {
                    std::cout << "Invalid input" << std::endl;
                }

            }
            else if(move.length()==10 && move.substr(0,7).compare("replace") == 0){
                char ReTileColour = move.at(8);
                char ReTileShape = move.at(9);
                int intReTileShape = ReTileShape -'0';

                Tile* tileToRemove = new Tile(ReTileColour,intReTileShape);
                if (getPlayer(currentPlayer)->getPlayerHand()->getTileWithColourShape(ReTileColour,intReTileShape) != nullptr) {
                    //add the tile to the end of the bag, delete from player hand
                    bag->getTileBag()->addBack(tileToRemove);
                    getPlayer(currentPlayer)->removeTileFromPlayerHand(tileToRemove);
                    //get a tile from front, add to player hand
                    Tile* tileToAdd = bag->getOneTile();
                    getPlayer(currentPlayer)->addTileToPlayerHand(tileToAdd);
                    bag->getTileBag()->deleteTile(tileToAdd);
                    getPlayer(currentPlayer)->getPlayerHand()->printToString(false);
                    switchRound();
                    correctInput = true;
                }
                else {
                    std::cout << "Invalid input" << std::endl;
                }

            }
            //save as file
            else if (move.substr(0,4).compare("save")==0){
                //get filename
                std::string saveFile = move.substr(5, move.length()-1);
                
                //std::cout << outFile << std::endl;
                std::cout << "saving" << std::endl;
                GameEngine::saveGame(saveFile);
            }
            else if(move.substr(0,4).compare("quit")==0){
                // std::cout << "You just finished playing a dumb game bro" << std::endl;
                correctInput = true;
            }
            else if(std::cin.eof()){
                correctInput = true;
            }
            else {
                std::cout << "Invalid input" << std::endl;
            }
            
        }
    }
}

void GameEngine::saveGame(std::string saveFile){
    std::ofstream saveGameFile (saveFile + ".save");
    for (int i = 0; i < NUMBER_OF_PLAYERS; i ++){
        std::string playerHand = getPlayer(i)->getPlayerHand()->printToString(true);
        saveGameFile << getPlayer(i)->getPlayerName() << std::endl;
        saveGameFile << getPlayer(i)->getPlayerScore() << std::endl;
        saveGameFile << playerHand << std::endl;
    }

    saveGameFile << board.getBoardTileRow() << "," << board.getBoardTileCol() << std::endl;

    std::string currentBag = bag->getTileBag()->printToString(true);
    //saveGameFile << board.display() << std::endl;
    saveGameFile << board.displayBoardStateToString() << std::endl;
    saveGameFile << currentBag << std::endl;

    //convert board into string

    saveGameFile << getPlayer(currentPlayer)->getPlayerName() << std::endl;
    if (ai_in_game == true) {
        saveGameFile << "true";
    } else {
        saveGameFile << "false";
    }
    saveGameFile.close();
    std::cout << "Game successfully saved" << std::endl;
}




Player* GameEngine::getPlayer(int index) {
    return playerListVector.at(index);
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
                            upDone = true;
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
                            leftDone = true;
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
                            rightDone = true;
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
                            downDone = true;
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
    return score;
}

void GameEngine::applyWinLose()
{
    Player* p1 = getPlayer(0);
    Player* p2 = getPlayer(1);
    std::ofstream highScoreFile;
    highScoreFile.open ("highScoreFile.txt",std::ios_base::app);
    board.display();
    std::cout << p1 ->getPlayerScore() << std::endl;
    std::cout << p2 ->getPlayerScore() << std::endl;

    if(p1 ->getPlayerScore() > p2 ->getPlayerScore())
    {
        std::cout<<"Player: "<<p1 ->getPlayerName()<<" won by "<<(p1 ->getPlayerScore() - p2 ->getPlayerScore())<<" points!!!"<<std::endl;
        highScoreFile << p1 ->getPlayerName() << std::endl;
        highScoreFile << std::to_string(p1 ->getPlayerScore()) << std::endl;
    }
    else if(p1 ->getPlayerScore() < p2 ->getPlayerScore())
    {
        std::cout<<"Player: "<<p2 ->getPlayerName()<<" won by "<<(p2 ->getPlayerScore() - p1 ->getPlayerScore())<<" points!!!"<<std::endl;
        highScoreFile << p2 ->getPlayerName() << std::endl;
        highScoreFile << std::to_string(p2 ->getPlayerScore()) << std::endl;    }
    else
    {
        std::cout<<"Game ended up in a Draw!!!"<<std::endl;
    }
}

void GameEngine::aiPlace() {
    Player* ai = getPlayer(currentPlayer);
    int score = 0;
    Tile* winningTile = nullptr;
    int winningRow = 0;
    int winningCol = 0;
    /*
    for each tile in ai hand, for each row and column in table
    verify if placement is good
    if good, check the calculated score
    if calculated score is higher than previous, set new score and its tile placement
    */
    if (board.getNumTiles() == 0) {
        Tile* tile = ai->getPlayerHand()->getAtIndex(1)->tile;
        board.placeTile(tile,12,12);
        //remove the selectedTile from the playerHand
        getPlayer(currentPlayer)->removeTileFromPlayerHand(tile);
        //add a new tile to the playerHand
        if (bag->getTileBag()->size() != 0) {
            Tile* newTile = bag->getOneTile();
            getPlayer(currentPlayer)->addTileToPlayerHand(newTile);
            bag->getTileBag()->deleteTile(newTile);
        }

        getPlayer(currentPlayer)->updatePlayerScore(calculateScore(12,12));

        //Applying Win/Lose
        if(getPlayer(currentPlayer) ->getPlayerHand()->size() == 0)
        {
            getPlayer(currentPlayer) ->updatePlayerScore(6);//Bonus!!!
            this ->applyWinLose();
        }
        else {
            switchRound();
        }
    }
    else {
        for (int tile = 1; tile <= ai->getPlayerHand()->size();tile++) {
            Tile* selectedTile = ai->getPlayerHand()->getAtIndex(tile)->tile;
            for (int row = 0;row < 26;row++) {
                for (int col = 0;col<26;col++) {
                    if (board.validatePlaceTile(selectedTile,row,col) == true) {
                        if (calculateScore(row,col) > score) {
                            score = calculateScore(row,col);
                            winningTile = selectedTile;
                            winningRow = row;
                            winningCol = col;
                        }
                    }
                }
            }
        }
        if (winningTile != nullptr) {
            board.placeTile(winningTile,winningRow,winningCol);
            //remove the selectedTile from the playerHand
            getPlayer(currentPlayer)->removeTileFromPlayerHand(winningTile);
            //add a new tile to the playerHand
            if (bag->getTileBag()->size() != 0) {
                Tile* newTile = bag->getOneTile();
                getPlayer(currentPlayer)->addTileToPlayerHand(newTile);
                bag->getTileBag()->deleteTile(newTile);
            }

            getPlayer(currentPlayer)->updatePlayerScore(calculateScore(winningRow,winningCol));

            //Applying Win/Lose
            if(getPlayer(currentPlayer) ->getPlayerHand()->size() == 0)
            {
                getPlayer(currentPlayer) ->updatePlayerScore(6);//Bonus!!!
                this ->applyWinLose();
            }
            else {
                switchRound();
            }
        }
        else {
            //if no tiles to place, replace first tile
            Tile* tileToReplace = getPlayer(currentPlayer)->getPlayerHand()->getAtIndex(1)->tile;
            bag->getTileBag()->addBack(tileToReplace);
            getPlayer(currentPlayer)->removeTileFromPlayerHand(tileToReplace);
            //get a tile from front, add to player hand
            Tile* tileToAdd = bag->getOneTile();
            getPlayer(currentPlayer)->addTileToPlayerHand(tileToAdd);
            bag->getTileBag()->deleteTile(tileToAdd);
            getPlayer(currentPlayer)->getPlayerHand()->printToString(false);
            switchRound();
        }

    }
}