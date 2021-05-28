
#include "LinkedList.h"
#include "ctype.h"
#include "GameEngine.h"
#include "Player.h"

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

#define MAX_NUMBER_PLAYERS 2
#define MAX_PLAYER_WITH_AI 1
#define EXIT_SUCCESS    0

void menu();
void newGame();
void loadGame();
void credits();
void highScore();

//A value just for loop
bool run = true;
bool ai = false;

int main(int argc, char* argv[]) {

    //Welcome
    std::cout << "Welcome to Qwirkle!!" << std::endl;
    std::cout << "--------------------" << std::endl;
    if (argc >= 2) {
        if (    std::string(argv[1]) == "--ai" ) {
            std::cout << argv[1] << std::endl;
            ai = true;
        }
    }
    //Menu Loop, the menu will loop again after each finish
    while(run == true){
        menu();
    }

    std::cout << "Goodbye!" << std::endl;
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
    std::cout << "4. High Scores" << std::endl;
    std::cout << "5. Quit" << std::endl;    
    
    //Menu option selector
    
    int choice = 0;
        std::cout << "> ";
        std::string input = "";
        std::cin >> input; 

        //if eof, stop program
        //else change input to integer
        if (!std::cin.eof()) {
                choice = input[0]-'0';
        }
        else {
            run = false;
        }
            
        if (input == "help") {
            std::cout << "You are in the main menu. You can type a number from 1-4" <<
            " to select a choice \n" << std::endl;
        }
        else if (input == "^D") {
            run = false;
        }
        else if (choice == 1){
            newGame();
            run = false;
        }
        else if (choice == 2){
            loadGame();
            run = false;
        }
        else if (choice == 3){
            credits();     
        }
        else if (choice == 4) {
            highScore();
        }
        else if (choice == 5){
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
    bool endOfFileFound = false;
    std::cout << "\nStarting a New Game \n" << std::endl;
    std::cin.ignore();
    if (ai == true) {
        while ( numberOfPlayers < MAX_PLAYER_WITH_AI && endOfFileFound == false ) {
            std::cout << "Enter a name for player " << numberOfPlayers << " (uppercase characters only)" << std::endl;
            std::cout << "> ";
            bool validate = false;
            bool help = false;
            std::string playerName;
            while (validate != true && endOfFileFound != true && help == false) {
                std::cin >> playerName;
                if (playerName == "help") {
                    std::cout << "You are in the player create. You can type a name in full capitals and press enter \n" << std::endl;
                    help = true;
                }
                else if (playerName == "^D" || std::cin.eof()) {
                    endOfFileFound = true;
                }
                else if (std::all_of(playerName.begin(), playerName.end(), [](unsigned char c){ return std::isupper(c); })){
                    validate = true;
                    playerNames[numberOfPlayers] = playerName;
                    numberOfPlayers++;
                }
                else{
                    std::cout << "Invalid name, only uppercased name needed" << std::endl;
                    validate = false;
                }            
            }
        }
    } else {
        while ( numberOfPlayers < MAX_NUMBER_PLAYERS && endOfFileFound == false ) {
            std::cout << "Enter a name for player " << numberOfPlayers << " (uppercase characters only)" << std::endl;
            std::cout << "> ";
            bool validate = false;
            bool help = false;
            std::string playerName;
            while (validate != true && endOfFileFound != true && help == false) {
                std::cin >> playerName;
                if (playerName == "help") {
                    std::cout << "You are in the player create. You can type a name in full capitals and press enter \n" << std::endl;
                    help = true;
                }
                else if (playerName == "^D" || std::cin.eof()) {
                    endOfFileFound = true;
                }
                else if (std::all_of(playerName.begin(), playerName.end(), [](unsigned char c){ return std::isupper(c); })){
                    validate = true;
                    playerNames[numberOfPlayers] = playerName;
                    numberOfPlayers++;
                }
                else{
                    std::cout << "Invalid name, only uppercased name needed" << std::endl;
                    validate = false;
                }            
            }
        }
    }

    if (endOfFileFound == false) {
        std::cout << "Lets play\n" << std::endl;
        GameEngine(playerNames,numberOfPlayers,ai);
    }
    run = false;
}

    void loadGame(){
        std::cout << "Enter the filename from which to load the game" << std::endl << 
        "> ";
    // //read from input

        std::string filename;
        std::cin >> filename;
        while (filename == "help") {
            std::cout<<"You are in load. You can type in the directory of a save file and press enter \n"<<std::endl;
            std::cout << "Enter the filename from which to load the game" << std::endl << 
            "> ";
            std::cin >> filename;
        }



    //open file
        std::ifstream file(filename);
        std::string values[100];
    // //check if the file is read successfully
        if (filename == "^D" || std::cin.eof()) {
            run = false;
        } else {
            if(!file){
                std::cout << "File is not read successfully" << std::endl;
            }
            else{
                std::cout<<"\nQwirkle game successfully loaded\n"<<std::endl;
                int index = 0;
                while (!file.eof()) {
                    std::string line;
                    std::getline(file,line);
                    if (line[0] != '#') {
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
                std::string ai_in_save = values[10];
                //if the line found contains the bool true, then the ai was made
                bool ai_in_save_bool = false;
                if (ai_in_save == "true") {
                    ai_in_save_bool = true;
                }
                std::cin.ignore();
                GameEngine(playerNames,player1Score,player1Hand,
                player2Hand,player2Score,boardShape,boardState,tileBagString,currentPlayerName,ai_in_save_bool);

            }

        }

}


//display student info
void credits(){
    std::cout<<"\n-------Credits-------\n"<<std::endl;

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

void highScore() {
    std::ifstream file("highScoreFile.txt");
    std::string input;
    std::vector<int> scores;
    std::vector<std::string> names;
    std::vector<std::string> values;
    std::cout << "----" << std::endl;
    std::cout << "Top 3 scores" << std::endl;
    while (!file.eof()) {
        std::string line;
        std::getline(file,line);
        values.push_back(line);
        //add scores to a vector
    }
    //even index = name, odd index = score as format in save file is:
    //PLAYERNAME
    //SCORE
    //PLAYERNAME
    //SCORE
    for (size_t i = 0;i < values.size();i++) {
        if (i%2 == 0) {
            names.push_back(values[i]);
        } else {
            scores.push_back(std::stoi(values[i]));
        }
    }

    //for the top 3 scores
    for (size_t i = 0; i < scores.size() && i < 3;i++) {
        //find the index of the greatest score for the size of score vector
        int index_for_high_score = 0;
        for (size_t j = 0;j < scores.size();j++) {
            if (scores.at(j) > scores.at(index_for_high_score)) {
                index_for_high_score = j;
            }
        }
        //print for index and remove this value from the vector
        std::cout << names.at(index_for_high_score) << " - " << scores.at(index_for_high_score) << std::endl;
        names.erase(names.begin() + index_for_high_score);
        scores.erase(scores.begin() + index_for_high_score);
        
    }
    // std::sort(scores.begin(), scores.end(), std::greater<int>());
    // for (size_t i = 0; i < scores.size() && i < 5;i++) {
    //     if (i == 0) {
    //         std::cout << values.at(0) << " - " << scores.at(i) << std::endl;
    //     } else {
    //         std::cout << values.at(i-1) << " - " << scores.at(i) << std::endl;


}