#include "Queen.h"
#include "Game.h"

using namespace std;



Queen::Queen(){
    setType('Q');
}

vector<Move> Queen::getMoves(){
    vector<Move> moves;
    const int x1 = getX();
    const int y1 = getY();

    const int xdir = getXDirection();
    const int ydir = getYDirection();

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


    /* consider the location where the piece at as a (0,0), then construct a xy-axis.
     * Then we divide the steps that Bishop can go into four quadrants. Therefore, we need 
     * four loops to check where the Bishop can go.
     */

    int x = x1 + hPositiveDir;
    int y = y1 + vPositiveDir;
    //first quadrant
    while(x <= 7 && y <= 7){
        if(!game->pieceAt(x, y) || !sameCase(game->pieceAt(x,y)->getType(), type)){
            Move availble = {x1,y1,x,y};
            moves.push_back(availble);
            if(game->pieceAt(x,y)){
                break;
            }

        }
        else{
            break;
        }
        x += hPositiveDir;
        y += vPositiveDir;
    }

    x = x1 + hNegativeDir;
    y = y1 + vPositiveDir;
    //second quadrant
    while(x >= 0 && y <= 7){
        if(!game->pieceAt(x, y) || !sameCase(game->pieceAt(x,y)->getType(), type)){
            Move availble = {x1,y1,x,y};
            moves.push_back(availble);
            if(game->pieceAt(x,y)){
                break;
            }

        }
        else{
            break;
        }
        x += hNegativeDir;
        y += vPositiveDir;
    }//end while

    x = x1 + hNegativeDir;
    y = y1 + vNegativeDir;
    //third quadrant
    while(x >= 0 && y>=0){
        if(!game->pieceAt(x, y) || !sameCase(game->pieceAt(x,y)->getType(), type)){
            Move availble = {x1,y1,x,y};
            moves.push_back(availble);
            if(game->pieceAt(x,y)){
                break;
            }

        }
        else{
            break;
        }
        x += hNegativeDir;
        y += vNegativeDir;
    }//end while

    x = x1 + hPositiveDir;
    y = y1 + vNegativeDir;
    // forth quadrant
    while(x<= 7 && y >= 0){
        if(!game->pieceAt(x, y) || !sameCase(game->pieceAt(x,y)->getType(), type)){
            Move availble = {x1,y1,x,y};
            moves.push_back(availble);
            if(game->pieceAt(x,y)){
                break;
            }

        }

        else{
            break;
        }
        x += hPositiveDir;
        y += vNegativeDir;
    } // end while

    for(int r = y1 + vPositiveDir; r <= 7; r= r + vPositiveDir){ 
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
    for(int c = x1 + hNegativeDir; c  >= 0; c= c+ hNegativeDir){
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
