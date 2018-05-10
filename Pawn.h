#ifndef __PAWN_H__
#define __PAWN_H__

#include "Piece.h"
#include <vector>

class Pawn : public Piece {
protected:
	bool justEP;
    bool enPassant;
public:
	Pawn();
    bool getEp();
    void setEp(bool);
	std::vector<Move> getMoves();

};

#endif
