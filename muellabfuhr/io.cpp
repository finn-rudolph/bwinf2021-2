#include <iostream>
#include "io.hpp"
using namespace std;

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

void print_graph(adj_map &graph) {
    for (int a = 0; a < graph.size(); a++) {
        cout << a << ": ";
        for (const auto &[b, w]: graph[a]) {
            cout << b << " -> " << w<< ";   ";
        }
    }
    cout << "\n" << endl;
}

void print_map_2d(map_2d &map) {
    for (const auto &[a, m]: map) {
        cout << a << ": ";
        for (const auto &[b, w]: m) {
            cout << b << " -> " << w << ";   ";
        }
        cout << "\n";
    }
    cout << "\n" << endl;
}

void print_vector(vector<int> &vector) {
    for (const auto &e: vector) {
        cout << e << " ";
    }
    cout << "\n" << endl;
}