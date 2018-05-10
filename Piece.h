#ifndef __PIECE_H__
#define __PIECE_H__

#include <vector>

class Game;
class Player;

struct Move{
	int x1, y1;
	int x2, y2;
	bool operator==(Move m2);
    bool operator!=(Move m2);
};

class Piece{
    protected:
        int xDirection;
        int yDirection;
	    int x, y;
	    char type;
	    Game *game;
	    Player *owner;
        bool first;
        int times;
public:
	Piece();
	virtual ~Piece() = 0;
    int getXDirection();
    int getYDirection();
    
	void setXDirection(int x);
	void setYDirection(int y);

	Player *getOwner();
	void setOwner(Player *p);
    int getTimes();
    void setTimes(int);
    bool getFirst();
    void setFirst(bool);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);

	void setGame(Game *g); 

	char getType();
	void setType(char c);

	void notify(Move m);
    bool sameCase(char a, char b);
	virtual std::vector<Move> getMoves(); 
};

#endif
