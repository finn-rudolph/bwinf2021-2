#include <vector>
#include <string>
#include <iostream>
#include "fhk_algorithm.hpp"
#include "io.hpp"

int main(int argc, char* argv[]) {
    int k = 5;
    if (argc > 2) {
        std::cout << "Too many arguments. Run with: ./main < [input file] [k]\n";
        exit(EXIT_FAILURE);
    } else if (argc == 2) {
        k = std::stoi(argv[1]);
    }
    std::cout << "Number of tours k = " << k << '\n';

    int n, m; 
    std::cin >> n >> m;

    adj_map graph = to_adjacency_map(n, m);
    std::vector<std::vector<int>> tours = fhk(graph, k);
    print_tours(tours, graph);
}