#include "GraphicDisplay.h"
#include <iostream>

GraphicDisplay::GraphicDisplay(): w(NULL){
	size = 50;
	w = new Xwindow(9 * size - 20,9 * size - 15 );
    // print the board with pieces.
    int c = 0;
    std::string a;

	for(int i = 0; i <8; i++){ //row
        std::string cheese ="";
        cheese += static_cast<char>( '8' - i);
		w->drawString(10, 50*(i+1) - 20, cheese, Xwindow::Black); 
        for(int j = 0; j < 8; j++){ // col
		    a = "";
            a += board[i][j];
            w->fillRectangle(size * (j+1) - 20 , size * i, size, size, c);
            map[i][j] = c;
          //  w->drawBigString((size * j) +5, size * i, "D",Xwindow::Black);
			(!c) ? c = 4 : c = 0;
		}
		(!c) ? c = 4 : c = 0;
	}
    for(int i = 1; i < 9; i++){
        std::string dog = "";
        dog += static_cast<char>('a' + i - 1);
        w->drawString(i * 50, 50 * 9 - 25, dog, Xwindow::Black);
    }
	//size = 500/n + (500 % n);
}

void GraphicDisplay::notify(Move &m, int status){
    board[m.y2][m.x2] = board[m.y1][m.x1];
    board[m.y1][m.x1] = 0;
	update(m);
}

void GraphicDisplay::update(Move &m){
    std::string a;
    char c = board[m.y2][m.x2];

    int yFactor = 0;
    (board[m.y2][m.x2] == '_') ? a = "" : a += c;
    w->fillRectangle((50 * (1  + m.x1))-20, 50 * m.y1, 50,50,map[m.y1][m.x1]);
    w->fillRectangle(50 * (1 +m.x2) - 20, 50 * m.y2, 50,50,map[m.y2][m.x2]);
    if(c == 'p' || c == 'q'){
       yFactor = 12;
    }
    else if(c < 'a'){
        yFactor = 5;
    }
    //w->drawBigString((50 * (1 +m.x1)) + 8 - 25, 50 * (m.y1 + 1 ) - yFactor , "", Xwindow::Black);
    w->drawBigString((50 * (1+ m.x2)) + 8 - 25, 50 * (m.y2 + 1) - yFactor, a, Xwindow::Black);
}

void GraphicDisplay::print(std::ostream &out){
}

void GraphicDisplay::init(int x, int y, char c){
   // std::cout << "Adding " << c << " to " << x << "," << y << std::endl;
    board[y][x] = c;
    Move m = {x,y,x,y};
    update(m);
}




GraphicDisplay::~GraphicDisplay(){
	delete w;
//	for(int i = 0; i < 8; i++){
//		delete [] board[i];
//	}
//	delete [] board;
}
