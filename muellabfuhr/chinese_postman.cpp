#include <bits/stdc++.h>
#include "chinese_postman.hpp"
using namespace std;

vector<int> postman(adj_map &graph) {
    vector<vector<int>> dis, pre;
    for (int i = 0; i < graph.size(); i++) {
        vector<vector<int>> shortetstPaths = dijkstra(graph, i);
        dis.push_back(shortetstPaths[0]);
        pre.push_back(shortetstPaths[1]);
    }

    adj_map odds_graph = create_odds_graph(graph, dis);
}

adj_map create_odds_graph(adj_map &graph, vector<vector<int>> &dis) {
    vector<int> odds;
    for (int i = 0; i < graph.size(); i++) {
        if (graph[i].size() % 2 == 1) {
            odds.push_back(i);
        }
    }

    adj_map odds_graph(graph.size());
    for (int i = 0; i < odds.size(); i++) {
        for (int j = i + 1; j < odds.size(); j++) {
            odds_graph[i][j] = odds_graph[j][i] = dis[i][j];
        }
    }

    return odds_graph;
}

vector<vector<int>> dijkstra(adj_map &graph, int start) {
    vector<int> dis(graph.size(), INT_MAX), pre(graph.size());
    vector<bool> visited(graph.size(), false);

    auto isCloser = [&dis](int a, int b) -> bool {
        return dis[a] < dis[b];
    };

    priority_queue<int, vector<int>, decltype(isCloser)> queue(isCloser);
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