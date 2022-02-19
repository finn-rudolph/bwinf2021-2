#include <bits/stdc++.h>
#include "types.hpp"
using namespace std;

vector<int> postman(adj_map &graph);

pair<map_2d, pair<int, int>> create_odds_graph(
    adj_map &graph, 
    vector<vector<int>> &dis
);

vector<vector<int>> dijkstra(adj_map &graph, int start);