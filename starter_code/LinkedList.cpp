
#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
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
   unsigned int count = 1;

   while (count != i && i<=size() ){
      currentNode = currentNode->next;
      count++;
   }

   return currentNode;
};

void LinkedList::addFront(Tile* tile) {
   //if size is 0, create a new node and set new node to head
   if (size() == 0) {
      Node* newNode = new Node(tile,nullptr);
      head = newNode;
   }
   else {
      Node* newNode = new Node(tile,head);
      head = newNode;
   }
};

void LinkedList::deleteFront() {
   //if size is one, then set head to nullptr (reset linkedlist)  
   if ( size() == 1 )  {
      head = nullptr;
   } 
   //check if size is not equal to zero, if its 0 how to delete a node?
   else if ( size() != 0 ) {
      Node* tempNode = head;
      head = head->next;
      delete tempNode;
   }
};

void LinkedList::addBack(Tile* tile) {
   //if size is 0, create a new node and set head
   if (size() == 0) {
      Node* newNode = new Node(tile,nullptr);
      head = newNode;
   } 
   else {
      Node* currentNode = head;
      //loop to the back of the linkedlist
      while (currentNode->next != nullptr) {
         currentNode = currentNode->next;

      }
      Node* newNode = new Node(tile,nullptr);
      currentNode->next = newNode;
   }
}

void LinkedList::deleteBack() {
      //if size is one, then set head to nullptr (reset linkedlist)  
   if ( size() == 1) {
      head = nullptr;
   } 
   else if ( size() != 0 ) {
      //current is last node, previous is node before last node
      Node* currentNode = head;
      Node* previous = nullptr;
      while (currentNode->next != nullptr) {
         previous = currentNode;
         currentNode = currentNode->next;
      }
      previous->next = nullptr;
      delete currentNode;
   }
}

void LinkedList::insertNode(Tile* tile, unsigned int index) {
   //if index is greater than 0 AND index less equal to size()
   if (index >= 1 && index <= size()) {

      //since index 1 is the front of the list, just add node using addfront
      if ( index == 1 ) {
         addFront(tile);
      }
      else {
         Node* previousNode = nullptr;
         Node* currentNode = head;

         for (unsigned int i = 1; i < index; ++i) {
            previousNode = currentNode;
            currentNode = currentNode->next;
         }

         /*
            TO DO:
            P  NN  CN
            P->next = NN
            NN->next = CN
         */
         Node* newNode = new Node(tile,currentNode);
         previousNode->next = newNode;
      }
   }
}

void LinkedList::deleteAtIndex(unsigned int index) {
   Node* previousNode = nullptr;
   Node* currentNode = head;
   if (index == 1) {
      deleteFront();
   }
   else if ( index <= size() ) {
      for (unsigned int i = 1; i < index; ++i) {
         previousNode = currentNode;
         currentNode = currentNode->next;
      }

      /*
         TO DO:
         P CN CNN
         P->next = CN->next
         delete CN
      */
      previousNode->next = currentNode->next;
      delete currentNode;      
   }

}