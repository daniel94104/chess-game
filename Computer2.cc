#include "Computer2.h"
#include <cstdlib>
#include <ctime>


using namespace std;



Computer2::Computer2(){
};
Computer2::~Computer2(){
    for(std::vector<Piece *>::iterator i = pieces.begin(); i != pieces.end(); i++){
        delete *i;
    }
}
bool Computer2::sameDest(Move m,int x, int y){
    return (m.x2 == x && m.y2 == y);
}



Move Computer2::makeMove(){
    Piece *eKing = enemy->getKing();
    vector<Piece *> e = enemy->getPieces();
    vector<Piece *> me = getPieces();
    vector<Move> moves;
    //check move.
    cout << "Checking if we can put the enemy king in check" << endl;
    for(vector<Piece *>::iterator i = me.begin(); i != me.end();i++){
        vector<Move> pmove = (*i)->getMoves();
        for(vector<Move>::iterator j = pmove.begin();j != pmove.end(); j++){
            if(g->checkResult((*j),eKing->getX(),eKing->getY())){
                if(g->valid((*j), (*i))){     
                    moves.push_back((*j));
                }
            }
        }//end check move.
    }
    if(moves.size()){
        srand(time(NULL));
       // int index = rand() % moves.size();
       // cout << index << endl;
        return moves.at(rand() %moves.size());
    }

    //check capture move using canAttack.
    cout << "Checking if we can capture any enemy pieces" << endl;
    for(vector<Piece *>::iterator ep = e.begin();ep!=e.end();ep++){
        for(vector<Piece *>::iterator mp = me.begin(); mp != me.end(); mp++){
            vector<Move> mpmove = (*mp)->getMoves();
            for(vector<Move>::iterator j = mpmove.begin(); j != mpmove.end(); j++){
                if(sameDest((*j),(*ep)->getX(), (*ep)->getY())){
                    Move m = {(*mp)->getX(), (*mp)->getY(), (*ep)->getX(), (*ep)->getY()};
                    if(g->valid(m,(*mp))){
                        moves.push_back(m);
                    }
                }//end if
            }//end push my attack move
        }//end check my piece
    }//end check the enemy piece.
    

    if(moves.size()){
        srand(time(NULL));
        return moves[rand() % moves.size()];
    }

    cout << "Picking a random move" << endl;
    srand(time(NULL));
    for(vector<Piece *>::iterator i = me.begin(); i != me.end(); i++){
        vector<Move> temp = (*i)->getMoves();
        for(vector<Move>::iterator j = temp.begin(); j != temp.end(); j++){
            if(g->valid((*j), (*i))){
                moves.push_back((*j));
            }
        }           
    }
    cout << "Picked a random move" << endl;
 Move final = {-1,-1,-1,-1};
    if(moves.size()){
   final = moves[rand() % moves.size()];
    char x1 = final.x1 + 'a';
    char y1 = 7 - final.y1 + '1';
    char x2 = final.x2 + 'a';
    char y2 = 7 - final.y2 + '1';
    cout << "I'll move " << x1 << y1 << " to " << x2 << y2 << endl;
    }else{
        g->resign(this);
    }
    return final;
}

      
Move Computer2::getMove(){
    string cmd;
    while(cin >> cmd){
        if(cmd == "move"){
            Move m;
            do{
                cout << "Dog" << endl;
                m = makeMove();
                if(m.x1 == -1) break;
            }while(!g->move(m)); 
            return m;
        }
        else{
            cout << "command not recognized" << endl;
        }
    }
    Move m1;
    return m1;
}


