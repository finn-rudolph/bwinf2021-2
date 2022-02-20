#include <bits/stdc++.h>
#include "types.hpp"
using namespace std;

pair<vector<int>, int> postman(adj_map &graph, matrix_2d &dis, matrix_2d &pre);

pair<map_2d, pair<int, int>> create_odds_graph(adj_map &graph, matrix_2d &dis);

pair<map_2d, int> create_multigraph(
    adj_map &graph, 
    set<pair<int, int>> &matching, 
    matrix_2d &pre
);

vector<int> euler_tour(map_2d edge_copies);
