#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "Piece.h"
#include "View.h"
#include <iostream>

class TextDisplay : public View{
	char theDisplay[8][8];
public:
	TextDisplay();
	~TextDisplay();
	void printArt();
	void notify(Move &m, int status);
	void init(int x, int y, char p);
 	void print(std::ostream &out);


};

#endif
