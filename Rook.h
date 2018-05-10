#ifndef __ROOK_H__
#define __ROOK_H__

#include "Piece.h"
#include <vector>

class Rook : public Piece {

public:
	Rook();
	std::vector<Move> getMoves();

};

#endif
