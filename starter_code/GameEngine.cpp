#include "GameEngine.h"
#include "Tile.h"
#include "Player.h"
#include "Bag.h"
#include "Board.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <ios>
#include <limits>

#define NUMBER_OF_PLAYERS 2 

//This constructor is for making a new game
GameEngine::GameEngine(int toggle1, int toggle2, std::string playerNames[],int numberOfPlayers) {
    // for (int i = 0; i < NUMBER_OF_PLAYERS;++i) {
    //     // Player* player = new Player(playerNames[i]);
    //     // playerList[i] = player;
    //     playerList[i] = new Player(playerNames[i]);
    // }
    // playerList[0] = new Player(playerNames[0]);
    // playerList[1] = new Player(playerNames[1]);
    this ->toggle1 = toggle1;
    this ->toggle2 = toggle2;
    this ->numPlayers = numberOfPlayers;
    for(int i =0; i<this ->numPlayers; i++)
    {
        playerListVector.push_back(new Player(playerNames[i]));
    }
    setupGame();
}

//This constructor is for continue a game after a saved game file is loaded
GameEngine::GameEngine(int toggle1, int toggle2, int numPlayers, std::string playerNames[], int playerScore[], std::string playerHand[],
            std::string boardShape, std::string boardState, std::string tileBagString, std::string currentPlayerName) {
    this ->toggle1 = toggle1;
    this ->toggle2 = toggle2;
    this ->numPlayers = numPlayers;  
    for (int i = 0; i < this ->numPlayers;i++) {
        Player* player = new Player(playerNames[i]);
        playerListVector.push_back(player);
        //if the playername is the current player, make the current player equal to the player
        if (getPlayer(i)->getPlayerName() == currentPlayerName) {
            currentPlayer = i;
        }

    }
    for(int i = 0; i<this ->numPlayers; i++)
    {
        getPlayer(i)->setPlayerScore(playerScore[i]);
    }
    for(int i =0; i<this ->numPlayers; i++)
    {
        int size = playerHand[i].size();
        for(int j =0; j<size; j+=3)
        {
            char color = playerHand[i][j];
            int shape = playerHand[i][j+1] - '0';
            getPlayer(i) ->addTileToPlayerHand(new Tile(color, shape));
        }
    }
    /*std::istringstream ssPlayer1(player1Hand);
    std::istringstream ssPlayer2(player2Hand);
    std::string tokenPlayer1;
    std::string tokenPlayer2;
    std::vector<std::string> resultPlayer1;
    std::vector<std::string> resultPlayer2;*/

    //set player 1 hand
    /*while (std::getline(ssPlayer1,tokenPlayer1,',')) {
        resultPlayer1.push_back(tokenPlayer1);
    }
    for (size_t i = 0;i<resultPlayer1.size();i++) {

        char colour = resultPlayer1.at(i).substr(0,1)[0];
        int shape = std::stoi(resultPlayer1.at(i).substr(1));
        Tile* tile = new Tile(colour,shape);
        getPlayer(0)->addTileToPlayerHand(tile);
    }

    //set player 2 hand
    while (std::getline(ssPlayer2,tokenPlayer2,',')) {
        resultPlayer2.push_back(tokenPlayer2);
    }
    for (size_t i = 0;i<resultPlayer2.size();i++) {

        char colour = resultPlayer2.at(i).substr(0,1)[0];
        int shape = std::stoi(resultPlayer2.at(i).substr(1));
        Tile* tile = new Tile(colour,shape);
        getPlayer(1)->addTileToPlayerHand(tile);
    }*/

    //create bag from tileBagString
    bag = new Bag(tileBagString);


    board.load(boardState);
    //std::cin.ignore();
    playGame();
    delete bag;
    for(int i =0; i<this ->numPlayers; i++)
    {
        delete getPlayer(i);
    }
}

GameEngine::~GameEngine() {
//     std::cout << "gameengine destructor" << std::endl;
//     // delete bag;
//     // delete getPlayer(0);
//     // delete getPlayer(1);
}
/**
 * 
 * This method is responsible for setting up the game.
 * It does the following:
 *  creates the bag for the game, with a random order after calling shuffle
 *  this order remains the same for the current game Engine
 * 
 *  loops 2 times through the players it takes 6 tiles from the bag and giving them to the player hand
 * 
 * */
