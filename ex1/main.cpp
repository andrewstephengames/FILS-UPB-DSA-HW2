#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

int N; // number of devices(has to be global to be seen by the functions)

template <typename TnodeInfo, typename TedgeInfo>
class Graph
{
public:
    int N;
    char **A;
    TnodeInfo *nodeInfo;
    TedgeInfo **edgeInfo;

    Graph(int numNodes)
    {
        int i, j;

        N = numNodes;

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

    void setNodeInfo(int i, TnodeInfo info)
    {
        nodeInfo[i] = info;
    }

    TnodeInfo getNodeInfo(int i)
    {
        return nodeInfo[i];
    }

    void addEdge(int i, int j)
    {
        A[i][j] = A[j][i] = 1;
    }
    void removeEdge(int i, int j)
    {
        A[i][j] = A[j][i] = 0;
    }

    void setEdgeInfo(int i, int j, TedgeInfo info)
    {
        edgeInfo[i][j] = edgeInfo[j][i] = info;
    }

    TedgeInfo getEdgeInfo(int i, int j)
    {
        return edgeInfo[i][j];
    }

    ~Graph()
    {
        int i;
        for (i = 0; i < N; i++)
        {
            delete A[i];
            delete edgeInfo[i];
        }
        delete A;
        delete edgeInfo;
        delete nodeInfo;
    }
};
Graph<int, int> network(100);

char *visited;

void dfs(int x)
{
    int y;
    cout << x << ' ';
    visited[x] = 1;

    for (y = 0; y < network.N; y++)
        if (network.A[x][y] && !visited[y])
            dfs(y);
}

void unvisit()
{
    for (int i = 0; i < network.N; i++)
    {
        visited[i] = 0;
    }
}

void bfs(int S)
{
    std::queue<int> Q;
    int x, y;

    Q.push(S);
    visited[S] = 1;

    while (!Q.empty())
    {
        x = Q.front();
        Q.pop();
        cout << x << ' ';
        for (y = 0; y < network.N; y++)
            if (network.A[x][y] && !visited[y])
            {
                visited[y] = 1;
                Q.push(y);
            }
    }
}

bool isCompleteGraph()
{
    // return true if it s a complete graph
    for (int i = 0; i < N; i++)
    {

        for (int j = i; j < N; j++)
        {

            if (network.A[i][j] == 0 && i != j)
            {
                return false; // a node is not connected to another one, so the graph is not complete
            }
        }
    }

    return true; // all nodes are connected directly, so we havea complete graph
}

bool isNodeIsolated()
{
    // return true if we have any nodes isolated
    for (int i = 0; i < N; i++)
    {

        bool verify = true; // to verify if there are isolated nodes

        for (int j = 0; j < N; j++)
        {

            if (network.A[i][j] == 1)
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

bool isCircuitHamiltonian()
{
    // return true if it is(so all the nodes can be accesed in the network)

    int countOnes = 0; // will count how many values of 1 we have in the matrix, as we need N/2 + 1 in order to have an hamiltonian graph

    for (int i = 0; i < N; i++)
    {

        for (int j = i; j < N; j++)
        {

            if (network.A[i][j] == 1)
            {
                countOnes++;
            }
        }
    }

    if (countOnes >= N - 1)
        return true; // our graph is eulerian

    return false; // no hamiltonian circuit found, so it's impossible to have every device connected
}

bool connected()
{
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

int main()
{
    int u, v;            // the connection between devices
    int countInputs = 1; // count the number of inputs for error handling
    int maxInput;
    bool isNetworkConnected;

    cout << "Number of devices: ";
    cin >> N;

    maxInput = N * (N - 1) / 2; // maximum value of imputs(complete graph)

    fstream fin("inputList.txt");

    while (fin >> u >> v)
    {

        // using a file to read the list of inputs for easier error handling

        if (u == v)
        {
            // node incident to itself
            cerr << "Error: u and v are the same, the node is incident to itself" << endl;
            exit(EXIT_FAILURE);
        }
        else if (u < 1 || v < 1 || u > N || v > N)
        {
            // unexisting node in graph
            cerr << "Error: u or v is can't be a correct device" << endl;
            exit(EXIT_FAILURE);
        }
        else if (countInputs > maxInput)
        {
            // too many vertices in the list
            cerr << "Error: too many imputs, not enough space in graph" << endl;
            exit(EXIT_FAILURE);
        }
        else if (network.A[u - 1][v - 1] == 1 || network.A[v - 1][u - 1] == 1)
        {
            // the user put the same input more times
            cerr << "Error: same input more than once" << endl;
            exit(EXIT_FAILURE);
        }

        network.addEdge(u - 1, v - 1);
        countInputs++;
    }

    /*for(int i = 0; i < N; i++){

           bool verify = true;//to verify if there are isolated nodes

           for(int j = 0; j < N; j++){

               cout << network.A[i][j] << ' ';
           }

           cout << endl;

       }
       cout << endl;*/

    isNetworkConnected = connected();

    if (isNetworkConnected == true)
        cout << "All devices in the network are connected!" << endl;
    else
        cout << "There is at least one device in the network that is not connected!" << endl;

    fin.close();
}
