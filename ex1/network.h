#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <queue>
using namespace std;

template <typename TnodeInfo, typename TedgeInfo>
class Graph {
public:
    int N, *visited;
    char **A;
    TnodeInfo *nodeInfo;
    TedgeInfo **edgeInfo;
    Graph(int numNodes);
    void setNodeInfo(int i, TnodeInfo info);
    TnodeInfo getNodeInfo(int i);
    void addEdge(int i, int j);
    void removeEdge(int i, int j);
    void setEdgeInfo(int i, int j, TedgeInfo info);
    TedgeInfo getEdgeInfo(int i, int j);
    ~Graph();
    void dfs(int x);
    void unvisit();
    void bfs(int S);
    bool isCompleteGraph();
    bool isNodeIsolated();
    bool isCircuitHamiltonian();
    bool connected();
};

#endif // NETWORK_H
