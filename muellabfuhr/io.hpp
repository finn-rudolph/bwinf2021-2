#include <vector>
#include <string>
#include "types.hpp"

adj_map to_adjacency_map(int n, int m);

void print_tours(std::vector<std::vector<int>> &tours, adj_map &graph);

void print_graph(adj_map &graph);

void print_vector(std::vector<int> &vec);

void write_complete_graph(matrix_2d &dis, std::vector<int> odds, std::string filename);