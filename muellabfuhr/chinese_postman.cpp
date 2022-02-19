#include "chinese_postman.hpp"
#include "perfect_matching.hpp"

vector<int> postman(adj_map &graph) {
    vector<vector<int>> dis, pre;
    for (int i = 0; i < graph.size(); i++) {
        vector<vector<int>> shortetst_paths = dijkstra(graph, i);
        dis.push_back(shortetst_paths[0]);
        pre.push_back(shortetst_paths[1]);
    }

    map_2d odds_graph; pair<int, int> largest_edge;
    tie(odds_graph, largest_edge) = create_odds_graph(graph, dis);

    set<pair<int, int>> matching = perfect_matching(odds_graph, largest_edge);
    for (auto it = matching.begin(); it != matching.end(); it++) {
        cout << (*it).first << " " << (*it).second << "\n";
    }
}

pair<map_2d, pair<int, int>> create_odds_graph(
    adj_map &graph, 
    vector<vector<int>> &dis
) {
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

vector<vector<int>> dijkstra(adj_map &graph, int start) {
    vector<int> dis(graph.size(), INT_MAX), pre(graph.size());
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