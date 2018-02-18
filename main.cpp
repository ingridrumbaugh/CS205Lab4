#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "../games/baseclass.h"
#include "../games/gametoken.h"
#include "../games/playertoken.h"
#include "../games/robottoken.h"
#include "../games/trashtoken.h"
#include "../games/walltoken.h"
#include "../games/gameboard.h"

#define ROWS 5
#define COLS 5

class FooTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    FooTest() {
        // You can do set-up work for each test here.
    }

    virtual ~FooTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Objects declared here can be used by all tests in the test case for Foo.
    GameToken *gameBoard[ROWS][COLS];

};

TEST(Constructor, TESTDEFAULTCONSTRUCT) {
    GameBoard gb;
    ASSERT_TRUE(gb.game_finished() == false);
    ASSERT_TRUE(gb.getRows() == 10);
    ASSERT_TRUE(gb.getCols() == 10); // Standard gameboard size
}

TEST(Constructor, TESTCUSTOMCONSTRUCT) {
    GameBoard gb2(5,5);
    ASSERT_TRUE(gb2.game_finished() == false);
    ASSERT_TRUE(gb2.getRows() == 5);
    ASSERT_TRUE(gb2.getCols() == 5);
}

TEST(Constructor, TESTDESTRUCTOR) {
    GameBoard gb;
    ASSERT_TRUE(gb.game_finished() == false);
    gb.~GameBoard();
    ASSERT_TRUE(gb.game_finished() == true);
}

// Make sure an error is thrown when you try to move
// onto a space that's already occupied
TEST(ExecutingTurn, TESTTURNS) {
    GameBoard gb;
    gb.add_token(1); // add a player
    gb.add_token(2); // add a robot
    gb.place_on_board(1, 1, 1);
    gb.place_on_board(2, 1, 2);

    std::string moveForward = "MoveForward";
    std::string moveRight   = "MoveRight";
    gb.perform_token_action(1, moveForward);
    ASSERT_TRUE(gb.allowed_To_Move() == false);
    gb.perform_token_action(1, moveRight);
    ASSERT_TRUE(gb.allowed_To_Move() == true);
}

// Make sure allowed to move bool is true
TEST(ExecutingTurn, TESTMOVESPACE) {
    GameBoard gb;
    gb.add_token(1); // add a player
    gb.place_on_board(1, 1, 1);
    std::string moveForward = "MoveForward";
    gb.perform_token_action(1, moveForward);
    ASSERT_TRUE(gb.allowed_To_Move() == true);
}

TEST(MoveToken, TESTLOCATION) {
    GameBoard gb;
    gb.add_token(1);
    gb.place_on_board(1, 1, 1);
    ASSERT_TRUE(gb.getTokenAtLocation(1,1) == 1);
    gb.place_on_board(1, 2, 2);
    ASSERT_TRUE(gb.getTokenAtLocation(2,2) == 1);
    ASSERT_TRUE(gb.getTokenAtLocation(1,1) == 0);
}

TEST(MoveToken, TESTMOVETWOTURNS) {
    GameBoard gb;
    gb.add_token(1);
    std::string dir = "Forward";
    gb.play_turn(1, dir);
    gb.play_turn(1, dir);
    ASSERT_TRUE(gb.allowed_To_Move() == false);
}

TEST(MoveToken, TESTTURNS) {
    GameBoard gb;
    gb.add_token(1);
    gb.add_token(1);
    std::string dir = "Forward";
    gb.play_turn(1, dir);
    gb.play_turn(2, dir);
    gb.play_turn(1, dir);

    ASSERT_TRUE(gb.turn_count(1) == 2);
    ASSERT_TRUE(gb.turn_count(2) == 1);
}

TEST(GameStatus, TESTMULTIPLEGAMES) {
    GameBoard gb1;
    ASSERT_TRUE(gb1.game_count() == 0);
    gb1.add_token(1);
    std::string right = "Right";
    gb1.play_turn(1,right);
    gb1.restart_game();
    gb1.add_token(1);
    gb1.play_turn(2,right);
    ASSERT_TRUE(gb1.game_count() == 2);
    gb1.~GameBoard();
    ASSERT_TRUE(gb1.game_count() == 0);
}

TEST(GameStatus, TESTROBOTCOLLISION) {
    GameBoard gb;
    gb.add_token(2);
    gb.add_token(2);
    // Robot collision
    gb.place_on_board(2, 1, 1);
    gb.place_on_board(2, 1, 1);
    ASSERT_TRUE(gb.getNumTrash() == 1);
    std::string rm = "Remove";
    gb.perform_token_action(2, rm);
    ASSERT_TRUE(gb.getNumTrash() == 0);
}

TEST(GameStatus, TESTSCORERESET) {
    GameBoard gb;
    gb.add_token(2);
    gb.add_token(1);
    gb.place_on_board(1, 1, 1);
    std::string dir = "Forward";
    gb.play_turn(1, dir);
    ASSERT_TRUE(gb.check_score() != 0);
    gb.restart_game();
    ASSERT_TRUE(gb.check_score() == 0);
}

TEST(GameStatus, TESTLOCATIONRESET) {
    GameBoard gb;
    gb.add_token(2);
    gb.add_token(1);
    gb.place_on_board(1, 1, 1);
    ASSERT_TRUE(gb.getTokenAtLocation(1,1) == 1);
    gb.restart_game();
    ASSERT_TRUE(gb.getTokenAtLocation(1,1) == 0);
}

TEST(AddTokens, TESTADDINGPLAYERS) {
    GameBoard gb;
    gb.add_token(1);
    gb.add_token(1);
    gb.add_token(1);
    // Should delete the 3rd player and not allow
    // there to be > 2 players
    ASSERT_TRUE(gb.getNumPlayers() == 2);
}

TEST(AddTokens, TESTADDWALL) {
    GameBoard gb;
    gb.add_wall(0,10,0,1);
    ASSERT_TRUE(gb.get_wall_err() == true);
    gb.~GameBoard();
    GameBoard gb2;
    gb.add_wall(0,1,0,10);
    ASSERT_TRUE(gb.get_wall_err() == true);
}

TEST(AddTokens, TESTADDTOKENS) {
    GameBoard geoff;
    geoff.add_token(1); // player
    geoff.add_token(2); // robot
    geoff.add_token(3); // trash
    geoff.add_wall(0,1,0,1); // wall

    ASSERT_TRUE(geoff.getNumPlayers() == 1);
    ASSERT_TRUE(geoff.getNumRobots()  == 1);
    ASSERT_TRUE(geoff.getNumTrash()   == 1);
    ASSERT_TRUE(geoff.getNumWalls()   == 1);

    std::string action = "Remove";
    geoff.perform_token_action(1, action);
    geoff.perform_token_action(2, action);
    geoff.perform_token_action(3, action);
    geoff.perform_token_action(4, action);

    ASSERT_TRUE(geoff.getNumPlayers() == 0);
    ASSERT_TRUE(geoff.getNumRobots()  == 0);
    ASSERT_TRUE(geoff.getNumTrash()   == 0);
    ASSERT_TRUE(geoff.getNumWalls()   == 0);
}


int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
