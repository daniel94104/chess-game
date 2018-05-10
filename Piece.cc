#include "Piece.h"
#include "Game.h"
#include "Player.h"

bool Move::operator==(Move m2){
	return ((x1 == m2.x1) &&
			(x2 == m2.x2) &&
			(y1 == m2.y1) &&
			(y2 == m2.y2));
}


bool Move::operator!=(Move m2){
    return ((x1 != m2.x1) ||
            (x2 != m2.x2) ||
            (y1 != m2.y1) ||
            (y2 != m2.y2));
}


Piece::Piece(){
	x = 0;
	y = 0;
	type = 0;
    xDirection = 0;
    yDirection = 0;
    owner = NULL;
    first = true;
    times = 1;
}

bool Piece::getFirst(){
    return first;
}

std::vector<Move> Piece::getMoves(){
	std::vector<Move> v;

	return v;
}

Piece::~Piece(){}

void Piece::notify(Move m){
	x = m.x2;
	y = m.y2;
    first = false;
    times++;
}


int Piece::getX(){
	return x;
}

int Piece::getY(){
	return y;
}

void Piece::setType(char c){
	type = c;
}

void Piece::setX(int x){
	this->x = x;
}

void Piece::setY(int y){
	this->y = y;
}

void Piece::setGame(Game *g){
	game = g;
}

void Piece::setXDirection(int x){
	xDirection = x;
}
int Piece::getXDirection(){
	return xDirection;
}

void Piece::setYDirection(int y){
	yDirection = y;
}

int Piece::getYDirection(){
	return yDirection;
}

Player *Piece::getOwner(){
	return owner;
}

void Piece::setOwner(Player *p){
	owner = p;
}

char Piece::getType(){
	return type;
}

bool Piece::sameCase(char a, char b){
    return (a <= 'z' && a >= 'a' && b <= 'z' && b >= 'a' ) ||
        (a <= 'Z' && a >= 'A' && b <= 'Z' && b >= 'A');        
}

void Piece::setFirst(bool b){
    first = b;
}

int Piece::getTimes(){
    return times;
}

void Piece::setTimes(int t){
    times = t;
}
