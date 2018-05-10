#include "Knight.h"
#include "Game.h"

using namespace std;


Knight::Knight(){
    setType('N');
}

bool onBoard(int x, int y){
    return (x >= 0 && x <= 7) && (y >=0 && y <=7);
}

vector<Move> Knight::getMoves(){
    vector<Move> moves;



    if(onBoard(x+2, y+1) && (!game->pieceAt(x+2, y+1) || !sameCase(type, game->pieceAt(x+2, y+1)->getType()))){
        Move m = {x, y, x+2, y+1};
        moves.push_back(m);
    }

    if(onBoard(x+2, y-1) && (!game->pieceAt(x+2, y-1) || !sameCase(type, game->pieceAt(x+2, y-1)->getType()))){
        Move m = {x, y, x+2, y-1};
        moves.push_back(m);
    }

    if(onBoard(x+1, y+2) && (!game->pieceAt(x+1, y+2) || !sameCase(type, game->pieceAt(x+1, y+2)->getType()))){
        Move m = {x, y, x+1, y+2};
        moves.push_back(m);
    }

    if(onBoard(x-1, y+2) && (!game->pieceAt(x-1, y+2) || !sameCase(type, game->pieceAt(x-1, y+2)->getType()))){
        Move m = {x, y, x-1, y+2};
        moves.push_back(m);
    }

    if(onBoard(x-2, y+1) && (!game->pieceAt(x-2, y+1) || !sameCase(type, game->pieceAt(x-2, y+1)->getType()))){
        Move m = {x, y, x-2, y+1};
        moves.push_back(m);
    }

    if(onBoard(x-2, y-1) && (!game->pieceAt(x-2, y-1) || !sameCase(type, game->pieceAt(x-2, y-1)->getType()))){
        Move m = {x, y, x-2, y-1};
        moves.push_back(m);
    }
    if(onBoard(x+1, y-2) && (!game->pieceAt(x+1, y-2) || !sameCase(type, game->pieceAt(x+1, y-2)->getType()))){
        Move m = {x, y, x+1, y-2};
        moves.push_back(m);
    }

    if(onBoard(x-1, y-2) && (!game->pieceAt(x-1, y-2) || !sameCase(type, game->pieceAt(x-1, y-2)->getType()))){
        Move m = {x, y, x-1, y-2};
        moves.push_back(m);
    }

    return moves; ;
}
