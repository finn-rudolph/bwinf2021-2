#include <bits/stdc++.h>
using namespace std;

typedef vector<map<int, int>> adj_map;

set<vector<int>> fhk(adj_map &graph);

adj_map create_odds_graph(adj_map &graph, vector<vector<int>> &dis);

vector<vector<int>> dijkstra(adj_map &graph, int start);