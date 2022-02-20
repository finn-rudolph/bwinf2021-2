#include <bits/stdc++.h>
#include "types.hpp"
#include "chinese_postman.hpp"
using namespace std;

set<vector<int>> fhk(adj_map &graph);

vector<int> construct_tour(vector<int> &cp_tour, matrix_2d &pre, int first, int last);

void close_tour(vector<int> &tour,int target,matrix_2d &pre, bool append_front);

int shortest_path_tour(adj_map &graph, matrix_2d &dis);

vector<vector<int>> dijkstra(adj_map &graph, int start);
