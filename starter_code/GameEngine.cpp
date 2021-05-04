#include "GameEngine.h"
#include "Tile.h"
#include <iostream>
#include "Player.h"
#include "Bag.h"
#include "Board.h"

#define NUMBER_OF_PLAYERS 2 

GameEngine::GameEngine(std::string playerNames[],char randomChar) {
    for (int i = 0; i < NUMBER_OF_PLAYERS;i++) {
        Player* player = new Player(playerNames[i]);
        playerList[i] = player;
    }
    setupGame();
}

GameEngine::GameEngine(std::string playerNames[], int player1Score, int player1Hand,
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

}


void GameEngine::playGame() {
    
}