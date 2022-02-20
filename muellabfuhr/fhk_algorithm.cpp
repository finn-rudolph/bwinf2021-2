#include "fhk_algorithm.hpp"

int shortest_path_tour(adj_map &graph, matrix_2d &dis) {
    int farthest = 0;
    for (int i = 0; i < graph.size(); i++) {
        for (auto it = graph[i].begin(); it != graph[i].end(); it++) {
            farthest = max(dis[0][i] + it->second + dis[it->first][0], farthest);
        }
    }

    return farthest;
}