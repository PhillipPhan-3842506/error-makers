
#include "LinkedList.h"
#include "ctype.h"

#include <fstream>
#include <iostream>
#include <string>

#define EXIT_SUCCESS    0

void menu();
void newGame();
void loadGame();
void credits();

//A value just for loop
bool run = true;

int main(void) {
    LinkedList* list = new LinkedList();
    delete list;
    
    //Welcome
    std::cout << "Welcome to Qwirkle!!" << std::endl;
    std::cout << "--------------------" << std::endl;

    //Menu Loop, the menu will loop again after each finish
    while(run == true){
        menu();
    }

    return EXIT_SUCCESS;
}

//Display menu and select options
void menu(void){

    //menu printed
    std::cout << "menu" << std::endl;
    std::cout << "----" << std::endl;
    std::cout << "1. New game" << std::endl;
    std::cout << "2. Load game" << std::endl;
    std::cout << "3. Credits(Show student information)" << std::endl;
    std::cout << "4. Quit" << std::endl;    
    
    //Menu option selector
    int choice;
    std::cin >> choice; 
    
    if (choice == 1){
        newGame();
    }
    if (choice == 2){
        loadGame();
    }
    if (choice == 3){
        credits();        
    }
    if (choice == 4){
        std::cout << "Goodbye!" << std::endl;
        run = false;        
    }
    else{
        std::cout << "Invalid input, terminating...." << std::endl;
        std::cout << "------------------------------" << std::endl;
        run = false;
    }

}
   
   


//Start a new game
void newGame(){
//validate check value
bool validate = false;

//create player 1 and player 2
std::string player1 = "";
std::string player2 = "";

std::cout << "Starting a New Game" << std::endl;
std::cout << std::endl;

//Player1
while (validate == false){
    std::cout << "Enter a name for Player 1" << std::endl;
    std::cin >> player1;
    if (std::all_of(player1.begin(), player1.end(), [](unsigned char c){ return std::isupper(c); })){
        validate = true;
    }
    else{
        std::cout << "Invalid name, all uppercase needed" << std::endl;
    }
    validate = false;
    std::cout << std::endl;
}
//Player2
while (validate == false){
    std::cout << "Enter a name for Player 2" << std::endl;
    std::cin >> player2;
    if (std::all_of(player2.begin(), player2.end(), [](unsigned char c){ return std::isupper(c); })){
        validate = true;
    }
    else{
        std::cout << "Invalid name, all uppercase needed" << std::endl;
    }
    validate = false;
    std::cout << std::endl;


std::cout << "Let's Play\n";
}
}

//Load a game from a file (not done yet, once done delete this msg)
void loadGame(){
    std::cout << "Enter the fileanme from which to load the game" << std::endl;
//read from input
    std::string filename;
    std::cin >> filename;

//open file
    std::ifstream (filename);

//check if the file is read successfully
    if(!filename){
        std::cout << "File is not read successfully" << std::endl;
    }
    else{
        //todo (How the file is read) also check format
    }
}


//display student info
void credits(){
    
    std::cout << "Name: Yi.Zhan" << std::endl;
    std::cout << "Student ID:  s3761429" << std::endl;
    std::cout << "Email:  s3761429@student.rmit.edu.au" << std::endl;
    
    std::cout << std::endl;

    std::cout << "Name: Alan Linto" << std::endl;
    std::cout << "Student ID:  s3806891" << std::endl;
    std::cout << "Email:  s3806891@student.rmit.edu.au" << std::endl;

    std::cout << std::endl;

    std::cout << "Name: Phillip Phan" << std::endl;
    std::cout << "Student ID:  s3842506" << std::endl;
    std::cout << "Email:  s3842506@student.rmit.edu.au" << std::endl;
    
    std::cout << std::endl;

    std::cout << "Name: Ningthouba Meitei Nahakpam" << std::endl;
    std::cout << "Student ID:  s3733745" << std::endl;
    std::cout << "Email:  s3733745@student.rmit.edu.au" << std::endl;
}
