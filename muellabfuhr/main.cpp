#include <vector>
#include <iostream>
#include "fhk_algorithm.hpp"
#include "io.hpp"
using namespace std;

int main() {
    int n, m; 
    cin >> n >> m;

    adj_map graph = to_adjacency_map(n, m);
    vector<vector<int>> tours = fhk(graph);
    print_tours(tours, graph);
}