#include "gametoken.h"

using namespace std;

GameToken::GameToken() {
    active = false;
    locationX = 0;
    locationY = 0;
}


GameToken::GameToken(int inttype){
    active = false;
    locationX = 0;
    locationY = 0;
    if      (inttype == 0) { type = tokenType::Player; }
    else if (inttype == 1) { type = tokenType::Robot;  }
    else if (inttype == 2) { type = tokenType::Trash;  }
    else if (inttype == 3) { type = tokenType::Wall;   }
    else {
        throw std::invalid_argument("Type must be an int 0-3");
    }

}

GameToken::tokenType GameToken::get_type() {
    return type;
}

void GameToken::set_position(int X, int Y){
    locationX = X;
    locationY = Y;
}

GameToken::tokenType GameToken::what_are_you(){
    return type;
}

void GameToken::add_to_play(){
    active = true;
}

void GameToken::remove_from_play(){
    active = false;
}

void GameToken::respond_to_neighbours(int x, int y){


} //Should be implemented seperately for every class

void GameToken::move_east(){
    locationX ++;
}

void GameToken::move_west(){
    locationX --;
}

void GameToken::move_north(){
    locationY ++;
}

void GameToken::move_south(){
    locationY --;
}

void GameToken::move_north_east(){
    locationX ++;
    locationY ++;
}

void GameToken::move_north_west(){
    locationY ++;
    locationX --;
}

void GameToken::move_south_east(){
    locationY --;
    locationX ++;
}

void GameToken::move_south_west(){
    locationX --;
    locationY ++;
}

int GameToken::get_location_x(){
    return locationX;
}

int GameToken::get_location_y(){
    return locationY;
}

bool GameToken::get_state(){
    return active;
}
