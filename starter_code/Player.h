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
        void setPlayerScore(int scoreToSet);
        bool getisAI();
        void setisAI(bool b);
    private:
        std::string name;
        unsigned int score;
        LinkedList* playerHand;
        bool is_ai = false;

};

#endif // ASSIGN2_PlAYER_H