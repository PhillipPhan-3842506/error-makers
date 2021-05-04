#ifndef ASSIGN2_GameEngine_H
#define ASSIGN2_GameEngine_H
#include <vector>
#include "Tile.h"
#include "Player.h"
class GameEngine {
    public:
        GameEngine();
        void start();
        void addPlayerToList(Player* player);
        void setupGame();
    private:
        std::vector< std::vector<Tile*> > board;
        std::vector<Player*> playerList;
};

#endif // ASSIGN2_GameEngine_H