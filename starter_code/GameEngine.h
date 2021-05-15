#ifndef ASSIGN2_GameEngine_H
#define ASSIGN2_GameEngine_H
#include <vector>
#include "Tile.h"
#include "Player.h"
#include "Board.h"
#include "Bag.h"
class GameEngine 
{
    public:
        GameEngine(std::string playerNames[], int numberOfPlayers);
        ~GameEngine();
        GameEngine(std::string playerNames[], int player1Score, std::string player1Hand,
        std::string player2Hand, int player2Score, std::string boardShape, 
        std::string boardState, std::string tileBagString, std::string currentPlayerName);
        Player* getPlayer(int index);
        void addPlayerToList(Player* player);
        void setupGame();
        void playGame();
        void switchRound();
        void playerMove();
        void saveGame(std::string saveFile);
        void applyWinLose();
        bool checkBoardTile(int x, int y);
        bool compareTilesCol(Tile* tile, int x, int y);
        bool compareTilesRow(Tile* tile, int x, int y);
        int calculateScore(int x, int y);
    private:
        Board* boardTiles;
        LinkedList tilebag;
        Board board;
        Bag* bag;
        int currentPlayer;
        // Player* playerList[];
        std::vector<Player*> playerListVector = {};
};

#endif // ASSIGN2_GameEngine_H