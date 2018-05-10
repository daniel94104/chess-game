#ifndef __KING_H__
#define __KING_H__

#include "Piece.h"
#include <vector>

class King : public Piece {
public:
	King();
	std::vector<Move> getMoves();

};

#endif
