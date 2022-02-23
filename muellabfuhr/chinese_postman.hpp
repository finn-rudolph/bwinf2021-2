#include <bits/stdc++.h>
#include "types.hpp"

std::pair<std::vector<int>, int> postman(adj_map &graph, matrix_2d &dis, matrix_2d &pre);

std::pair<map_2d, std::pair<int, int>> create_odds_graph(adj_map &graph, matrix_2d &dis);

std::pair<map_2d, int> create_multigraph(
    adj_map &graph, 
    std::set<std::pair<int, int>> &matching, 
    matrix_2d &pre
);

std::vector<int> euler_tour(map_2d &graph);

void remove_edge(map_2d &graph, int v1, int v2);

void dfs_tour(int start, map_2d& graph, std::vector<int>& subtour);

