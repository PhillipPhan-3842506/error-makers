#include "GameEngine.h"
#include "Tile.h"
#include <iostream>
#include "Player.h"
#include "Bag.h"
#include "Board.h"

#define NUMBER_OF_PLAYERS 2 

//This constructor is for making a new game
GameEngine::GameEngine(std::string playerNames[],char randomChar) {
    for (int i = 0; i < NUMBER_OF_PLAYERS;i++) {
        Player* player = new Player(playerNames[i]);
        playerList[i] = player;
    }
    setupGame();
}

//This constructor is for continue a game after a saved game file is loaded
GameEngine::GameEngine(std::string playerNames[], int player1Score, std::string player1Hand,
        std::string player2Hand, int player2Score, std::string boardShape, 
        std::string boardState, std::string tileBag, std::string currentPlayer) {
            
    for (int i = 0; i < NUMBER_OF_PLAYERS;i++) {
        Player* player = new Player(playerNames[i]);
        playerList[i] = player;
    }
    //to do : finish implementing code for hand
    //seperate playerHand to seperate tiles
    //create board + boardState
    //create new tilebag
    //set currentPlayer


    // playerList[0]->updatePlayerScore(player1Score);
    // playerList[0]->
    // playerList[1]->updatePlayerScore(player2Score);


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
    Board board;
    board.display();

    std::cout << "---------------------------" << std::endl;
    Bag* bag = new Bag();
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
        std::cout << playerList[i]->getPlayerName() << " has : " << std::endl;
        playerList[i]->getPlayerHand()->print();

    }
    std::cout << "bag contains : " << std::endl;
    bag->getTileBag()->print();

    playGame();
}

//The acutally gameplay
void GameEngine::playGame() {
    //prompt current player to go
    std::cout << playerList[currentPlayer]->getPlayerName() << ", it's your turn now" << std::endl;
    //display the score of each player
    for (int i = 0; i < NUMBER_OF_PLAYERS; i ++){
    std::cout << "score for " << playerList[i]->getPlayerName() << ": " << playerList[i]->getPlayerScore() << std::endl;
    }
    //display the current board

    //display the tiles in current player's hand
    std::cout << "Your hand is: " << std::endl;
    playerList[currentPlayer]->getPlayerHand()->print();

    playerMove();
}

//the function to switch turn bewteen players
void GameEngine::switchRound(){
    currentPlayer++;
    if (currentPlayer == NUMBER_OF_PLAYERS) {
        currentPlayer = 0;
    }
}

void GameEngine::playerMove(){
//    bool correctInput = false;
//    while (correctInput == false){
        std::string place;
        std::cin >> place;
        std::string hand;
        std::cin >> hand;
        std::string at;
        std::cin >> at;
        std::string co;
        std::cin >> co;

        std::cout << place << std::endl;
        std::cout << hand << std::endl;
        std::cout << at << std::endl;
        std::cout << co << std::endl;

        
//    }
}