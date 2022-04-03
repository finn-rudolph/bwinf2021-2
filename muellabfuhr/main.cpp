#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include "fhk_algorithm.hpp"
#include "io.hpp"

int main(int argc, char* argv[]) {
    int k = 5;
    float alpha = 0.6;
    if (argc > 3) {
        std::cout << "Too many arguments. Run with: ./main < [input file] [k] [α]\n";
        exit(EXIT_FAILURE);
    }
    if (argc >= 2) k = std::stoi(argv[1]);
    if (argc >= 3) alpha = std::stof(argv[2]);
    
    std::cout << "k = " << k << ", α = " << alpha << '\n';

    auto begin = std::chrono::system_clock::now();
    int n, m; 
    std::cin >> n >> m;

    adj_map graph = to_adjacency_map(n, m);
    std::vector<std::vector<int>> tours = fhk(graph, k, alpha);
    print_tours(tours, graph);

    std::cout << ((std::chrono::duration<float>) (std::chrono::system_clock::now() - begin)).count() << " s \n"; 
}