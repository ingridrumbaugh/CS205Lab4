#ifndef GAMETOKEN_H
#define GAMETOKEN_H
#include "baseclass.h"

class GameToken : public BaseClass {
public:

    GameToken(int inttype);

    GameToken();

    enum tokenType {Player, Robot, Trash, Wall};

    void set_position(int X, int Y);

    virtual tokenType what_are_you();

    void add_to_play();

    void remove_from_play();

    virtual void respond_to_neighbours(int x, int y); //Should be implemented seperately for every class

    void move_east();

    void move_west();

    void move_north();

    void move_south();

    void move_north_east();

    void move_north_west();

    void move_south_east();

    void move_south_west();

    int get_location_x();

    int get_location_y();

    bool get_state();

    tokenType get_type();


protected:
    int locationX ;
    int locationY ;
    bool active ;
    tokenType type;
   // GameBoard *board;

};

#endif // GAMETOKEN_H
