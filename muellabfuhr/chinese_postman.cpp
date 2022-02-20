#include "chinese_postman.hpp"
#include "perfect_matching.hpp"
#include "utility.hpp"

pair<vector<int>, int> postman(adj_map &graph, matrix_2d &dis, matrix_2d &pre) {
    map_2d odds_graph;
    pair<int, int> largest_edge;
    tie(odds_graph, largest_edge) = create_odds_graph(graph, dis);

    set<pair<int, int>> matching = perfect_matching(odds_graph, largest_edge);

    map_2d edge_copies;
    int weight_sum;
    tie(edge_copies, weight_sum) = create_multigraph(graph, matching, pre);

    vector<int> cp_tour = euler_tour(edge_copies);
    return { cp_tour, weight_sum };
}

pair<map_2d, pair<int, int>> create_odds_graph(adj_map &graph, matrix_2d &dis) {
    set<int> odds;
    for (int i = 0; i < graph.size(); i++) {
        if (graph[i].size() % 2 == 1) {
            odds.insert(i);
        }
    }

    map_2d odds_graph;
    int max_cost = 0;
    pair<int, int> largest_edge;

    for (auto it = odds.begin(); it != odds.end(); it++) {
        for (auto jt = it; jt != odds.end(); jt++) {
            if (*it != *jt) {
                odds_graph[*it][*jt] = odds_graph[*jt][*it] = dis[*it][*jt];

                if (dis[*it][*jt] > max_cost) {
                    largest_edge = { *it, *jt };
                    max_cost = dis[*it][*jt];
                }
            }
        }
    }

    return { odds_graph, largest_edge };
}

pair<map_2d, int> create_multigraph(
    adj_map &graph, 
    set<pair<int, int>> &matching, 
    matrix_2d &pre
) {
    map_2d edge_copies;
    int weight_sum = 0;

    for (int i = 0; i < graph.size(); i++) {
        for (auto it = graph[i].begin(); it != graph[i].end(); it++) {
            edge_copies[i][it->first] = 1;
            weight_sum += it->second;
        }
    }

    for (auto it = matching.begin(); it != matching.end(); it++) {
        int v1 = it->first;
        int v2 = pre[it->second][it->first];

        while (v2 != -1) {
            edge_copies[v1][v2] += 1;
            edge_copies[v2][v1] += 1;
            weight_sum += graph[v1][v2];
            v1 = v2;
            v2 = pre[it->second][v2];
        }
    }

    return { edge_copies, weight_sum };
}

vector<int> euler_tour(adj_map &graph, adj_map &edge_copies) {}

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