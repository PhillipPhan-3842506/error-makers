
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
   void addBack(Tile* tile);

   /**
    * Insert a node into the linkedlist
    * index must be <= the size of the linkedlist
    */
   void insertNode(Tile* tile, unsigned int index);

   void deleteFront();
   void deleteBack();
   void deleteAtIndex(unsigned int index);

private:
   Node* head;
};

#endif // ASSIGN2_LINKEDLIST_H
