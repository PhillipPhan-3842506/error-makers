
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();
   unsigned int size();
   Node* getAtIndex(unsigned int i);

   void addFront(Tile* tile);

   void deleteFront();

private:
   Node* head;
};

#endif // ASSIGN2_LINKEDLIST_H
