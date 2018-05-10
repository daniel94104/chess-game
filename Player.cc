#include "Player.h"
#include <string>

using namespace std;

Player::Player(){
	input = NULL;
	numPieces = 0;
	king = NULL;
	g = NULL;
}
Player::~Player(){
	for(std::vector<Piece *>::iterator i = pieces.begin(); i != pieces.end(); i++){
		delete *i;
	}
}

void Player::setGame(Game *g){
	this->g = g;
}
void Player::setSource(std::istream *in){
	input = in;
}

void Player::clear(){
	numPieces = 0;
}

vector<Piece *> Player::getPieces(){
	return pieces;
}
void Player::addPiece(Piece *p){
	pieces.push_back(p);
	numPieces++;
	if((p->getType() == 'K' || p->getType() == 'k') && king == NULL) king = p;
}	

void Player::removePiece(Piece *p){	
	for(std::vector<Piece *>::iterator i = pieces.begin(); i != pieces.end(); i++){
		if(((*i)->getX() == p->getX()) && ((*i)->getY() == p->getY())){
			//delete *i;
			pieces.erase(i);
			break;
		}
	}
}

void Player::setKing(Piece *p){
	king = p;
}
Piece *Player::getKing(){
	return king;
}
Player *Player::getEnemy(){
	return enemy;
}
void Player::setEnemy(Player *p){
    enemy = p;
}

Move str_to_move(const string &in, const string &in2){
	Move m;
	m.x1 = in[0] - 'a';
	m.y1 = 7 - (in[1] - '1');
	m.x2 = (in2[0] - 'a');
	m.y2 = 7 - (in2[1] - '1');
	return m;
}


Move Player::getMove(){
	std::string cmd;
	std::string orig, moved;
	while(*input >> cmd){
		if(cmd == "move"){ //They're making a move
			Move m;
			*input >> orig;
			*input >> moved;
			m = str_to_move(orig, moved);
			//turn ? m = white->getMove() : black->getMove();	
			if(g->validMove(m) && g->pieceAt(m.x1, m.y1) &&
				king->sameCase(g->pieceAt(m.x1, m.y1)->getType(), king->getType()) &&
				g->move(m)){
				cout << static_cast<char>(m.x1 + 'a') 
			 		 << static_cast<char>(7 - m.y1 + '1')
			 		 << " to " <<  static_cast<char>(m.x2 + 'a')
			 		 <<  static_cast<char>(7 - m.y2 + '1') << endl; 
			 		 break;
			}else{
				cout << "invalid move" << endl;
			}
		}else if(cmd == "resign"){
					g->resign(this);
					break;
		}else if(cmd == "list"){
			*input >> cmd;
			int x = cmd[0] - 'a';
			int y = 7 - (cmd[1] - '1');
			if(g->pieceAt(x, y)){
				vector<Move> v = g->pieceAt(x,y)->getMoves();
		 		for(std::vector<Move>::iterator i = v.begin(); i != v.end(); i++){
		 			int x1 = i->x1 + 'a';
		 			int x2 = i->x2 + 'a';
		 			int y1 = 7 - i->y1 + '1';
		 			int y2 = 7 - i->y2 + '1';
		 			cout << static_cast<char>(x1) << static_cast<char>(y1)
		 				 << " to " <<  static_cast<char>(x2)
						 <<  static_cast<char>(y2) << endl; 
		 		}
			}else{
				cout << "No piece at " << cmd << endl;
			}
		}else if(cmd == "attack?"){
			*input >> orig;
			int x = orig[0] - 'a';
			int y = 7 - (orig[1] - '1');
			if(g->pieceAt(x, y) && g->canAttack(x, y, g->pieceAt(x,y)->getOwner()->getKing()->getType())){
				cout << orig << " can be attacked" << endl;
			}else if(g->canAttack(x, y, king->getType())){
				cout << orig << " Can be attacked" << endl;
			}else{
				cout << orig << " cannot be attacked" << endl;
			}


		}else{
			cout << "Command not recognized" << endl;
		}
	}

	Move m1;
	return m1;
}

