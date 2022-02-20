#include <bits/stdc++.h>
#include "types.hpp"
#include "chinese_postman.hpp"
using namespace std;

set<vector<int>> fhk(adj_map &graph);

int shortest_path_tour(adj_map &graph, matrix_2d &dis);

vector<vector<int>> dijkstra(adj_map &graph, int start);
