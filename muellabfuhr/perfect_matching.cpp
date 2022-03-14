#include <vector>
#include <set>
#include <queue>
#include <cmath>
#include "perfect_matching.hpp"

// This algorithm only works for complete and metric graphs.

std::set<std::pair<int, int>> perfect_matching(map_2d &graph, std::pair<int, int> &largest_edge) {
    if (graph.empty()) return { };
    auto [max1, max2] = largest_edge;
    int max_cost = graph.at(max1).at(max2);

    std::map<int, float> dis_max1;
    dis_max1[max1] = 0.0;
    dis_max1[max2] = (float) max_cost;

    auto smaller_dis = [&dis_max1](int a, int b) -> bool {
        return dis_max1[a] > dis_max1[b];
    };

    std::priority_queue<int, std::vector<int>, decltype(smaller_dis)> order(smaller_dis);
    order.push(max1);
    order.push(max2);

    for (const auto &[v, ignore]: graph) {
        if (v != max1 && v != max2) {
            float dis = circle_intersection(
                (float) graph[v][max1],
                (float) graph[v][max2], 
                (float) max_cost
            );
            dis_max1[v] = dis;
            order.push(v);
        }
    }

    std::set<std::pair<int, int>> matching;

    while (!order.empty()) {
        int a = order.top();
        order.pop();
        int b = order.top();
        order.pop();

        matching.insert({ a, b });
    }

    return matching;
}

float circle_intersection(float r1, float r2, float distance) {
    return (std::pow(distance, 2) + std::pow(r1, 2) - std::pow(r2, 2)) / (2 * distance);
}
