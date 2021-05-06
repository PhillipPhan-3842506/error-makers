#ifndef ASSIGN2_GameEngine_H
#define ASSIGN2_GameEngine_H
#include <vector>
#include "Tile.h"
#include "Player.h"
#include "Board.h"
#include "Bag.h"
class GameEngine {
    public:
        GameEngine(std::string playerNames[], char randomChar);
        GameEngine(std::string playerNames[], int integer);
        GameEngine(std::string playerNames[], int player1Score, std::string player1Hand,
        std::string player2Hand, int player2Score, std::string boardShape, 
        std::string boardState, std::string tileBag, std::string currentPlayer);
        void start();
        void addPlayerToList(Player* player);
        void setupGame();
        void playGame();
        void switchRound();
        void playerMove();
        
    private:
        // std::vector< std::vector<Tile*> > board;
        Board board;
        Bag* bag;
        int currentPlayer;
        Player* playerList[];
};

#endif // ASSIGN2_GameEngine_H