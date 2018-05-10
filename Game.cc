#include "Game.h"
#include <vector>
#include "Pawn.h"


using namespace std;

GameNotification::GameNotification(){

}
GameNotification::~GameNotification(){

}


Game::Game(Player *white, Player *black){
	board = new Piece**[8];
	for(int i = 0; i < 8; i++){
		board[i] = new Piece*[8];
	}
	this->white = white;
	this->black = black;
	notif = NULL;
	state = 1;
}

Game::~Game(){
	for(int i = 0; i < 8; i++){
		delete [] board[i];
	}
	delete [] board;

}

bool Game::validMove(Move m){
	return m.x1 < 8 && m.x1 >= 0 && m.y1 < 8 && m.y1 >= 0
	&& m.x2 < 8 && m.x2 >= 0 && m.y2 < 8 && m.y2 >= 0;
}
Piece *Game::pieceAt(int x, int y){
	if(x > 7 || x < 0 || y > 7 || y < 0) cerr << "Out of bounds on pieceAt" << endl;
	if(board[y][x])	return board[y][x];
	return NULL;
}

void Game::resign(Player *p){
    if(p->getKing()->getType() == 'K'){
    	delete white;
    	white = NULL;
    }else{
		black = NULL;
	}
	state = 0;
}

Player *Game::getWinner(){
	if(!white) return black;
	if(!black) return white;
	return 0;
}

void Game::setNotification(GameNotification *n){
	notif = n;
}
void Game::killPiece(int x, int y){
	board[y][x]->getOwner()->removePiece(board[y][x]);
    delete board[y][x];
	board[y][x] = NULL;
	Move m = {x,y,x,y};
	notif-> notify(m, status());
}

//Checkmate checker; checks:
//1. Can king move out of the way?
//2. can the offender be killed?
//3. Can a piece move so that the king won't be killed?

bool Game::checkStatus(Piece *offender){
	if(state == 0) return 0; 
	if(!offender){
		Piece *whiteKing = white->getKing();
		Piece *blackKing = black->getKing();
		if((offender = canAttack(whiteKing->getX(), whiteKing->getY(), whiteKing->getType()))){
			state = 2;
		}
		if((offender = canAttack(blackKing->getX(), blackKing->getY(), blackKing->getType()))){
			state = 3;
		}
	}
	if(state > 1 && offender){
		//Kings moves:
		Player *checked = NULL;
		(state == 2) ? checked = white : checked = black;

		vector<Move> kingMoves = checked->getKing()->getMoves();
		for(vector<Move>::iterator i = kingMoves.begin(); i != kingMoves.end(); i++){
			if(canAttack((*i).x2, (*i).y2, checked->getKing()->getType())){
				return true; //If the king can get out of the way, we keep the state as is
			}
		}

		//Can the offender be killed?
		if(canAttack(offender->getX(), offender->getY(), offender->getType())){
			return true; //If we can kill the offender, then we keep the current state
		}
	}
	Player *p = white;
	do{
		bool stale = true;

	    //check stalemate;
	    Player *owner = p;
		if(state == 1){
			vector<Piece *> pieces = owner->getPieces();
			for(vector<Piece *>::iterator i = pieces.begin(); i != pieces.end(); i++){
				std::vector<Move> moves = (*i)->getMoves();
				for(std::vector<Move>::iterator j =  moves.begin(); j != moves.end(); j++){
					if(valid((*j), (*i))){
						stale = false;
						break;
					}
				}
				if(!stale) break;
			}
		}
		if(stale) state = 4;
		(p->getKing()->getType() == 'K') ? p = black : p = white;
	}while(p->getKing()->getType() != 'K');
	
	return true;
}



int abs(int x){
	int y = (x>0) ? x : -x;
	return y;
}


