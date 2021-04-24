
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
   unsigned int count = 0;

   while (count != i && !( i > size()) ) {
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