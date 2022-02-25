#include <bits/stdc++.h>
#include "types.hpp"
#include "chinese_postman.hpp"

std::vector<std::vector<int>> fhk(adj_map &graph);

std::vector<int> construct_tour(std::vector<int> &cp_tour, matrix_2d &pre, int first, int last);

void close_tour(std::vector<int> &tour, matrix_2d &pre, bool append_front);

int shortest_path_tour(adj_map &graph, matrix_2d &dis);

std::vector<std::vector<int>> dijkstra(adj_map &graph, int start);
