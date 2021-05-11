
#include "LinkedList.h"
#include "ctype.h"
#include "GameEngine.h"
#include "Player.h"

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

#define MAX_NUMBER_PLAYERS 2
#define EXIT_SUCCESS    0

void menu();
void newGame();
void loadGame();
void credits();

//A value just for loop
bool run = true;

int main(void) {

    //Welcome
    std::cout << "Welcome to Qwirkle!!" << std::endl;
    std::cout << "--------------------" << std::endl;

    //Menu Loop, the menu will loop again after each finish
    while(run == true){
        menu();
    }

    std::cout << "Game has exited" << std::endl;
    return EXIT_SUCCESS;
}

//Display menu and select options
void menu(){

    //menu printed
    std::cout << "menu" << std::endl;
    std::cout << "----" << std::endl;
    std::cout << "1. New game" << std::endl;
    std::cout << "2. Load game" << std::endl;
    std::cout << "3. Credits(Show student information)" << std::endl;
    std::cout << "4. Quit" << std::endl;    
    
    //Menu option selector
    int choice;
    std::cout << ">";
    std::cin >> choice; 
    
    if (choice == 1){
        newGame();
        run = false;
    }
    else if (choice == 2){
        loadGame();
        run = false;
    }
    else if (choice == 3){
        credits();
        run = false;        
    }
    else if (choice == 4){
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

    std::string playerNames[]= {"",""};
    int numberOfPlayers = 0;

    std::cout << "\nStarting a New Game \n" << std::endl;

    std::cin.ignore();
    while ( !(std::cin.eof()) && (numberOfPlayers < MAX_NUMBER_PLAYERS) ) {
        std::cout << "Enter a name for player " << numberOfPlayers << " (uppercase characters only)" << std::endl;
        std::cout << ">";
        bool validate = false;
        std::string playerName;
        while (validate != true) {
            std::getline(std::cin,playerName);
            if (std::all_of(playerName.begin(), playerName.end(), [](unsigned char c){ return std::isupper(c); })){
                validate = true;
            }
            else{
                std::cout << "Invalid name, only uppercased name needed" << std::endl;
                validate = false;
            }            
        }

        playerNames[numberOfPlayers] = playerName;
        numberOfPlayers++;
    }
    std::cout << "Lets play\n" << std::endl;
    // int randomIntegerCauseCrash = 10101;
    // GameEngine(playerNames,randomIntegerCauseCrash);
    GameEngine(playerNames,numberOfPlayers);
    run = false;
}

    //Load a game from a file (not done yet, once done delete this msg)
    void loadGame(){
        std::cout << "Enter the fileanme from which to load the game" << std::endl << 
        "> ";
    // //read from input

        std::string filename;
        std::cin >> filename;

    //open file
        std::ifstream file(filename);
        std::string values[100];
    // //check if the file is read successfully
        if(!file){
            std::cout << "File is not read successfully" << std::endl;
        }
        else{
            int index = 0;
            while (!file.eof()) {
                std::string line;
                std::getline(file,line);
                values[index] = line;
                index++;
                
            }
        }

        std::string playerNames[] = {values[0],values[3]};
        int player1Score = std::stoi(values[1]);
        std::string player1Hand = values[2];
        int player2Score = std::stoi(values[4]);
        std::string player2Hand = values[5];
        std::string boardShape = values[6];
        std::string boardState = values[7];
        std::string tileBagString = values[8];
        std::string currentPlayerName = values[9];
        std::cin.ignore();
        GameEngine(playerNames,player1Score,player1Hand,
        player2Hand,player2Score,boardShape,boardState,tileBagString,currentPlayerName);

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
