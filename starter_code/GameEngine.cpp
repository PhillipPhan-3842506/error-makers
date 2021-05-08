#include "GameEngine.h"
#include "Tile.h"
#include "Player.h"
#include "Bag.h"
#include "Board.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define NUMBER_OF_PLAYERS 2 

//This constructor is for making a new game
GameEngine::GameEngine(std::string playerNames[],int numberOfPlayers) {
    // for (int i = 0; i < NUMBER_OF_PLAYERS;++i) {
    //     // Player* player = new Player(playerNames[i]);
    //     // playerList[i] = player;
    //     playerList[i] = new Player(playerNames[i]);
    // }
    playerList[0] = new Player(playerNames[0]);
    playerList[1] = new Player(playerNames[1]);
    setupGame();
}

//This constructor is for continue a game after a saved game file is loaded
GameEngine::GameEngine(std::string playerNames[], int player1Score, std::string player1Hand,
        std::string player2Hand, int player2Score, std::string boardShape, 
        std::string boardState, std::string tileBagString, std::string currentPlayerName) {
            
    for (int i = 0; i < NUMBER_OF_PLAYERS;i++) {
        Player* player = new Player(playerNames[i]);
        //if the playername is the current player, make the current player equal to the player
        if (playerNames[i] == currentPlayerName) {
            currentPlayer = i;
        }
        playerList[i] = player;
    }

    //set player 1 score + hand
    playerList[0]->updatePlayerScore(player1Score);
    //set player 2 score
    playerList[1]->updatePlayerScore(player2Score);

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
        playerList[0]->addTileToPlayerHand(tile);
    }

    //set player 2 hand
    while (std::getline(ssPlayer2,tokenPlayer2,',')) {
        resultPlayer2.push_back(tokenPlayer2);
    }
    for (size_t i = 0;i<resultPlayer2.size();i++) {

        char colour = resultPlayer2.at(i).substr(0,1)[0];
        int shape = std::stoi(resultPlayer2.at(i).substr(1));
        Tile* tile = new Tile(colour,shape);
        playerList[1]->addTileToPlayerHand(tile);
    }

    //create bag from tileBagString
    bag = new Bag(tileBagString);

    playGame();
    //boardState


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
            playerList[i]->addTileToPlayerHand(tileToAdd);
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
    std::cout << playerList[currentPlayer]->getPlayerName() << ", it's your turn now" << std::endl;
    //display the score of each player
    for (int i = 0; i < NUMBER_OF_PLAYERS; i ++){
    std::cout << "score for " << playerList[i]->getPlayerName() << ": " << playerList[i]->getPlayerScore() << std::endl;
    }
    //display the current board

    //display the tiles in current player's hand
    std::cout << "Your hand is: " <<
    playerList[currentPlayer]->getPlayerHand()->printToString() << std::endl;
    
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
    std::string move;
