#include "perfect_matching.hpp"

// This algorithm only works for complete and metric graphs.

set<pair<int, int>> perfect_matching(map_2d &graph, pair<int, int> &largest_edge) {
    int a, b; 
    tie(a, b) = largest_edge;
    int max_length = graph[a][b];

    vector<float> dis_to_a(graph.size());
    dis_to_a[a] = 0;
    dis_to_a[b] = max_length;

    auto smaller_dis = [&dis_to_a](int a, int b) -> bool {
        return dis_to_a[a] < dis_to_a[b];
    };

    priority_queue<int, vector<int>, decltype(smaller_dis)> order(smaller_dis);
    order.push(a);
    order.push(b);

    for (auto it = graph.begin(); it != graph.end(); it++) {
        if (it->first != a && it->first != b) {
            int cost_a = graph[it->first][a];
            int cost_b = graph[it->first][b];
            float dis = circle_intersection(
                (float) cost_a,
                (float) cost_b, 
                (float) max_length
            );
            dis_to_a[it->first] = dis;
            order.push(it->first);
        }
    }

    set<pair<int, int>> matching;

    while (!order.empty()) {
        int u = order.top();
        order.pop();
        int v = order.top();
        order.pop();

        matching.insert(make_pair(u, v));
    }

    return matching;
}

float circle_intersection(float r1, float r2, float distance) {
    return (pow(distance, 2) + pow(r1, 2) - pow(r2, 2)) / (2 * distance);
}
