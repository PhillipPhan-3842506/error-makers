#include "Bag.h"

Bag::Bag() {
    //create array of colours
    //create array of shapes
    tileBag = new LinkedList();
    Colour colours[6] = {RED,ORANGE,YELLOW,GREEN,BLUE,PURPLE};
    Shape shapes[6] = {CIRCLE,STAR_4,DIAMOND,SQUARE,STAR_6,CLOVER};

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            //create 3 of each tile
            for (int k = 0; k < 3;k++) {
                Tile* tile = new Tile(colours[i],shapes[j]);
                this->tileBag->addBack(tile);
            }
        }
    }
}

Tile* Bag::getOneTile() {
    return tileBag->getAtIndex(1)->tile;
}

LinkedList* Bag::getTileBag() {
    return this->tileBag;
}