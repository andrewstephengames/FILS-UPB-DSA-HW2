#include "network.h"

template <typename TnodeInfo, typename TedgeInfo>
Graph<TnodeInfo, TedgeInfo>::Graph (int numNodes) {
    int i, j;

    N = numNodes;
    visited = new int[N];

    // allocate the adjacency matrix
    A = new char *[N];
    for (i = 0; i < N; i++)
        A[i] = new char[N];
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            A[i][j] = 0;

    // allocate the array with node information
    nodeInfo = new TnodeInfo[N];

    // allocate the matrix of edge information
    edgeInfo = new TedgeInfo *[N];
    for (i = 0; i < N; i++)
        edgeInfo[i] = new TedgeInfo[N];
}

template <typename TnodeInfo, typename TedgeInfo>
void Graph<TnodeInfo, TedgeInfo>::setNodeInfo(int i, TnodeInfo info) {
    nodeInfo[i] = info;
}

template <typename TnodeInfo, typename TedgeInfo>
TnodeInfo Graph<TnodeInfo, TedgeInfo>::getNodeInfo(int i) {
    return nodeInfo[i];
}

template <typename TnodeInfo, typename TedgeInfo>
void Graph<TnodeInfo, TedgeInfo>::addEdge(int i, int j) {
    A[i][j] = A[j][i] = 1;
}

template <typename TnodeInfo, typename TedgeInfo>
void Graph<TnodeInfo, TedgeInfo>::removeEdge(int i, int j) {
    A[i][j] = A[j][i] = 0;
}

template <typename TnodeInfo, typename TedgeInfo>
void Graph<TnodeInfo, TedgeInfo>::setEdgeInfo(int i, int j, TedgeInfo info) {
    edgeInfo[i][j] = edgeInfo[j][i] = info;
}

template <typename TnodeInfo, typename TedgeInfo>
TedgeInfo Graph<TnodeInfo, TedgeInfo>::getEdgeInfo(int i, int j) {
    return edgeInfo[i][j];
}

template <typename TnodeInfo, typename TedgeInfo>
Graph<TnodeInfo, TedgeInfo>::~Graph() {
    int i;
    for (i = 0; i < N; i++) {
        delete A[i];
        delete edgeInfo[i];
    }
    delete A;
    delete edgeInfo;
    delete nodeInfo;
}

template <typename Tnodeinfo, typename Tedgeinfo>
void Graph<Tnodeinfo, Tedgeinfo>::dfs(int x) {
    int y;
    cout << x << ' ';
    visited[x] = 1;

    for (y = 0; y < N; y++)
        if (A[x][y] && !visited[y])
            dfs(y);
}

template <typename Tnodeinfo, typename Tedgeinfo>
void Graph<Tnodeinfo, Tedgeinfo>::unvisit() {
    for (int i = 0; i < N; i++)
        visited[i] = 0;
}

template <typename Tnodeinfo, typename Tedgeinfo>
void Graph<Tnodeinfo, Tedgeinfo>::bfs(int S) {
    queue<int> Q;
    int x, y;

    Q.push(S);
    visited[S] = 1;

    while (!Q.empty()) {
        x = Q.front();
        Q.pop();
        cout << x << ' ';
        for (y = 0; y < N; y++)
            if (A[x][y] && !visited[y]) {
                visited[y] = 1;
                Q.push(y);
            }
    }
}

template <typename Tnodeinfo, typename Tedgeinfo>
bool Graph<Tnodeinfo, Tedgeinfo>::isCompleteGraph() {
    // return true if it s a complete graph
    for (int i = 0; i < N; i++)
    {

        for (int j = i; j < N; j++)
        {

            if (A[i][j] == 0 && i != j)
            {
                return false; // a node is not connected to another one, so the graph is not complete
            }
        }
    }

    return true; // all nodes are connected directly, so we havea complete graph
}

template <typename Tnodeinfo, typename Tedgeinfo>
bool Graph<Tnodeinfo, Tedgeinfo>::isNodeIsolated() {
    // return true if we have any nodes isolated
    for (int i = 0; i < N; i++)
    {

        bool verify = true; // to verify if there are isolated nodes

        for (int j = 0; j < N; j++)
        {

            if (A[i][j] == 1)
            {
                verify = false; // node is not isolated
            }
        }

        if (verify == true)
        {
            return true; // there is an isolated node
        }
    }
    return false; // there is no isolated node

    // here we need to use all the matrix, as we can't be certain we don t have an isolated node
    // Example:
    /*

    0 1 1 1
    1 0 0 0
    1 0 0 0
    1 0 0 0

    if we were to look only above the main diagonal, nodes 2, 3 and 4 would be considered isolated, which they are not

    */
}

template <typename Tnodeinfo, typename Tedgeinfo>
bool Graph<Tnodeinfo, Tedgeinfo>::isCircuitHamiltonian() {
    // return true if it is(so all the nodes can be accesed in the network)

    int countOnes = 0; // will count how many values of 1 we have in the matrix, as we need N/2 + 1 in order to have an hamiltonian graph

    for (int i = 0; i < N; i++)
    {

        for (int j = i; j < N; j++)
        {

            if (A[i][j] == 1)
            {
                countOnes++;
            }
        }
    }

    if (countOnes >= N - 1)
        return true; // our graph is eulerian

    return false; // no hamiltonian circuit found, so it's impossible to have every device connected
}

template <typename Tnodeinfo, typename Tedgeinfo>
bool Graph<Tnodeinfo, Tedgeinfo>::connected() {
    // returns true if all devices are connected

    if (isCompleteGraph() == true)
        return true;
    // graph is complete, all devices are connected

    if (isNodeIsolated() == true)
        return false;
    // at least one node is islated, so at least one device is not connected

    if (isCircuitHamiltonian() == true)
        return true;
    // graph has a hamiltonian cycle, so all nodes are connected in the network

    return false;
    // means that the devices are not connected
}

template class Graph<int, int>; // fix linker not linking
