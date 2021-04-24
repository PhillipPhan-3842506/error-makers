
#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;

   // TODO
}

LinkedList::~LinkedList() {
   Node* currentNode = head;
   Node* nextNode;

   while (currentNode!=nullptr) {
      nextNode = currentNode->next;
      delete currentNode;
      currentNode = nextNode;
   }
}

//return length of LinkedList 
unsigned int LinkedList::size() {
   int length = 0;
   Node* currentNode = head;

   while (currentNode != nullptr) {
      length++;
      currentNode = currentNode->next;
   }

   return length;
};

//get Tile at given index
Node* LinkedList::getAtIndex(unsigned int i) {
   Node* currentNode = head;
   int count = 0;

   while (count != i && !( i > size()) ) {
      currentNode = currentNode->next;
      count++;
   }

   return currentNode;
};