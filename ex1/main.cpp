#include <iostream>
#include "network.h"
#include <fstream>
using namespace std;

int main()
{
    int N;
    int u, v;            // the connection between devices
    int countInputs = 1; // count the number of inputs for error handling
    int maxInput;
    bool isNetworkConnected;

    cout << "Number of devices: ";
    cin >> N;
    Graph<int, int> *network = new Graph<int, int> (N);

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
            cerr << "Error: u or v can't be a correct device" << endl;
            exit(EXIT_FAILURE);
        }
        else if (countInputs > maxInput)
        {
            // too many vertices in the list
            cerr << "Error: too many inputs, not enough space in graph" << endl;
            exit(EXIT_FAILURE);
        }
        else if (network->A[u - 1][v - 1] == 1 || network->A[v - 1][u - 1] == 1)
        {
            // the user put the same input more times
            cerr << "Error: same input more than once" << endl;
            exit(EXIT_FAILURE);
        }

        network->addEdge(u - 1, v - 1);
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

    isNetworkConnected = network->connected();

    if (isNetworkConnected == true)
        cout << "All devices in the network are connected!" << endl;
    else
        cout << "There is at least one device in the network that is not connected!" << endl;

    fin.close();
    delete network;
    return 0;
}
