#include <bits/stdc++.h>
#include "types.hpp"
using namespace std;

vector<int> postman(adj_map &graph);

pair<map_2d, pair<int, int>> create_odds_graph(adj_map &graph, matrix_2d &dis);

adj_map create_multigraph(adj_map &graph, set<pair<int, int>> matching, matrix_2d &pre);

vector<vector<int>> dijkstra(adj_map &graph, int start);

vector<int> euler_tour(adj_map &graph, adj_map &edge_copies);