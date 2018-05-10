#ifndef __VIEW_H__
#define __VIEW_H__
#include <iostream>
#include <sstream>

#include "Piece.h"
class View {
  public:
    View();   

   // virtual void printArt() = 0;
 	virtual void notify(Move &m, int status) = 0;
	virtual void init(int x, int y, char c) = 0;
 	virtual void print(std::ostream &out) = 0;
 	virtual ~View() = 0;
};

#endif
