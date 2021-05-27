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
        GameEngine(int toggle1, int toggle2, std::string playerNames[], int numberOfPlayers);
        ~GameEngine();
        GameEngine(int toggle1, int toggle2, int numPlayers, std::string playerNames[], int playerScore[], std::string playerHand[], std::string boardShape, 
        std::string boardState, std::string tileBagString, std::string currentPlayerName);
        Player* getPlayer(int index);
        void addPlayerToList(Player* player);
        void setupGame();
        void playGame();
        void switchRound();
        void playerMove();
        void sort(std::vector<std::string> &coll);
        void saveGame(std::string saveFile);
        void applyWinLose();
        void log();
        int place();
        void placeMultiple();
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
        int numPlayers;
        int toggle1, toggle2;
        // Player* playerList[];
        std::vector<Player*> playerListVector = {};
};

#endif // ASSIGN2_GameEngine_H