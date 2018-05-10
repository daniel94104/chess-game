#include "Computer1.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Computer1::~Computer1(){
    for(std::vector<Piece *>::iterator i = pieces.begin(); i != pieces.end(); i++){
        delete *i;
    }
}

Move Computer1::makeMove(){
	vector<Move> moves;

	srand(time(NULL));
	for(vector<Piece *>::iterator i = pieces.begin(); i != pieces.end(); i++){
        vector<Move> temp = (*i)->getMoves();
        for(vector<Move>::iterator j = temp.begin(); j != temp.end(); j++){
            if(g->valid((*j), (*i))){
                moves.push_back((*j));
            }
        }           
    }

    Move final = moves[rand() % moves.size()];
    char x1 = final.x1 + 'a';
    char y1 = 7 - final.y1 + '1';
    char x2 = final.x2 + 'a';
    char y2 = 7 - final.y2 + '1';
    cout << "I'll move " << x1 << y1 << " to " << x2 << y2 << endl;
    return final;
}

Move Computer1::getMove(){
	string cmd;
	while(cin >> cmd){
		if(cmd == "move"){
			g->move(makeMove());
			break;
		}else{
			cout << "Command not recognized" << endl;
		}
	}
	Move m1;
	return m1;
}
