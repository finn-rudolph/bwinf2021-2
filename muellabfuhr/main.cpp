#include <bits/stdc++.h>
#include "fhk_algorithm.hpp"
using namespace std;

adj_map to_adjacency_map(int n, int m);

void print_tours(vector<vector<int>> &tours, adj_map &graph);

int main() {
    int n, m; 
    cin >> n >> m;

    adj_map graph = to_adjacency_map(n, m);
    vector<vector<int>> tours = fhk(graph);
    print_tours(tours, graph);
}

adj_map to_adjacency_map(int n, int m) {
    adj_map adjMap(n);

    for (int i = 0; i < m; i++) {
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        adjMap[v1][v2] = adjMap[v2][v1] = w;
    }

    return adjMap;
}

void print_tours(vector<vector<int>> &tours, adj_map &graph) {
    int largest = 0;
    for (int i = 0; i < tours.size(); i++) {
        cout << "Tag " << (i + 1) << ": ";
        int cost = 0;

        for (int j = 0; j < tours[i].size(); j++) {
            cout << tours[i][j] << " ";
            if (j != 0) cost += graph[tours[i][j]][tours[i][j - 1]];
        }

        cout << "| Gesamtlänge: " << cost << "\n";
        if (cost > largest) largest = cost;
    }
    cout << "\nLänge der längsten Tagestour: " << largest << endl;
}