#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "Piece.h"
#include <vector>

class Knight : public Piece {

public:
	Knight();
    //return a vector of valid moves.
	std::vector<Move> getMoves();

};

#endif
