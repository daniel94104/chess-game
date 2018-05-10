#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Piece.h"
#include "Game.h"
#include <vector>
#include <iostream>

class Player{
protected:
	std::vector<Piece *> pieces;
	int numPieces;
	std::istream *input;
	Piece *king;
	Game *g;
	Player *enemy;
public:
	Player();
	virtual ~Player();

	std::vector<Piece *> getPieces();

	void setSource(std::istream *in);

	void setGame(Game *g);

	void setKing(Piece *p);
	//deletes the current pieces held by the player
	void clear();

	void setEnemy(Player *e);

	Player *getEnemy();
	//register a piece with the player
	void addPiece(Piece *p);

	//remove a piece
	void removePiece(Piece *p);

	//reads in a move from input
	virtual Move getMove();

	Piece *getKing();
};

#endif
