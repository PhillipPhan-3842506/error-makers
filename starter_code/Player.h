#ifndef ASSIGN2_PlAYER_H
#define ASSIGN2_PlAYER_H

#include "LinkedList.h"
#include <iostream>
#include <vector>

class Player {
    public:
        Player(std::string name);
        ~Player();
        std::string getPlayerName();
        int getPlayerScore();
        void updatePlayerScore(int score);
        LinkedList* getPlayerHand();
        void addTileToPlayerHand(Tile* tile);
        void removeTileFromPlayerHand(Tile* tileToRemove);
        Tile* getSpecificTile(Tile* tile);

    private:
        std::string name;
        unsigned int score;
        LinkedList* playerHand;

};

#endif // ASSIGN2_PlAYER_H