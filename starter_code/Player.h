#ifndef ASSIGN2_PlAYER_H
#define ASSIGN2_PlAYER_H

#include "LinkedList.h"
#include <iostream>
#include <vector>

class Player {
    public:
        Player();
    private:
        std::string name;
        LinkedList* playerTiles;

};

#endif // ASSIGN2_PlAYER_H