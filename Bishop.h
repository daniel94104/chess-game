#ifndef __BISHOP_H__
#define __BISHOP_H__

#include "Piece.h"
#include <vector>

class Bishop : public Piece {
public:
	Bishop();
	std::vector<Move> getMoves();

};

#endif
