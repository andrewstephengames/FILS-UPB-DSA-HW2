#include "image.h"

Graph::Graph(int n) {
    this->n = n;
    a = new u8*[SIZE+1];
    for (int i = 0; i < SIZE+1; i++)
        a[i] = new u8[SIZE+1];
}

Graph::~Graph() {
    for (int i = 0; i < SIZE; i++)
        delete[] a[i];
    delete[] a;
}

void Graph::addEdge (u8 x, u8 y, u8 w) {
    a[x][y] = w;
}

void Graph::print() {
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++)
            cout << (int)a[x][y] << " ";
        cout << endl;
    }
}
