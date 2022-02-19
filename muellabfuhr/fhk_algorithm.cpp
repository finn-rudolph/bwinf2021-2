#include <bits/stdc++.h>
#include "fhk_algorithm.hpp"
using namespace std;

set<vector<int>> fhk(const vector<map<int, int>> adjMap) {
    vector<vector<int>> dis, pre;
    for (int i = 0; i < adjMap.size(); i++) {
        vector<vector<int>> shortetstPaths = dijkstra(adjMap, i);
        dis.push_back(shortetstPaths[0]);
        pre.push_back(shortetstPaths[1]);
    }
}

vector<vector<int>> dijkstra(const vector<map<int, int>> &adjMap, int start) {
    vector<int> dis(adjMap.size(), INT_MAX), pre(adjMap.size());
    vector<bool> visited(adjMap.size(), false);

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

        for (auto it = adjMap[curr].begin(); it != adjMap[curr].end(); it++) {
            if (!visited[it->first] && dis[it->first] > dis[curr] + it->second) {
                dis[it->first] = dis[curr] + it->second;
                pre[it->first] = curr;
                queue.push(it->first);
            }
        }
    }

    return { dis, pre };
}
