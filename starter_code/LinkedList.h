
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

   std::string printToString();
   void swapNodes(int index1, int index2);
   void shuffle();
   Node* getTile(Tile* tile);
   Node* getTileWithColourShape(char COLOUR,int SHAPE);
   void deleteTile(Tile* tile);

private:
   Node* head;
};

#endif // ASSIGN2_LINKEDLIST_H
