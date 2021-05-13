#ifndef ASSIGN2_BAG_H
#define ASSIGN2_BAG_H

#include "LinkedList.h"
#include "Tile.h"
#include "TileCodes.h"

class Bag {
    public:
        Bag();
        Bag(std::string tileBagString);
        Tile* getOneTile();
        LinkedList* getTileBag();
    private:
        LinkedList* tileBag;

//take from front, add to end
};

#endif // ASSIGN2_BAG_H