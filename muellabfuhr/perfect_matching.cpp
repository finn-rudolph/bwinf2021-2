#include "perfect_matching.hpp"
#include "utility.hpp"
using namespace std;

// This algorithm only works for complete and metric graphs.

set<pair<int, int>> perfect_matching(map_2d &graph, pair<int, int> &largest_edge) {
    auto [a, b] = largest_edge;
    int max_cost = graph[a][b];

    vector<float> dis_a(graph.size());
    dis_a[a] = 0;
    dis_a[b] = max_cost;

    auto smaller_dis = [&dis_a](int a, int b) -> bool {
        return dis_a[a] < dis_a[b];
    };

    priority_queue<int, vector<int>, decltype(smaller_dis)> order(smaller_dis);
    order.push(a);
    order.push(b);

    for (const auto &[v, ignore]: graph) {
        if (v!= a && v != b) {
            float dis = circle_intersection(
                (float) graph[v][a],
                (float) graph[v][b], 
                (float) max_cost
            );
            dis_a[v] = dis;
            order.push(v);
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
