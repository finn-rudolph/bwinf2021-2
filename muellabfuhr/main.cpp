#include <bits/stdc++.h>
#include "fhk_algorithm.hpp"
using namespace std;

adj_map to_adjacency_map(int n, int m);

void print_tours(vector<vector<int>> tours);

int main() {
    int n, m; 
    cin >> n >> m;

    adj_map graph = to_adjacency_map(n, m);
    vector<vector<int>> tours = fhk(graph);
    print_tours(tours);
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

void print_tours(vector<vector<int>> tours) {
    for (int i = 1; i <= tours.size(); i++) {
        cout << "Tag " << i << ": ";
        for (const auto v: tours[i - 1]) {
            cout << v << " ";
        }
        cout << "\n";
    }
}