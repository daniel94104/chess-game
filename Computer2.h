#ifndef __COMPUTER2_H__
#define __COMPUTER2_H__

#include "Player.h"

class Computer2 :public Player{
    public:
       Computer2();
       Move makeMove();
       //check if the move goes to (x,y).
       bool sameDest(Move m, int x, int y);
       Move getMove();
};

#endif