void GameEngine::setupGame() {
    currentPlayer = 0;
    //set up board
    // board.display();

    std::cout << "---------------------------" << std::endl;
    bag = new Bag();
    bag->getTileBag()->shuffle();

    //loops through players, assigns them 6 tiles each
    for (int i = 0; i < this ->numPlayers; i++) {
        //give 6 tiles per player
        for (int tiles = 0; tiles < 6; tiles++) {
            Tile* tileToAdd = bag->getOneTile();
            getPlayer(i)->addTileToPlayerHand(tileToAdd);
            //as player picked a tile from the front, remove the tile
            bag->getTileBag()->deleteTile(tileToAdd);

        }
        //std::cout << getPlayer(i)->getPlayerName() << " has : ";
        //std::cout<<getPlayer(i)->getPlayerHand()->printToString()<< std::endl;;

    }
    // std::cout << "bag contains : " << std::endl;
    bag->getTileBag()->printToString();
    std::cin.ignore();
    playGame();
    delete bag;
    for(int i =0; i<this ->numPlayers; i++)
    {
        delete getPlayer(i);
    }
}

//The acutally gameplay
void GameEngine::playGame() {
    //prompt current player to go
    log();
    playerMove();
//    switchRound();
}

//the function to switch turn bewteen players
void GameEngine::switchRound(){
    currentPlayer++;
    currentPlayer = currentPlayer%this->numPlayers;
    playGame(); 
}
// " place XX at XX"
void GameEngine::playerMove()
{
    bool correctInput = false;
    std::string move = "";
//check input correct
    while (correctInput == false){
//store user input as 4 strings
        std::cout << "> ";
        std::getline(std::cin, move);
        //std::cin>>move;
        //Input Validation
        //std::cin.ignore();
        if(move.compare("help")==0)
        {
            std::string line = "";
            std::ifstream file("help.txt");
            while(!file.eof())
            {
                std::getline(file, line);
                std::cout<<line<<std::endl;
            }
            correctInput = false;
        }
        /*else if(move.compare("placing")==0)
        {
            this ->placeMultiple();
            if(getPlayer(currentPlayer) ->getPlayerHand()->size() == 0)
            {
                board.display(toggle1, toggle2);
                getPlayer(currentPlayer) ->updatePlayerScore(6);//Bonus!!!
                this ->applyWinLose();
                // std::cout << "You just finished playing a dumb game bro" << std::endl;
            }
            else
            {
                switchRound();
            }
            correctInput = true;
        }*/
        /*else if((move.length()==14 || move.length() == 15) && (move.substr(0,5).compare("place") == 0 && move.substr(9,2).compare("at")==0 && isdigit(move.substr(13)[0]))){
            //store tile values
            char tileColour = move.at(6);
            char tileShape = move.at(7);
            int intTileShape = tileShape -'0';

            if (getPlayer(currentPlayer)->getPlayerHand()->getTileWithColourShape(tileColour,intTileShape) != nullptr) {
                //store input as tile
                Tile* selectedTile = getPlayer(currentPlayer)->getPlayerHand()->getTileWithColourShape(tileColour, intTileShape)->tile;
                //store board values
                std::string rowNames = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                char row = move.at(12);
                std::size_t find = rowNames.find_first_of(row);
                int rowAsInt = find;

                std::string col = move.substr(13);
                int colAsInt = std::stoi(col);
                
                //place the selectedTile to the board
                //validating the placement of tiles
                if(checkBoardTile(rowAsInt, colAsInt) == false)
                {
                    std::cout<<"Can't place at "<<row<<colAsInt<<" , to be placed near a previously existing tile on the board"<<std::endl;
                }
                else if(!(compareTilesRow(selectedTile, rowAsInt, colAsInt)==true && compareTilesCol(selectedTile, rowAsInt, colAsInt) == true))
                {
                    std::cout<<std::endl;
                }
                else if (board.placeTile(selectedTile,rowAsInt,colAsInt) == true) 
                {
                    //remove the selectedTile from the playerHand
                    getPlayer(currentPlayer)->removeTileFromPlayerHand(selectedTile);
                    //add a new tile to the playerHand
                    if (bag->getTileBag()->size() != 0) {
                        Tile* newTile = bag->getOneTile();
                        getPlayer(currentPlayer)->addTileToPlayerHand(newTile);
                        bag->getTileBag()->deleteTile(newTile);
                    }

                    //getPlayer(currentPlayer)->getPlayerScore()+(calculateScore(rowAsInt,colAsInt) -> get player current score, and add the new calculated score
                    getPlayer(currentPlayer)->updatePlayerScore(calculateScore(rowAsInt,colAsInt));
                    //Applying Win/Lose
                    if(getPlayer(currentPlayer) ->getPlayerHand()->size() == 0)
                    {
                        board.display(toggle1, toggle2);
                        getPlayer(currentPlayer) ->updatePlayerScore(6);//Bonus!!!
                        this ->applyWinLose();
                        // std::cout << "You just finished playing a dumb game bro" << std::endl;
                    }
                    else
                    {
                        switchRound();
                    }
                    correctInput = true;
                    
                }
            } else {
                std::cout << "Tile: "<<tileColour<<tileShape <<" is not found in the player's hand"<< std::endl;
            }

        }*/
        else if(move.length()==10 && move.substr(0,7).compare("replace") == 0){
            char ReTileColour = move.at(8);
            char ReTileShape = move.at(9);
            int intReTileShape = ReTileShape -'0';

            Tile* tileToRemove = new Tile(ReTileColour,intReTileShape);
            if (getPlayer(currentPlayer)->getPlayerHand()->getTileWithColourShape(ReTileColour,intReTileShape) != nullptr) {
                //add the tile to the end of the bag, delete from player hand
                bag->getTileBag()->addBack(tileToRemove);
                getPlayer(currentPlayer)->removeTileFromPlayerHand(tileToRemove);
                //get a tile from front, add to player hand
                Tile* tileToAdd = bag->getOneTile();
                getPlayer(currentPlayer)->addTileToPlayerHand(tileToAdd);
                bag->getTileBag()->deleteTile(tileToAdd);
                getPlayer(currentPlayer)->getPlayerHand()->printToString();
                switchRound();
                correctInput = true;
            }
            else {
                std::cout << "Tile: "<<ReTileColour<<ReTileShape<<" not found int the player's hand" << std::endl;
            }

        }
        //save as file
        else if (move.substr(0,5).compare("save ")==0){
            //get filename
            std::string saveFile = move.substr(5, move.length()-1);
            
            //std::cout << outFile << std::endl;
            std::cout << "saving" << std::endl;
            GameEngine::saveGame(saveFile);
        }
        else if(move.substr(0,4).compare("quit")==0){
            // std::cout << "You just finished playing a dumb game bro" << std::endl;
            correctInput = true;
        }
        else if(std::cin.eof()){
            correctInput = true;
        }
        else {
            std::cout << "Invalid Command !!! Please type 'help' for valid commands" << std::endl;
        }
    }
}

