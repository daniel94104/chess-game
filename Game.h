#ifndef __GAME_H__
#define __GAME_H__

#include "Piece.h"
#include "Player.h"

class GameNotification{
	public:
		GameNotification();
		virtual void init(int x, int y, char p) = 0;
		virtual void notify(Move m, int status) = 0;
		virtual ~GameNotification() = 0;
};

class Game{
	Piece ***board;
	Player *white;
	Player *black;
	GameNotification *notif;


	//0 if checkmate
	//1 if normal
	//2 if check by black
	//3 if check by white
	//4 if stalemate
	int state; 	
	void setStatus(Player *p);
public:

	Game(Player *white, Player *black);
	~Game();

	//returns 0 if checkmate, 1 if normal, 2 if check, 3 if stalemate
	int status();

	bool validMove(Move m);

	//returns the piece at a given (x,y)
	Piece *pieceAt(int x, int y);

	//takes in a Move and performs it (Also checks if it's valid);
	bool move(Move m);

	Player *getWinner();

	//called my Controller to place a piece at square at (x, y)
	//removes the previous piece (and disassociates it from the Player
	//  that owned it)
	void init(int x, int y, Piece *p);

	//if the square can be attacked by the type opposite to king 
	// (ucase to lcase), then it returns true;
	Piece * canAttack(int x, int y, char king);

	//returns true if a board is valid:
	//(i.e Contains only 1 king for each player, 
	// No pawns at the end of the board, or
	// the kings aren't in check)
	bool valid();

	void killPiece(int x, int y);

	//valid override that checks to make sure m is in p->getMoves(); 
	bool valid(Move m, Piece *p);

	void setNotification(GameNotification *n);

	//notifies the piece of a move, as well as the controller. 
	void notify(Move m);

	void resign(Player *p);

	bool checkStatus(Piece *offender);

    //check if we can attack (x,y), when we perform such move.
    bool checkResult(Move m, int x, int y);

};

#endif