bool Game::move(Move m){
	if(valid(m, board[m.y1][m.x1])){
		if((m.x1 != m.x2) && (board[m.y1][m.x1]->getType() == 'p' ||
			board[m.y1][m.x1]->getType() == 'P')){
			if(board[m.y2][m.x2] ==  NULL){
				killPiece(m.x2, m.y2 - board[m.y1][m.x1]->getYDirection());
				board[m.y2][m.x2] = board[m.y1][m.x1];
				board[m.y1][m.x1] = NULL; 
				notify(m);
				return true;
			}
        }//end enPassant.

        //castling move.
        if((board[m.y1][m.x1]->getType() == 'k' || board[m.y1][m.x1]->getType() == 'K')){
            //shorter castling
        	if(m.x2- m.x1 == 2){
        		board[m.y2][m.x2] = board[m.y1][m.x1];
        		board[m.y1][m.x1] = NULL;
        		board[m.y1][5] = board[m.y1][7];
        		board[m.y1][7] = NULL;
        		Move rook = {7,m.y1,5,m.y1};
        		board[m.y2][m.x2]->setFirst(false);
        		notify(rook);
        		notify(m);
        		return true;
        	}
            //longer castling.
        	else if(m.x2 - m.x1 == -2){
        		board[m.y2][m.x2] = board[m.y1][m.x1];
        		board[m.y1][m.x1] = NULL;
        		board[m.y1][3] = board[m.y1][0];
        		board[m.y1][0] = NULL;
        		Move rook = {0,m.y1,3,m.y1};
        		board[m.y2][m.x2]->setFirst(false);
        		notify(rook);
        		notify(m);
        		return true;
        	}
        }//end castling.

        Piece *moved = board[m.y1][m.x1];
        if(board[m.y2][m.x2]){
        	board[m.y2][m.x2]->getOwner()->removePiece(board[m.y2][m.x2]);
        	board[m.y2][m.x2] = board[m.y1][m.x1];
        	board[m.y1][m.x1] = NULL; 
        }else{

        	if((moved->getType() == 'P' || moved->getType() == 'p') && abs(m.y2 - m.y1) == 2){
        		dynamic_cast<Pawn *>(moved)->setEp(true);

        	}
        	board[m.y2][m.x2] = board[m.y1][m.x1];
        	board[m.y1][m.x1] = NULL; 
        }
        
        
        for(int i = 0; i < 8; i++){
        	for(int j = 0; j < 8; j++){
        		if(pieceAt(i,j) && (pieceAt(i,j)->getType() == 'P' || pieceAt(i,j)->getType() == 'p')){
        			dynamic_cast<Pawn*>(pieceAt(i,j))->setEp(false);
        		}
        	}
        }

        notify(m);


	//Check if the move put the enemy king in check
		Piece *p = board[m.y2][m.x2];
		Piece * enemyKing = p->getOwner()->getEnemy()->getKing();
		cout << enemyKing << endl;
		vector<Move> v = p->getMoves();
		Piece *offender = NULL;
		for(vector<Move>::iterator i = v.begin(); i != v.end(); i++){
			if((*i).x2 == enemyKing->getX()
				&& (*i).y2 ==  enemyKing->getY()){
				cout << "Check" << endl;
				offender = pieceAt((*i).x1, (*i).y1);
				(enemyKing->getType() == 'K') ? state = 2 : state = 3;
				break;
			}
			if(i+1 == v.end()) state = 1;
		}
		checkStatus(offender);
	    return true;
    }
    return false;
}

void Game::init(int x, int y, Piece *p){
	board[y][x] = p;
	char ret;
	p ? ret = p->getType() : ret = '_';
	notif->init(x, y, ret);
}

bool sameDest(Move *m1, Move *m2){
	return (m1->x2 == m2->x2) && (m2->y2 == m1->y2);
}

Piece *Game::canAttack(int x, int y, char king){
	Player *enemy;
	bool isWhite = king < 'a';
	if(isWhite){
		enemy = black;
	}else{
		enemy = white;
	}
	vector<Piece *> pieces = enemy->getPieces();

    //make temp piece that we check if it can be attacked
	Piece *n = new Pawn;
	n->setX(x);
	n->setY(y);
	n->setType(isWhite ? 'P' : 'p');
	n->setGame(this);

	int yDir = 1;
	isWhite ? yDir *= -1 : yDir;
	n->setYDirection(yDir);
	n->setXDirection(1);


	Piece *oldPiece;
	board[y][x] ? oldPiece = board[y][x] : oldPiece = NULL;
	board[y][x] = n;
	if(oldPiece) oldPiece->getOwner()->removePiece(oldPiece);
	Move temp = {0,0,x,y};
	Piece *offender = NULL;
	for(std::vector<Piece *>::iterator i = pieces.begin(); i != pieces.end(); i++){

		vector<Move> m = (*i)->getMoves();
		for(std::vector<Move>::iterator j = m.begin(); j != m.end(); j++){

			if(sameDest(&(*j), &temp)){
				offender = (*i);
				break;
			}
		}
		if(offender) break;
	}

	delete n;
	board[y][x] = oldPiece;
	if(oldPiece) oldPiece->getOwner()->addPiece(oldPiece);
	return offender;
}

//checks if each player has only 1 king and 
// that there are no pawns on the last row
bool Game::valid(){
	if(!white->getKing() || !black->getKing()) return false;

	vector<Piece *> wPieces = white->getPieces();
	for(std::vector<Piece *>::iterator i = wPieces.begin(); i != wPieces.end(); i++){
		if((*i)->getType() == 'P' || (*i)->getType() == 'p'){
			if((*i)->getY() == 7 || (*i)->getY() == 0) return false;
		}
	}

	vector<Piece *> bPieces = black->getPieces();
	for(std::vector<Piece *>::iterator i = bPieces.begin(); i != bPieces.end(); i++){
		if((*i)->getType() == 'P' || (*i)->getType() == 'p'){
			if((*i)->getY() == 7 || (*i)->getY() == 0) return false;
		}
	}

	if(canAttack(white->getKing()->getX(), white->getKing()->getY(), white->getKing()->getType())){
		return false;
	}

	if(canAttack(black->getKing()->getX(), black->getKing()->getY(), black->getKing()->getType())){
		return false;
	}


	return true;
}


