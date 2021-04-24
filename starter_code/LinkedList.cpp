
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