//check input correct
    while (correctInput == false){
//store user input as 4 strings
        std::getline(std::cin, move);
        //std::cout << "\n " << std::endl;
        //std::cout << "place substring: " << move.substr(0,5) << std::endl;
        //std::cout << "at substring: " << move.substr(9,2) << std::endl;
        //std::cout << "tileColour substring: " << move.substr(6,2) << std::endl;
        //std::cout << "row/col substring: " << move.substr(12,2) << std::endl;
        std::cout << ">";

        
        if(move.substr(0,5).compare("place") == 0 && move.substr(9,2).compare("at")==0){
            //store tile values
            char tileColour = move.at(6);
            char tileShape = move.at(7);
            int intTileShape = tileShape -'0';

            // std::cout << tileColour << std::endl;
            // std::cout << tileShape  << std::endl;

            //store input as tile
            Tile* selectedTile = playerList[currentPlayer]->getPlayerHand()->getTileWithColourShape(tileColour, intTileShape);
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
            board.placeTile(selectedTile,rowAsInt,colAsInt);
            //remove the selectedTile from the playerHand
            playerList[currentPlayer]->removeTileFromPlayerHand(selectedTile);
            //add a new tile to the playerHand
            playerList[currentPlayer]->addTileToPlayerHand(bag->getOneTile());

            // std::cout<<"\nRule is gonna called\n";
            // this->gameRules(new Player("Alan"), rowAsInt-1, colAsInt);
            switchRound();
            correctInput = true;

            // todo store input as board
        }
        else if(move.substr(0,7).compare("replace") == 0){
            char ReTileColour = move.at(8);
            char ReTileShape = move.at(9);
            int intReTileShape = ReTileShape -'0';

            Tile* tileToRemove = new Tile(ReTileColour,intReTileShape);
            
            //add the tile to the end of the bag, delete from player hand
            bag->getTileBag()->addBack(tileToRemove);
            playerList[currentPlayer]->removeTileFromPlayerHand(tileToRemove);
            //get a tile from front, add to player hand
            Tile* tileToAdd = bag->getOneTile();
            playerList[currentPlayer]->addTileToPlayerHand(tileToAdd);
            bag->getTileBag()->deleteTile(tileToAdd);
            playerList[currentPlayer]->getPlayerHand()->printToString();
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
            std::cout << "I am not thankful for playing" << std::endl;
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
    std::ofstream saveGameFile (saveFile + "save");
    for (int i = 0; i < NUMBER_OF_PLAYERS; i ++){
        std::string playerHand = playerList[i]->getPlayerHand()->printToString();
        saveGameFile << playerList[i]->getPlayerName() << std::endl;
        saveGameFile << playerList[i]->getPlayerScore() << std::endl;
        saveGameFile << playerHand << std::endl;
    }

    saveGameFile << board.getBoardTileRow() << std::endl;  
    saveGameFile << board.getBoardTileCol() << std::endl;

    std::string currentBag = bag->getTileBag()->printToString();
    saveGameFile << currentBag << std::endl;

    //convert board into string

    saveGameFile << playerList[currentPlayer]->getPlayerName() << std::endl;

    saveGameFile.close();
    std::cout << "Game successfully saved" << std::endl;
}

void GameEngine::gameRules(Player* p, int x, int y)
{
    Tile* a = this->board.getTilefromBoard(x,y);
    //Display col
    std::cout<<a->getTitleDetails()<<"\n";
    //this ->getTilesCol(x, y);
    //this ->getTilesRow(x, y);
}

/*void GameEngine::getTilesRow(int x , int y)
{
    int row = x+1;
    if(row < 6)
    {
        Tile* rowTile = this->board.getTilefromBoard(row,y);
        while(row < 6 && rowTile!=nullptr)
        {
            std::cout<<rowTile->getTitleDetails()<<"\n";
            row++;
            rowTile = this->board.getTilefromBoard(row,y);
        }
    }
    row = x-1;
    if(row>=0)
    {
        Tile* rowTile = this->board.getTilefromBoard(row,y);
        while(row >= 0 && rowTile!=nullptr)
        {
            std::cout<<rowTile->getTitleDetails()<<"\n";
            row--;
            rowTile = this->board.getTilefromBoard(row,y);
        }
    }
}*/
/*void GameEngine::getTilesCol(int x, int y)
{
    int col = y+1;
    if(col < 6)
    {
        Tile* colTile = this->board.getTilefromBoard(x,col);
        while(col < 6 && colTile!=nullptr)
        {
            std::cout<<colTile->getTitleDetails()<<"\n";
            col++;
            colTile = this->board.getTilefromBoard(x,col);
        }
    }
    col = y-1;
    if(col>=0)
    {
        Tile* colTile = this->board.getTilefromBoard(x,col);
        while(col >= 0 && colTile!=nullptr)
        {
            std::cout<<colTile->getTitleDetails()<<"\n";
            col--;
            colTile = this->board.getTilefromBoard(x,col);
        }
    }
}*/
/*bool GameEngine::matchTile(Tile* ptr, int x, int y)
{
    int col = y+1;
    if(col < 6)
    {
        Tile* colTile = this->board.getTilefromBoard(x,col);

    }
}*/
bool GameEngine::compareTiles(Tile* p, Tile* o)
{
    bool flag = false;
    if(p->getTitleDetails().compare(o->getTitleDetails()) == 0)
    {
        flag = true;
    }
    return flag;
}