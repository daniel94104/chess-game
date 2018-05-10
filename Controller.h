#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "Game.h"
#include "View.h"
#include <iostream>

class Controller : public GameNotification{
	View *display;
	View *gd;
	Game *game;
	Player *white;
	Player *black;
	int blackPts;
	int whitePts;
	bool turn; //Alternates to keep track of who's turn it is
	const char *file;
	Piece *createPiece(int x, int y, char p);
	Player *createPlayer(std::string type);
	void readBoard(std::istream &in);
public:
	Controller(bool graphics);
	~Controller();

	//main loop - read in commands and excute the game
	void play();

	//notifies the display of a change
	void notify(Move m, int status);

	void init(int x, int y, char p);

	void setFile(const char* file);

	void setup();
};
#endif
