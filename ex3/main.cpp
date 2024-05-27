#include <fstream>

using namespace std;

ifstream in ("input.txt");

#include "image.h"

int main () {
    int x;
    Graph *g = new Graph(SIZE);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            in >> x;
            if (x > T)
                x = 0;
            g->addEdge (i, j, x);
        }
    g->print();
    delete g;
    return 0;
}
