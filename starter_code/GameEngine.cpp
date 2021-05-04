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