void GameEngine::saveGame(std::string saveFile){
    std::ofstream saveGameFile (saveFile + ".save");
    saveGameFile << this ->numPlayers <<std::endl;
    for (int i = 0; i < this ->numPlayers; i ++){
        std::string playerHand = getPlayer(i)->getPlayerHand()->printToString();
        saveGameFile << getPlayer(i)->getPlayerName() << std::endl;
        saveGameFile << getPlayer(i)->getPlayerScore() << std::endl;
        saveGameFile << playerHand << std::endl;
    }

    saveGameFile << board.getBoardTileRow() << "," << board.getBoardTileCol() << std::endl;

    std::string currentBag = bag->getTileBag()->printToString();
    //saveGameFile << board.display() << std::endl;
    saveGameFile << board.displayBoardStateToString() << std::endl;
    saveGameFile << currentBag << std::endl;

    //convert board into string

    saveGameFile << getPlayer(currentPlayer)->getPlayerName() << std::endl;

    saveGameFile.close();
    std::cout << "Game successfully saved" << std::endl;
}


bool GameEngine::compareTilesRow(Tile* tile, int x , int y)
{
    std::vector<Tile*> rowTileCollection;
    bool flag = true;
    Tile* rowTile;

    int row = x+1;
    if(row < 26)
    {
        while(row < 26 && this->board.getTilefromBoard(row,y)!=nullptr)
        {
            rowTile = this->board.getTilefromBoard(row,y);
            rowTileCollection.push_back(rowTile);
            row++;
        }
    }
    row = x-1;
    if(row >= 0)
    {
        while(row >=0 && this->board.getTilefromBoard(row,y)!=nullptr)
        {
            rowTile = this->board.getTilefromBoard(row,y);
            rowTileCollection.push_back(rowTile);
            row--;
        }
    }
    //To check whether the collections conatins any duplicate entries
    const int size = rowTileCollection.size();
    int i = 0, j=0;
    while(flag == true && i< size-1)
    {
        j = i+1;
        while(flag == true && j< size)
        {
            if(rowTileCollection[i]->colour == rowTileCollection[j] ->colour && rowTileCollection[i] ->shape == rowTileCollection[j] ->shape)
            {
                std::cout<<"Duplicate entry found in the Col Collection ("<<rowTileCollection[i] ->colour<<rowTileCollection[i] ->shape<<")";
                flag = false;
            }
            j++;
        }
        i++;
    }
    //Checking whether the tile is placable
    i = 0;
    while(flag == true && i< size)
    {
        if(!(rowTileCollection[i]->colour == tile ->colour || rowTileCollection[i] ->shape == tile ->shape))
        {
            std::cout<<"Tile to be placed: "<<tile ->colour<<tile ->shape<<" doesn't match with Col tile: "<<rowTileCollection[i] ->colour<<rowTileCollection[i] ->shape;
            flag = false;
        }
        if(flag == true && (rowTileCollection[i]->colour == tile ->colour && rowTileCollection[i] ->shape == tile ->shape))
        {
            std::cout<<"Duplicate entry found in the Col Collection ("<<rowTileCollection[i] ->colour<<rowTileCollection[i] ->shape<<")";
            flag = false;
        }
        i++;
    }
    return flag;
}
bool GameEngine::compareTilesCol(Tile* tile, int x, int y)
{
    std::vector<Tile*> colTileCollection;
    Tile* colTile;
    bool flag = true;

    int col = y+1;
    if(col < 26)
    {
        while(col < 26 && this->board.getTilefromBoard(x,col)!=nullptr)
        {
            colTile = this->board.getTilefromBoard(x,col);
            colTileCollection.push_back(colTile);
            col++;
        }
    }
    col = y-1;
    if(col>=0)
    {
        while(col >= 0 && this->board.getTilefromBoard(x,col)!=nullptr)
        {
            colTile = this->board.getTilefromBoard(x,col);
            colTileCollection.push_back(colTile);
            col--;
        }
    }
    //To check whether the collections conatins any duplicate entries
    const int size = colTileCollection.size();
    int i = 0, j=0;
    while(flag == true && i< size-1)
    {
        j = i+1;
        while(flag == true && j< size)
        {
            if(colTileCollection[i]->colour == colTileCollection[j] ->colour && colTileCollection[i] ->shape == colTileCollection[j] ->shape)
            {
                std::cout<<"Duplicate entry found in the Row Collection ("<<colTileCollection[i] ->colour<<colTileCollection[i] ->shape<<")";
                flag = false;
            }
            j++;
        }
        i++;
    }
    //Checking whether the tile is placable
    i = 0;
    while(flag == true && i< size)
    {
        if(!(colTileCollection[i]->colour == tile ->colour || colTileCollection[i] ->shape == tile ->shape))
        {
            std::cout<<"Tile to be placed: "<<tile ->colour<<tile ->shape<<" doesn't match with Row tile: "<<colTileCollection[i] ->colour<<colTileCollection[i] ->shape;
            flag = false;
        }
        if(flag==true && (colTileCollection[i]->colour == tile ->colour && colTileCollection[i] ->shape == tile ->shape))
        {
            std::cout<<"Duplicate entry found in the Row Collection ("<<colTileCollection[i] ->colour<<colTileCollection[i] ->shape<<")";
            flag = false;
        }
        i++;
    }
    return flag;
}

