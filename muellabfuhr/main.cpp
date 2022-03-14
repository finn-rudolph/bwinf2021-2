#include <vector>
#include <iostream>
#include "fhk_algorithm.hpp"
#include "io.hpp"

int main() {
    int n, m; 
    std::cin >> n >> m;

    adj_map graph = to_adjacency_map(n, m);
    std::vector<std::vector<int>> tours = fhk(graph);
    print_tours(tours, graph);
}