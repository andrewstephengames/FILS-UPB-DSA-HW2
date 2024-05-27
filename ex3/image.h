#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
using namespace std;

#define SIZE 6
#define T 10

typedef unsigned char u8;

class Graph {
public:
    Graph(int n);
    ~Graph();
    void addEdge(u8 x, u8 y, u8 w);
    void print();
private:
    int n;
    u8 **a;
};
#endif // IMAGE_H