//Checks to see if a move made is valid:
/* so far;
 * Doesn't put king in Check
 * Exists in p's getMoves()
 * 
 */
 bool Game::valid(Move m, Piece *p){
	//move is invalid by default.
 	bool valid = false;



    //in particular, if they do casting, then it's valid
    //check for castling.
    //long castling.

 	if((board[m.y1][m.x1]->getType() == 'K' || board[m.y1][m.x1]->getType() == 'k') 
 		&& (board[m.y1][m.x1]->getTimes() == 1)
 		&& (abs(m.x2 - m.x1) == 2)){
        //valid = true;
 		if(m.x2 < 4){
 			for(int x = 1; x < 4; x++){
 				if(canAttack(x,m.y1,board[m.y1][m.x1]->getType())){
 					valid = false;
 					return valid;
 				}
 			}
 		}else{
 			for(int x = 5; x< 7;x++){
 				if(canAttack(x,m.y1, board[m.y1][m.x1]->getType())){
 					valid = false;
 					return valid;
                    //break;
 				}
 			}
        }//shorter castling.
    }
    //end for checking castling.

	 //the move could be valid if it's in the piece's Moves
    std::vector<Move> moves = p->getMoves();
    for(std::vector<Move>::iterator i = moves.begin(); i != moves.end(); i++){
        //cout << (*i).x1 << " " << (*i).y1 << " to " 
        //     << (*i).x2 << " " << (*i).y2 << endl;
    	if(*i == m){
    		valid = true;
    		break;
    	}
    }
    if(!valid) return false;

    //make the move temporarily, to see if doing so puts the king under attack
    // since a move that puts your king in check is invalid
    Piece *tmp = board[m.y2][m.x2];
    if(tmp) tmp->getOwner()->removePiece(tmp);
    board[m.y2][m.x2] = board[m.y1][m.x1];
    board[m.y1][m.x1] = NULL;

    board[m.y2][m.x2]->setX(m.x2);
    board[m.y2][m.x2]->setY(m.y2);


    Player *owner = p->getOwner();

    if(canAttack(owner->getKing()->getX(), 
    	owner->getKing()->getY(), 
    	owner->getKing()->getType())){
    	valid = false;
	}

	board[m.y1][m.x1] = board[m.y2][m.x2];
	board[m.y2][m.x2]= tmp;
	if(tmp) tmp->getOwner()->addPiece(tmp);
	board[m.y1][m.x1]->setX(m.x1);
	board[m.y1][m.x1]->setY(m.y1);
	if(tmp) tmp->setTimes(tmp->getTimes() - 2);

    return valid;
}

void Game::notify(Move m){
	board[m.y2][m.x2]->notify(m);
	notif->notify(m, status());
}

void Game::setStatus(Player *p){
	Piece *king = p->getKing();
	int kx = king->getX(), ky = king->getY();

    if(canAttack(kx, ky, king->getType())){ //King is in check
    	state = 2;

    	std::vector<Move> moves = king->getMoves();
    	for(std::vector<Move>::iterator i = moves.begin(); i != moves.end(); i++){
    		if(!canAttack((*i).x2, (*i).y2, king->getType())) break;
    		if(i+1 == moves.end()) state = 0;
    	}
    }else{
    	state = 1;
    }
}
int Game::status(){
	checkStatus(NULL);
	return state;
}


bool Game::checkResult(Move m, int x, int y){

	bool attack = false;
    //temporary perform the move m with the piece located at the (x1,y1);
	Piece *tmp = board[m.y2][m.x2];
	if(tmp) tmp->getOwner()->removePiece(tmp);
	board[m.y2][m.x2] = board[m.y1][m.x1];
	board[m.y1][m.x1] = NULL;
	board[m.y2][m.x2]->setX(m.x2);
	board[m.y2][m.x2]->setY(m.y2);
	std::vector<Move> moves = board[m.y2][m.x2]->getMoves();
	for(std::vector<Move>::iterator i =moves.begin();i != moves.end(); i++){
		if((*i).x2 == x && (*i).y2 == y){
			attack = true;
			break;
		}
    }//end for loop.
    board[m.y1][m.x1] = board[m.y2][m.x2];
    board[m.y2][m.x2]= tmp;
    if(tmp) tmp->getOwner()->addPiece(tmp);
    board[m.y1][m.x1]->setX(m.x1);
    board[m.y1][m.x1]->setY(m.y1);
    return attack;
}

