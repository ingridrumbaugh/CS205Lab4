#include "gameboard.h"

using namespace std;

GameToken g;

GameBoard::GameBoard() {
    gameActive = true;
    cols = 10;
    rows = 10;
    int *x = nullptr;
    gameboard = new int**[rows];

    for(int i = 0; i < rows; i ++) {
        gameboard[i] = new int*[cols];
    }

    for(int j = 0; j < rows; j ++) {
        for(int i = 0; i < cols; i ++) {
            gameboard[i][j] = nullptr;
        }
    }

}


GameBoard::GameBoard(int x_size, int y_size) {
    gameActive = true;
    x_size = cols;
    y_size = rows;
    int *x = nullptr;
    gameboard = new int**[rows];

    for(int i = 0; i < rows; i ++) {
        gameboard[i] = new int*[cols];
    }

    for(int j = 0; j < rows; j ++) {
        for(int i = 0; i < cols; i ++) {
            gameboard[i][j] = nullptr;
        }
    }

}

GameBoard::~GameBoard() {
    gameActive = false;
    for(int i = 0; i < rows; i ++) {
        delete gameboard[i];
    }
    delete gameboard;
}

void GameBoard::clear_board() {
    // Make all assignments null
    for(int j = 0; j < rows; j ++) {
        for(int i = 0; i < cols; i ++) {
            gameboard[i][j] = nullptr;
        }
    }
}

void GameBoard::restart_game() {
    p1score = 0;
    p2score = 0;
    clear_board();

}

void GameBoard::play_turn(int playernumber, std::string direction) {
    // playernumber --> i.e. p1, p2, robot1, robot2...

    if      (direction == "East")      { g.move_east(); }
    else if (direction == "West")      { g.move_west(); }
    else if (direction == "North")     { g.move_north(); }
    else if (direction == "South")     { g.move_south(); }
    else if (direction == "Northeast") { g.move_north_east(); }
    else if (direction == "Northwest") { g.move_north_west(); }
    else if (direction == "Southeast") { g.move_south_east(); }
    else if (direction == "Southwest") { g.move_south_west(); }
    else {
        throw std::invalid_argument("Type must be a valid direction");
    }
}

int GameBoard::getRows() {
    return rows;
}

int GameBoard::getCols() {
    return cols;
}

bool GameBoard::allowed_To_Move() {
    return allowedToMove;
}

void GameBoard::add_token(int type) {
    g = GameToken(type);
    g.add_to_play();
}

void GameBoard::perform_token_action(int tokenType, std::string actionType) {

}

int GameBoard::check_score() {
    return p1score-p2score;
}

int GameBoard::get_score(int player) {
    if      (player == 1) { return p1score; }
    else if (player == 2) { return p2score; }
    else {
        throw std::invalid_argument("Type must be a valid player #");
    }
}

bool GameBoard::game_finished() {
    return gameActive;
}

int GameBoard::game_count() {
    return numGames;
}

int GameBoard::turn_count(int player) {
    if      (player == 1) { return p1Turns; }
    else if (player == 2) { return p2Turns; }
    else {
        throw std::invalid_argument("Type must be a valid player #");
    }
}

void GameBoard::game_statistics() {

}

int xplace = 0;
int yplace = 0;
// 0 --> Player
void GameBoard::place_on_board(int tokenType, int x, int y) {
    g = GameToken(tokenType);
    g.add_to_play();
    g.set_position(x, y);
}


int* GameBoard::getTokenAtLocation(int x, int y) {
    return gameboard[x][y];
}

