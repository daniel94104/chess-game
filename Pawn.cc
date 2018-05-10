#include "Pawn.h"
#include "Game.h"

using namespace std;


Pawn::Pawn(){
	setType('P');
    justEP = 0;
    enPassant = 0;
}

bool Pawn::getEp(){
    return enPassant;
}

void Pawn::setEp(bool b){
    if(!b){
        if(justEP){
            justEP = false;
        }else{
            enPassant  = b;
        }
    }else{
        justEP = true;
        enPassant = true;
    }
}



vector<Move> Pawn::getMoves(){
	vector<Move> moves;

    if((times == 1)&& first  && !game->pieceAt(x, y+yDirection) && !game->pieceAt(x, y + yDirection*2)){
        Move m = {x, y, x, y + yDirection*2};
        moves.push_back(m);
    }

    if(!game->pieceAt(x, y + yDirection)){
        Move m = {x, y, x, y + yDirection};
        moves.push_back(m);
    }

    if(x > 0 && game->pieceAt(x-1, y + yDirection) && 
        !sameCase(game->pieceAt(x-1, y + yDirection)->getType(), type)){
        Move m = {x, y, x-1, y + yDirection};
        moves.push_back(m);
    }

    if(x < 7 && game->pieceAt(x+1, y + yDirection) && 
        !sameCase(game->pieceAt(x+1, y + yDirection)->getType(), type)){
        Move m = {x, y, x+1, y+yDirection};
        moves.push_back(m);
    }

    //checking if could do enpassant.
    //check for first quadrant.
    if(x < 7 && game->pieceAt(x + 1,y)){
        if(!sameCase(type,game->pieceAt(x + 1, y)->getType()) && 
                    (game->pieceAt(x +1 , y)->getType() == 'p' || game->pieceAt(x +1 ,y)->getType() == 'P')){
            if(dynamic_cast<Pawn *>(game->pieceAt(x+1,y))->enPassant){
                Move m = {x,y, x+1, y + yDirection};
                moves.push_back(m);
            }
        }
    }
    if(x > 0 && game->pieceAt(x - 1, y)){
        if(!sameCase(game->pieceAt(x-1,y)->getType(),type) &&
                (game->pieceAt(x -1 , y)->getType() == 'p' || game->pieceAt(x -1 ,y)->getType() == 'P')){
            if(dynamic_cast<Pawn *>(game->pieceAt(x-1,y))->enPassant){
                Move m = {x,y,x-1,y+yDirection};
                moves.push_back(m);
            }
        }
    }
    return moves;
}