Player* GameEngine::getPlayer(int index) 
{
    return playerListVector.at(index);
}

bool GameEngine::checkBoardTile(int x, int y)
{
    bool flag = false;
    if(board.getNumTiles()==0)
    {
        //Checking ehther any tile exists
        flag = true;
    }
    else
    {
        if(((x+1) < 26 && this->board.getTilefromBoard(x+1,y)!=nullptr))
        {
            flag = true;
        }
        else if(((x-1) >= 0 && this->board.getTilefromBoard(x-1, y)!=nullptr))
        {
            flag = true;
        }
        else if(((y+1) < 26 && this->board.getTilefromBoard(x,y+1)!=nullptr))
        {
            flag = true;
        }
        else if(((y-1) >= 0 && this->board.getTilefromBoard(x,y-1)!=nullptr))
        {
            flag = true;
        }
    }
    //std::cout<<"Directions calculated: "<<flag<<std::endl;
    return flag;
}

// (x+1,y) right
// (x-1, y) left
// (x,y+1) up
// (x,y-1) down
// calculating the score a player get in his turn ( one turn only )
int GameEngine::calculateScore(int x, int y){
    int score;
    int up = 0;         bool upDone = false;
    int down = 0;       bool downDone = false;
    int right = 0;      bool rightDone = false;
    int left = 0;       bool leftDone = false;
//Checking up side one by one if there's any tile to score
    while(upDone == false){
        if(this->board.getTilefromBoard(x, y+1)!=nullptr){
            up = 2;
            if(this->board.getTilefromBoard(x, y+2)!=nullptr){
                up = 3;
                if(this->board.getTilefromBoard(x, y+3)!=nullptr){
                    up = 4;
                    if(this->board.getTilefromBoard(x, y+4)!=nullptr){
                        up = 5;
                        if(this->board.getTilefromBoard(x, y+5)!=nullptr){
                            up = 12;
                            std::cout << "Qwirkle !!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
                            upDone = true;
                    }
            else{
            upDone = true;
        }
        }
            else{
            upDone = true;
        }
        }
            else{
            upDone = true;
        }
        }
            else{
            upDone = true;
        }
        }
            else{
            upDone = true;
    }
}
//Checking left side one by one if there's any tile to score
    while(leftDone == false){
        if(this->board.getTilefromBoard(x-1, y)!=nullptr){
            left = 2;
            if(this->board.getTilefromBoard(x-2, y)!=nullptr){
                left = 3;
                if(this->board.getTilefromBoard(x-3, y)!=nullptr){
                    left = 4;
                    if(this->board.getTilefromBoard(x-4, y)!=nullptr){
                        left = 5;
                        if(this->board.getTilefromBoard(x-5, y)!=nullptr){
                            left = 12;
                            std::cout << "Qwirkle !!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
                            leftDone = true;
                    }
            else{
                leftDone = true;
        }
        }
            else{
                leftDone = true;
    
        }
        }
            else{
                leftDone = true;
    
        }
        }
            else{
                leftDone = true;
    
        }
        }
            else{
                leftDone = true;
    
    }
}
//Checking right side one by one if there's any tile to score
    while(rightDone == false){
        if(this->board.getTilefromBoard(x+1,y)!=nullptr){
            right = 2;
            if(this->board.getTilefromBoard(x+2,y)!=nullptr){
                right = 3;
                if(this->board.getTilefromBoard(x+3,y)!=nullptr){
                    right = 4;
                    if(this->board.getTilefromBoard(x+4,y)!=nullptr){
                        right = 5;
                        if(this->board.getTilefromBoard(x+5,y)!=nullptr){
                            right = 12;
                            std::cout << "Qwirkle !!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
                            rightDone = true;
                    }
            else{
            rightDone = true;
        }
        }
            else{
            rightDone = true;
        }
        }
            else{
            rightDone = true;
        }
        }
            else{
            rightDone = true;
        }
        }
            else{
            rightDone = true;
    }
}
//Checking down side one by one if there's any tile to score
    while(downDone == false){
        if(this->board.getTilefromBoard(x,y-1)!=nullptr){
            down = 2;
            if(this->board.getTilefromBoard(x,y-2)!=nullptr){
                down = 3;
                if(this->board.getTilefromBoard(x,y-3)!=nullptr){
                    down = 4;
                    if(this->board.getTilefromBoard(x,y-4)!=nullptr){
                        down = 5;
                        if(this->board.getTilefromBoard(x,y-5)!=nullptr){
                            down = 12;
                            std::cout << "Qwirkle !!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
                            downDone = true;
                    }
            else{
            downDone = true;
        }
        }
            else{
            downDone = true;
        }
        }
            else{
            downDone = true;
        }
        }
            else{
            downDone = true;
        }
        }
            else{
            downDone = true;
    }
}
//The score of one turn
    score = up + down + left + right;
    return score;
}

