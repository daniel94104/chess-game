#include "Controller.h"
#include "TextDisplay.h"
#include "GraphicDisplay.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include "Knight.h"
#include "Computer1.h"
#include <string>
#include <iostream>
#include <fstream>
#include "Computer2.h"

using namespace std;

Controller::Controller(bool graphics){
	display = new TextDisplay;
	(graphics) ? gd = new GraphicDisplay : gd = NULL;
	white = NULL;
	black = NULL;
	game = NULL;
	turn = true;
}

Controller::~Controller(){
	delete game;
	delete display;
	delete black;
	delete white;
	delete gd;
}

Piece *Controller::createPiece(int x, int y, char p){
	Piece *n;
	bool white = (p >= 'A' && p <= 'Z'); //if it's upper case, it's a White piece

	char temp = p;
	int yDir = -1; //white moves up;
	if(!white){
		yDir = 1;
		temp -= 'a' - 'A'; //if it's upper case, make it lower;
	}

	switch(temp){
		case 'R':
			n = new Rook;
			break;
		case 'B':
			n = new Bishop;
			break;
		case 'N':
			n = new Knight;
			break;
		case 'Q':
			n = new Queen;
			break;
		case 'K':
			n = new King;
			break;
		case 'P':
			n = new Pawn;
			break;
		default:
			return NULL;
			break;
	}

	n->setX(x);
	n->setY(y);
	n->setType(p);
	n->setGame(game);
	white ? n->setOwner(this->white) : n->setOwner(black);
	if(temp == 'K') n->getOwner()->setKing(n);
    if(temp == 'P'){
        if(n->getY() == 6 || n->getY() == 1){
            n->setFirst(true);
            n->setTimes(1);
        }
        else{
            n->setFirst(false);
            n->setTimes(1);
        }
    }

	n->getOwner()->addPiece(n);
	n->setYDirection(yDir);
	n->setXDirection(1);
	return n;
}

void Controller::readBoard(istream &in){
	white->clear();
	black->clear();

	char cmd;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			in >> cmd;
			Piece *p = createPiece(j, i, cmd);
			char ret;
			p ? ret = p->getType() : ret = '_';
			game->init(j, i, p);
			
		}
	}
	in >> cmd;
	turn = cmd == 'W'; //Last line is a char that specifies first turn

}

string uCase(string in){
	string b;
	int len = in.length();
	for(int i = 0; i < len; i++){
		b += (in[i] >= 'a' && in[i] <= 'z') ? in[i] - 'a' : in[i];
	}
    cout << b << endl;
	return b;
}

Player *Controller::createPlayer(string type){
	Player *p;
	if(type == "human"){
		p = new Player;
		p->setSource(&cin);
	}else if(type == "computer1"){
		p = new Computer1;
	}else if(type == "computer2"){
	    cout << "Made new c2" << endl;
        p = new Computer2;
	}else{
		p = new Player;
		p->setSource(&cin);
	}
	return p;
}



Move str2move(const string &in, const string &in2){
	Move m;
	m.x1 = in[0] - 'a';
	m.y1 = 7 - (in[1] - '1');
	m.x2 = (in2[0] - 'a');
	m.y2 = 7 - (in2[1] - '1');
	return m;
}

void Controller::setup(){
	cout << "Entered Setup mode:" << endl;
	string cmd;
	delete white;
	delete black;
	delete game;
	white = createPlayer("human");
	black = createPlayer("human");
	
	game = new Game(white, black);
	white->setGame(game);
	black->setGame(game);
	game->setNotification(this);
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			game->init(i, j, NULL);
		}
	}
	display->print(cout);
	while(cin >> cmd){
		if(cmd == "+"){
			string piece, cords;
			cin >> piece;
			cin >> cords;
			Move m = str2move(cords, "a1");

			//check for multiple kings
			if((piece[0] == 'k' && black->getKing()) || (piece[0] == 'K' && white->getKing())){
				cout << "You cannot have more than one king" << endl;
			}else if(!game->pieceAt(m.x1, m.y1)){
				Piece * p = createPiece(m.x1, m.y1, piece[0]);
				game->init(m.x1, m.y1, p);
				display->print(cout);
			}else{
				cout << "There is a piece already at " << cords << endl;
			}
		}else if(cmd == "-"){
			string cords;
			cin >> cords;
			Move m = str2move(cords, "a1");
			if(game->validMove(m) && game->pieceAt(m.x1, m.y1)){
				if(game->pieceAt(m.x1, m.y1)->getType() == 'K' ||
					game->pieceAt(m.x1, m.y1)->getType() == 'k'){
					game->pieceAt(m.x1, m.y1)->getOwner()->setKing(NULL);
				}
				game->pieceAt(m.x1, m.y1)->getOwner()->removePiece(game->pieceAt(m.x1, m.y1));
				game->init(m.x1, m.y1, NULL);

			}else{
				cout << "No piece at " << cords << endl;
			}
			display->print(cout);
		}else if(cmd == "done"){
			if(game->valid()){
				break;
			}else{
				cout << "Board is invalid, cannot leave set up mode" << endl;
			}
		}else if(cmd == "="){
			string color;
			cin >> color;
			turn = color == "white";
		}else{
			cout << "Command not recognized" << endl;
		}
	}


}

void Controller::play(){

	string cmd, cmd2;
	bool quit = false;
	bool set = false;
	cout << "Welcome to Chess(tm)" << endl;	
	while(!quit){
	cout << "Currently, the commands are: " << endl;
	cout << "game [player] [player], where player is either human or computer[1-4]" << endl;
	cout << "setup - enter mode where you can add and drop pieces from the board" << endl;
		while(cin >> cmd){
		
			if(cmd == "game"){
				cin >> cmd;
				cin >> cmd2;

				if(!set){
				delete white;
				delete black;
				delete game;

				white = createPlayer(cmd);
				black = createPlayer(cmd2);

				game = new Game(white, black);
				white->setGame(game);
				black->setGame(game);
                white->setEnemy(black);
                black->setEnemy(white);
				game->setNotification(this);
				ifstream ifs(file);
				readBoard(ifs);
				display->print(cout);
			}
				cout << "The current commands are: move [startpos] [endpos], list [pos], quit"
					 << endl;
				
				cout << "Game Started!" << endl;

				while(game->status()){
					if(game->status() == 2){
						cout << "Check on white's king" << endl; 
					}else if(game->status() == 3){
						cout << "Check on black's king" << endl;
					}
					if(turn){
						cout << "White's turn" << endl;
						white->getMove();
					}else{
						cout << "Black's turn" << endl;
						black->getMove();
					}
					display->print(cout);
					turn = !turn;				
				}

				if(game->getWinner()->getKing()->getType() == 'K'){
					black = NULL;
					cout << "~Checkmate~" << endl;
					cout << "White wins!" << endl;
				}else{
					white = NULL;
					cout << "~Checkmate~" << endl;
					cout << "Black wins!" << endl;
				}
				break;

			}else if(cmd == "setup"){
				setup();
				set = true;
			}else if(cmd == "quit"){
				quit = true;
				break;
			}else{
				cout << "Command not recognized" << endl;
			}

		}
	if(quit) break;
	}
}


void Controller::setFile(const char* file){
	this->file = file;
}

void Controller::init(int x, int y, char p){
	display->init(x, y, p);
	if(gd) gd->init(x, y, p);
}
void Controller::notify(Move m, int status){
	display->notify(m, status);
	if(gd) gd->notify(m, status);
}
