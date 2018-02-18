#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include "gametoken.h"
#include <string>

class GameBoard {
public:
     GameBoard();
     GameBoard(int x_size, int y_size);
    ~GameBoard();

    void restart_game();

    void play_turn(int playernumber, std::string direction);

    void clear_board();

    // 1 --> player
    // 2 --> robot
    // 3 --> trash
    // 4 --> wall
    void add_token(int type);

    void perform_token_action(int tokenType, std::string actionType);

    void add_wall(int startx, int endx, int starty, int endy);

    bool get_wall_err();

    int check_score();

    int get_score(int player);

    bool game_finished();

    int game_count();

    // 1 or 2 for player 1 or player 2 
    int turn_count(int player);

    void game_statistics(); // No return type, print to command line

    // Replace with ID number later or something
    void place_on_board(int tokenType, int x, int y); // Throw error if exceeds board size
    
    int getRows();
    int getCols(); 
    bool allowed_To_Move();
    
    // 1 player, 2 robot, 3 trash, 4 wall
    int *getTokenAtLocation(int x, int y);

    int getNumTrash();
    int getNumPlayers();
    int getNumWalls();
    int getNumRobots();

protected:
    int rows;
    int cols;

    bool gameActive;
    bool whosTurn;
    bool spotOccupied;
    bool allowedToMove;
    bool wallError;

    int playerType; // = 1;
    int robotType;  // = 2;
    int trashType;  // = 3;
    int wallType;   // = 4;

    int numTokens;
    int numPlayers;
    int numRobots;
    int numTrash;
    int numWalls;

    int p1score;
    int p2score;
    int p1Turns; // Number of turns played by p1
    int p2Turns;
    int numGames;
    
    int ***gameboard;

    int whoWon; // 1 if P1 won, 2 if P2 won

};

#endif // GAMEBOARD_H
