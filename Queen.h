#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "Piece.h"
#include <vector>

class Queen : public Piece {

public:
	Queen();
	std::vector<Move> getMoves();

};

#endif
