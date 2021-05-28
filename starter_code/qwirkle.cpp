
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
void createGame(int);
void loadGame();
void credits();
void options();

//A value just for loop
bool run = true;
//Values for toggling color/unicodes
int t1=0;
int t2=0;
int t3 = 0;

//Main Method Program Starts here........
int main(void) {

    //Welcome
    std::cout << "Welcome to Qwirkle!!" << std::endl;
    std::cout << "--------------------" << std::endl;

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
    std::cout << "4. Quit" << std::endl;
    std::cout << "5. Options" <<std::endl;    
    
    //Menu option selector
    int choice = 0;
    std::cout << "> ";
    std::string input = "";
    std::getline(std::cin, input); 
    
    //if eof, stop program
    //else change input to integer
    if (!std::cin.eof()) {
        choice = input[0]-'0';
    } else {
        run = false;
    }

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
    else if(choice == 4){
        run = false;
    }
    else if (choice == 5){
        options();
        std::cin.ignore();
        run = true;        
    }
    else if (choice == 0) {
        run=false;
    }
    else{
        std::cout << "Invalid input, terminating...." << std::endl;
        std::cout << "------------------------------" << std::endl;
        run = false;
    }

}
   
   


//Start a new game
void newGame(){

    /*std::string playerNames[]= {"",""};
    int numberOfPlayers = 0;
    bool endOfFileFound = false;*/
    
    std::cout << "\nStarting a New Game \n" << std::endl;


    if(t3!=0)
    {
    int numberPlayers = 0;
    std::string numPlayers = "";
    bool flag = true;
    while(flag == true)
    {
        std::cout<<"Enter the number of Players (3/4) : "<<std::endl;
        std::cout<<"> ";
        std::cin>>numPlayers;
        if(isdigit(numPlayers[0]) && numPlayers.size()==1)
        {
            numberPlayers = numPlayers[0] - '0';
            if(numberPlayers>2 && numberPlayers<5)
            {
                flag = false;
                createGame(numberPlayers);
            }
            else
            {
                std::cout<<"Must either 3 or 4 players for Mutiplayer"<<std::endl;
            }
        }
        else
        {
            std::cout<<"Invalid Input"<<std::endl;
        }
    }
    }
    else
    {
        createGame(MAX_NUMBER_PLAYERS);
    }
    /*while ( numberOfPlayers < MAX_NUMBER_PLAYERS && endOfFileFound == false ) {
        std::cout << "Enter a name for player " << numberOfPlayers << " (uppercase characters only)" << std::endl;
        std::cout << "> ";
        bool validate = false;
        std::string playerName;
        while (validate != true && endOfFileFound != true) {
            std::cin >> playerName;
            if (playerName == "^D" || std::cin.eof()) {
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
    if (endOfFileFound == false) {
        std::cout << "Lets play\n" << std::endl;
        GameEngine(playerNames,numberOfPlayers);
    }*/
    run = false;
}

    //Load a game from a file (not done yet, once done delete this msg)
    void loadGame(){
        std::cout << "Enter the fileanme from which to load the game" << std::endl << 
        "> ";
    // //read from input

        std::string filename;
        //std::getline(std::cin, filename);
        std::cin>>filename;
        //std::cout<<"Filename: "<<filename<<std::endl;
    //open file
        std::ifstream file(filename);
        std::string values[100];
    // //check if the file is read successfully
        if (filename == "^D" || std::cin.eof()) {
            run = false;
        } else 
        {
            if(!file){
                std::cout << "File is not read successfully" << std::endl;
            }
            else{
                std::cout<<"\nQwirkle game successfully loaded\n"<<std::endl;
                int index = 0;
                while (!file.eof()) {
                    std::string line;
                    std::getline(file,line);
                    values[index] = line;
                    index++;
                    
                }

                int number = 0;
                while(values[number].compare("26,26")!=0)
                {
                    number++;
                }
                const int numberPlayers = number/3;
                std::string playername[numberPlayers];
                std::string playerhand[numberPlayers];
                    
                    int playerscore[numberPlayers];
                    int i =0;
                    int j = 0;
                    int k =1;
                    int l =2;
                    while(i<numberPlayers)
                    {
                        playername[i] = values[j];
                        playerscore[i] = std::stoi(values[k]);
                        playerhand[i] = values[l];
                        j+=3;
                        k+=3;
                        l+=3;
                        i++;
                    }
                    std::string boardShape = values[index-5];
                    std::string boardState = values[index-4];
                    std::string tileBagString = values[index-3];
                    std::string currentPlayerName = values[index-2];
                    //std::cin.ignore();
                    
                    GameEngine load(t1, t2, numberPlayers,playername, playerscore, playerhand, boardShape, boardState, tileBagString, currentPlayerName);
                
                    /*std::string playerNames[] = {values[0],values[3]};
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
                    player2Hand,player2Score,boardShape,boardState,tileBagString,currentPlayerName);*/

            }


        }


}

void createGame(int numPlayers)
{
    int i =0;
    std::string playerName[numPlayers];
    std::string name ="";
    while(i < numPlayers)
    {
        std::cout << "Enter a name for player " << (i+1) << " (uppercase characters only)" << std::endl;
        std::cout << "> ";
        std::cin>>name;
        if(std::all_of(name.begin(), name.end(), [](unsigned char c){ return std::isupper(c); }))
        {
            playerName[i] = name;
            i++;
        }
        else
        {
            std::cout << "Invalid name, only uppercased name needed" << std::endl;
        }
    }
    std::cout << "Lets play\n" << std::endl;
    GameEngine newGame(t1, t2, playerName, numPlayers);
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

void options()
{
    //std::cin.ignore();
    std::cout<<"------------OPTIONS------------"<<std::endl;
    std::cout<<"1. Toggle tile color: "<<std::endl;
    std::cout<<"> ";
    std::cin>>t1;
    std::cout<<"2. Toggle tile shape: "<<std::endl;
    std::cout<<"> ";
    std::cin>>t2;
    std::cout<<"3. Toggle Multiplayer(3 to 4): "<<std::endl;
    std::cout<<"> ";
    std::cin>>t3;
}