void GameEngine::applyWinLose()
{
    std::cout<<"\n********GAME***OVER**********\n"<<std::endl;
    std::cout<<"************RESULTS**************"<<std::endl;
    int highScore = getPlayer(0) ->getPlayerScore();
    for(int i =0; i<this ->numPlayers; i++)
    {
        if(highScore < getPlayer(i) ->getPlayerScore())
        {
            highScore = getPlayer(i) ->getPlayerScore();
        }
    }
    //Printing out results
    int i =0;
    while(i<this ->numPlayers)
    {
        std::cout<<"Player: "<<getPlayer(i) ->getPlayerName()<<" Points: "<<getPlayer(i) ->getPlayerScore()<<std::endl;
        if(highScore == getPlayer(i) ->getPlayerScore())
        {
            std::cout<<"Player: "<<getPlayer(i) ->getPlayerName()<<" won the game with "<<highScore<<" points"<<std::endl;
        }
        i++;
    }
}

void GameEngine::log()
{
    std::cout << std::endl;
    board.display(toggle1, toggle2);
    std::cout << getPlayer(currentPlayer)->getPlayerName() << ", it's your turn now" << std::endl;
    //display the score of each player
    for (int i = 0; i < this ->numPlayers; i ++){
    std::cout << "score for " << getPlayer(i)->getPlayerName() << ": " << getPlayer(i)->getPlayerScore() << std::endl;
    }
    //display the current board

    //display the tiles in current player's hand
    std::cout << "Your hand is: ";
    std::string hand = getPlayer(currentPlayer)->getPlayerHand()->printToString();
    const int size = hand.size();
    for(int i =0; i<size; i+=3)
    {
        char code = hand.substr(i,2).at(0);
        std::cout<<board.setColorTile(code, toggle1);
        std::cout<<hand.substr(i,1)<<board.setShape(std::stoi(hand.substr(i+1)), toggle2)<<"\033[38;5;15m";
        if(i == size -2)
        {
            std::cout<<std::endl;
        }
        else
        {
            std::cout<<",";
        }
    }   
}
void GameEngine::sort(std::vector<std::string> &coll)
{
    /*std::string a = coll.at(0);
    int pos = a.find(':');
    const int size = coll.size();
    for(int i =0; i<size-1; i++)
    {
        int num1 = std::stoi(coll.at(i).substr(coll.at(i).find(':')+2));
        for(int j=i+1; j<size; j++)
        {
            int num2 = std::stoi(coll.at(j).substr(coll.at(i).find(':')+2));

        }
    }
    int num = std::stoi(a.substr(pos+2)); */
}

