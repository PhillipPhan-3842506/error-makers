#ifndef ASSIGN2_GameEngine_H
#define ASSIGN2_GameEngine_H
#include <vector>
#include "Tile.h"
class GameEngine {
    public:
        GameEngine();
    private:
        std::vector< std::vector<Tile> > board;
};

#endif // ASSIGN2_GameEngine_H