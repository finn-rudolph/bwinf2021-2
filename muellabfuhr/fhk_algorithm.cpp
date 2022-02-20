#include "fhk_algorithm.hpp"

set<vector<int>> fhk(adj_map &graph) {
    matrix_2d dis, pre;
    for (int i = 0; i < graph.size(); i++) {
        vector<vector<int>> shortetst_paths = dijkstra(graph, i);
        dis.push_back(shortetst_paths[0]);
        pre.push_back(shortetst_paths[1]);
    }

    vector<int> postman_tour = postman(graph, dis, pre);
    int lower_bound = shortest_path_tour(graph, dis);
}

int shortest_path_tour(adj_map &graph, matrix_2d &dis) {
    int farthest = 0;
    for (int i = 0; i < graph.size(); i++) {
        for (auto it = graph[i].begin(); it != graph[i].end(); it++) {
            farthest = max(dis[0][i] + it->second + dis[it->first][0], farthest);
        }
    }

    return farthest;
}

vector<vector<int>> dijkstra(adj_map &graph, int start) {
    vector<int> dis(graph.size(), INT_MAX), pre(graph.size(), -1);
    vector<bool> visited(graph.size(), false);

    auto is_closer = [&dis](int a, int b) -> bool {
        return dis[a] < dis[b];
    };

    priority_queue<int, vector<int>, decltype(is_closer)> queue(is_closer);
    queue.push(start);
    dis[start] = 0;

    while (queue.size() != 0) {
        int curr = queue.top();
        queue.pop();
        visited[curr] = true;

        for (auto it = graph[curr].begin(); it != graph[curr].end(); it++) {
            if (!visited[it->first] && dis[it->first] > dis[curr] + it->second) {
                dis[it->first] = dis[curr] + it->second;
                pre[it->first] = curr;
                queue.push(it->first);
            }
        }
    }

    return { dis, pre };
}