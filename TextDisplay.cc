#include "TextDisplay.h"
#include <fstream>
#include <string>

using namespace std;

TextDisplay::TextDisplay(){
	
}
TextDisplay::~TextDisplay(){

}
void TextDisplay::notify(Move &m, int state){
	theDisplay[m.y2][m.x2] = theDisplay[m.y1][m.x1];
	theDisplay[m.y1][m.x1] = '_'; 
	if(state == 0) cout << "Checkmate!" << endl;
	if(state == 2) cout << "White is in Check" << endl;
	if(state == 3) cout << "Black is in Check" << endl;
	if(state == 4) cout << "Stalemate" << endl;
}
void TextDisplay::init(int x, int y, char p){
	theDisplay[y][x] = p;
}
void TextDisplay::print(std::ostream &out){
	for(int i = 0; i < 9; i++){
		(i < 8) ? out << 8-i << " " : out << "  ";
		for(int j = 0; j < 8; j++){
			(i < 8) ? out << theDisplay[i][j] : out << (char)(j+'a');
		}
		out << std::endl;
	}
}

void TextDisplay::printArt(){
	ifstream ifs("chess_art.txt");
	string s;
	while(getline(ifs, s)) cout << s;
}
