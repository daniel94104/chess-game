#include "King.h"
#include "Game.h"

using namespace std;


King::King(){
    setType('K');
    first = 1;
}





vector<Move> King::getMoves(){
    vector<Move> moves;
    //up
    if((y > 0) && (!game->pieceAt(x,y-1) || !sameCase(game->pieceAt(x, y-1)->getType(), type))){
        Move m = {x, y, x, y-1};
        moves.push_back(m);
    }

    //down
    if((y < 7) && (!game->pieceAt(x,y+1) || !sameCase(game->pieceAt(x, y+1)->getType(), type))){
        Move m = {x, y, x, y+1};
        moves.push_back(m);
    }

    //left
    if((x > 0) && (!game->pieceAt(x-1,y) || !sameCase(game->pieceAt(x-1, y)->getType(), type))){
        Move m = {x, y, x-1, y};
        moves.push_back(m);
    }

    //right
    if((x < 7) && (!game->pieceAt(x+1,y) || !sameCase(game->pieceAt(x+1, y)->getType(), type))){
        Move m = {x, y, x+1, y};
        moves.push_back(m);
    }

    //top left
    if(((x > 0) && (y > 0)) && (!game->pieceAt(x-1,y-1) ||
                !sameCase(game->pieceAt(x-1, y-1)->getType(), type))){
        Move m = {x, y, x-1, y-1};
        moves.push_back(m);
    }

    //bottom left
    if(((x > 0) && (y < 7)) && (!game->pieceAt(x-1,y+1) ||
                !sameCase(game->pieceAt(x-1, y+1)->getType(), type))){
        Move m = {x, y, x-1, y+1};
        moves.push_back(m);
    }

    //top right
    if(((x < 7) && (y > 0)) && (!game->pieceAt(x+1,y-1) || 
                !sameCase(game->pieceAt(x+1, y-1)->getType(), type))){
        Move m = {x, y, x+1, y-1};
        moves.push_back(m);
    }

    //bottom right
    if(((x < 7) && (y < 7)) && (!game->pieceAt(x+1,y+1) || 
                !sameCase(game->pieceAt(x+1, y+1)->getType(), type))){
        Move m = {x, y, x+1, y+1};
        moves.push_back(m);
    }

        return moves;
}
