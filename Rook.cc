#include "Rook.h"
#include "Game.h"

using namespace std;


Rook::Rook(){
	setType('R');
}


vector<Move> Rook::getMoves(){
	vector<Move> moves;
    
    int x1 = getX();
    int y1 = getY();
    
    int xdir = getXDirection();
    int ydir = getYDirection();
    
    int vPositiveDir = 0;//positive vertical direction index.
    int vNegativeDir = 0;//negative vertical direction index.
    int hPositiveDir = 0;//positive horizontal direction index.
    int hNegativeDir = 0;//negative horizontal direction index.
    
    
    if(ydir < 0){
        vPositiveDir = -ydir;
        vNegativeDir = ydir;
    }
    else{
        vPositiveDir = ydir;
        vNegativeDir = -ydir;
    }
    if(xdir < 0 ){
        hPositiveDir = -xdir;
        hNegativeDir = xdir;
    }
    else{
        hPositiveDir = xdir;
        hNegativeDir = -xdir;
    }

    //get available step in vertical direction.
    for(int r = y1 + vPositiveDir; r <= 7; r= r + vPositiveDir){
        if(!game->pieceAt(x1, r) || !sameCase(game->pieceAt(x1,r)->getType(), type)){
            Move availble = {x1,y1,x1,r};
            moves.push_back(availble);
            //Stop when you reach a piece blocking the way
            if(game->pieceAt(x1,r)){
                    break;
                }


        }
        else{
            break;
        }
    }
    for(int r = y1 + vNegativeDir; r >= 0; r = r + vNegativeDir){
         if(!game->pieceAt(x1, r) || !sameCase(game->pieceAt(x1,r)->getType(), type)){
                Move availble = {x1,y1,x1,r};
                moves.push_back(availble);
                if(game->pieceAt(x1,r)){
                    break;
                }

        }

        else{
            break;
        }
    }

    //get available step in horizontal direction.
    for(int c = x1 + hPositiveDir; c <= 7; c= c+ hPositiveDir){
         if(!game->pieceAt(c, y1) || !sameCase(game->pieceAt(c,y1)->getType(), type)){
                Move availble = {x1,y1,c,y1};
                moves.push_back(availble);
                if(game->pieceAt(c,y1)){
                    break;
                }

        }

        else{
            break;
        }
    }
   for(int c = x1 + hNegativeDir; c >= 0; c= c+ hNegativeDir){
         if(!game->pieceAt(c, y1) || !sameCase(game->pieceAt(c,y1)->getType(), type)){
                Move availble = {x1,y1,c,y1};
                moves.push_back(availble);
                if(game->pieceAt(c,y1)){
                    break;
                }

        }

        else{
            break;
        }
   }


   return moves; 
}
