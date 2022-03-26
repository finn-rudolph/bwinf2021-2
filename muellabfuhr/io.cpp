#include <iostream>
#include <fstream>
#include "io.hpp"

adj_map to_adjacency_map(int n, int m) {
    adj_map adjMap(n);

    for (int i = 0; i < m; i++) {
        int v1, v2, w;
        std::cin >> v1 >> v2 >> w;
        adjMap[v1][v2] = adjMap[v2][v1] = w;
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
    for (int a = 0; a < graph.size(); a++) {
        std::cout << a << ": ";
        for (const auto &[b, w]: graph[a]) {
            std::cout << b << " -> " << w<< ";   ";
        }
    }
    std::cout << "\n" << std::endl;
}

void print_vector(std::vector<int> &vec) {
    for (const auto &e: vec) {
        std::cout << e << " ";
    }
    std::cout << "\n" << std::endl;
}

void write_complete_graph(matrix_2d &dis, std::vector<int> odds, std::string filename) {
    std::ofstream out_file(filename);
    int n = odds.size();
    out_file << n << ' ' << (n * (n - 1) / 2) << '\n';

    for (int i = 0; i < odds.size(); i++)
        for (int j = i + 1; j < odds.size(); j++)
            out_file << i << ' ' << j << ' ' << dis[odds[i]][odds[j]] << '\n'; 
        
}