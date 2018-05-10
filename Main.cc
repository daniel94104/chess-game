#include "Controller.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
	bool g = true;
	string s = "std_board.txt";
	const char *file = s.c_str();
	if(argc > 1){
		file = argv[1];
	}

	Controller c(g);
	ifstream ifs(file);
	if(ifs.good()){
		c.setFile(file);
	}else{
		cout << "File doesn't exist or failed to open" << endl;
		cout << "Using standard file" << endl;
		c.setFile(s.c_str());
	}
	c.play();

	
	return 0;
}

