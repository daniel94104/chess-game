#ifndef __GRAPHICDISPLAY_H__
#define __GRAPHICDISPLAY_H__
#include "View.h"
#include "window.h"
#include <iostream>

class GraphicDisplay :public View{
    Xwindow *w;
    int size;
    char board[8][8];
    int map[8][8];
    public:
        GraphicDisplay();
        void notify(Move &m, int status);
        void print(std::ostream &out);
        void update(Move &m);
        void init(int x, int y, char c);
        ~GraphicDisplay();
};
#endif
