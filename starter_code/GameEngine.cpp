#include "GameEngine.h"
#include "Tile.h"
#include <iostream>
#include "Player.h"
#include "Bag.h"
#include "Board.h"

GameEngine::GameEngine() {

}

void GameEngine::start() {
    std::cout << "Play game" << std::endl;

    setupGame();
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
    std::cout << "Tile bag: " << std::endl;
    std::cout << "---------------------------" << std::endl;

    //loop to set up cards
    std::vector<Player*> :: iterator iter;
    for (iter = playerList.begin(); iter != playerList.end(); iter++) {
        //get 6 tiles to add to players hand
        for (int i = 0; i < 6;i++) {
            //tile = get first tile
            Tile* tile = bag->getTileBag()->getAtIndex(1)->tile;
            // std::cout << tile->getTitleDetails() << std::endl;
            (*iter)->addTileToPlayerHand(tile);
            bag->getTileBag()->deleteFront();
        }
        std::cout << (*iter)->getPlayerName() << " hand contains: ";
        (*iter)->getPlayerHand()->print();
        std::cout << "--------------------------- " << std::endl;
    }
    bag->getTileBag()->print();
    }

//add player to playerlist so that gameengine can do things with each player
void GameEngine::addPlayerToList(Player* player) {
    playerList.push_back(player);
}