#include <iostream>
#include <fstream>
#include "io.hpp"

adj_map to_adjacency_map(int n, int m) {
    adj_map adjMap(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        adjMap[u][v] = adjMap[v][u] = w;
    }
    return adjMap;
}

void print_tours(std::vector<std::vector<int>> &tours, adj_map &graph) {
    int largest = 0;
    for (int i = 0; i < tours.size(); i++) {
        std::cout << "Tag " << (i + 1) << ": ";
        int cost = 0;

        for (int j = 0; j < tours[i].size(); j++) {
            std::cout << tours[i][j] << " ";
            if (j != 0) cost += graph[tours[i][j]][tours[i][j - 1]];
        }

        std::cout << "| Gesamtlänge: " << cost << "\n";
        if (cost > largest) largest = cost;
    }
    std::cout << "\nLänge der längsten Tagestour: " << largest << std::endl;
}

void print_graph(adj_map &graph) {
    for (int u = 0; u < graph.size(); u++) {
        std::cout << u << ": ";
        for (const auto &[v, w]: graph[u]) {
            std::cout << v << " -> " << w<< ";   ";
        }
    }
    std::cout << "\n\n";
}

void print_vector(std::vector<int> &vec) {
    for (const auto &elem: vec) std::cout << elem << " ";
    std::cout << "\n\n";
}

void write_complete_graph(matrix_2d &dis, std::vector<int> &odds, std::string filename) {
    std::ofstream out_file(filename);
    int n = odds.size();
    out_file << n << ' ' << (n * (n - 1) / 2) << '\n';

    for (int i = 0; i < odds.size(); i++)
        for (int j = i + 1; j < odds.size(); j++)
            out_file << i << ' ' << j << ' ' << dis[odds[i]][odds[j]] << '\n'; 
}