void GameEngine::placeMultiple()
{
    //std::cin.ignore();
    std::string input = "";
    int n=0;
    bool flag = true;
    while(flag == true)
    {
        std::cout<<"Enter number of tiles to be placed :"<<std::endl;
        std::cout<<"> ";
        std::getline(std::cin, input);

        if(isdigit(input[0]))
        {
            n = input[0] - '0';
            if(n>0)
            {
                if(n<=int(this ->getPlayer(currentPlayer) ->getPlayerHand()->size()))
                {
                    flag = false;
                }
                else
                {
                    std::cout<<"Not that much tiles in the hand!!!"<<std::endl;
                }
            }
            else
            {
                std::cout<<"The number of tiles to be place must be more than 0"<<std::endl;
            }
        }
        else
        {
            std::cout<<"Invalid Input!!!!"<<std::endl;
        }
    }

    int i =1;
    //std::cin.ignore();
    while(i<=n)
    {
        std::cout<<"Cmd to place tile: "<<i<<std::endl;
        if(place()==0)
        {
            i = n+1;
        }
        else
        {
            i++;
        }
    }
}

int GameEngine::place()
{
    std::string move = "";
    bool flag = false;
    int ret = -1;

    while(flag == false)
    {
        std::cout << "> ";
        std::getline(std::cin, move);

        if(move.compare("help")==0)
        {
            std::string line = "";
            std::ifstream file("help.txt");
            while(!file.eof())
            {
                std::getline(file, line);
                std::cout<<line<<std::endl;
            }
            flag = false;
        }
        else if((move.length()==14 || move.length() == 15) && (move.substr(0,5).compare("place") == 0 && move.substr(9,2).compare("at")==0 && isdigit(move.substr(13)[0])))
        {
            //store tile values
            char tileColour = move.at(6);
            char tileShape = move.at(7);
            int intTileShape = tileShape -'0';

            if (getPlayer(currentPlayer)->getPlayerHand()->getTileWithColourShape(tileColour,intTileShape) != nullptr) {
                //store input as tile
                Tile* selectedTile = getPlayer(currentPlayer)->getPlayerHand()->getTileWithColourShape(tileColour, intTileShape)->tile;
                //store board values
                std::string rowNames = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                char row = move.at(12);
                std::size_t find = rowNames.find_first_of(row);
                int rowAsInt = find;

                std::string col = move.substr(13);
                int colAsInt = std::stoi(col);
                
                //place the selectedTile to the board
                //validating the placement of tiles
                if(checkBoardTile(rowAsInt, colAsInt) == false)
                {
                    std::cout<<"Can't place at "<<row<<colAsInt<<" , to be placed near a previously existing tile on the board"<<std::endl;
                }
                else if(!(compareTilesRow(selectedTile, rowAsInt, colAsInt)==true && compareTilesCol(selectedTile, rowAsInt, colAsInt) == true))
                {
                    std::cout<<std::endl;
                }
                else if (board.placeTile(selectedTile,rowAsInt,colAsInt) == true) 
                {
                    //remove the selectedTile from the playerHand
                    getPlayer(currentPlayer)->removeTileFromPlayerHand(selectedTile);
                    //add a new tile to the playerHand
                    if (bag->getTileBag()->size() != 0) {
                        Tile* newTile = bag->getOneTile();
                        getPlayer(currentPlayer)->addTileToPlayerHand(newTile);
                        bag->getTileBag()->deleteTile(newTile);
                    }

                    //getPlayer(currentPlayer)->getPlayerScore()+(calculateScore(rowAsInt,colAsInt) -> get player current score, and add the new calculated score
                    getPlayer(currentPlayer)->updatePlayerScore(calculateScore(rowAsInt,colAsInt));
                    //Applying Win/Lose
                    flag = true;
                    log();
                }
            } 
            else 
            {
                std::cout << "Tile: "<<tileColour<<tileShape <<" is not found in the player's hand"<< std::endl;
            }
        }
        else if(move.length()==10 && move.substr(0,7).compare("replace") == 0)
        {
            ret = 0;
            char ReTileColour = move.at(8);
            char ReTileShape = move.at(9);
            int intReTileShape = ReTileShape -'0';

            Tile* tileToRemove = new Tile(ReTileColour,intReTileShape);
            if (getPlayer(currentPlayer)->getPlayerHand()->getTileWithColourShape(ReTileColour,intReTileShape) != nullptr) {
                //add the tile to the end of the bag, delete from player hand
                bag->getTileBag()->addBack(tileToRemove);
                getPlayer(currentPlayer)->removeTileFromPlayerHand(tileToRemove);
                //get a tile from front, add to player hand
                Tile* tileToAdd = bag->getOneTile();
                getPlayer(currentPlayer)->addTileToPlayerHand(tileToAdd);
                bag->getTileBag()->deleteTile(tileToAdd);
                getPlayer(currentPlayer)->getPlayerHand()->printToString();
                //switchRound();
                flag = true;
            }
            else 
            {
                std::cout << "Tile: "<<ReTileColour<<ReTileShape<<" not found int the player's hand" << std::endl;
            }

        }
        else if (move.substr(0,5).compare("save ")==0){
            //get filename
            std::cout<<"Can't save a file while placing"<<std::endl;
            
            flag = false;
        }
        else if(move.substr(0,4).compare("quit")==0)
        {
            std::cout<<"Can't quit while placing"<<std::endl;
            flag = false;
        }
        else
        {
            std::cout<<"Invalid Command !!! Please type 'help' for valid commands"<<std::endl;
        }
    }
    return ret;   
}
