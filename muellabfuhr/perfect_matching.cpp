#include <vector>
#include <set>
#include <queue>
#include <cmath>
#include <iostream>
#include <chrono>
#include "perfect_matching.hpp"

// This algorithm only works for complete and metric graphs.

std::vector<edge> perfect_matching(map_2d &graph, edge &largest_edge) {
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

    std::vector<edge> matching;
    int cost_sum = 0;

    while (!order.empty()) {
        int a = order.top();
        order.pop();
        int b = order.top();
        order.pop();

        cost_sum += graph[a][b];
        matching.push_back({ a, b });
    }

    std::cout << "Geometric matching solution with total cost " << cost_sum << '\n';

    return matching;
}

float circle_intersection(float r1, float r2, float distance) {
    return (std::pow(distance, 2) + std::pow(r1, 2) - std::pow(r2, 2)) / (2 * distance);
}

void exchange(std::vector<edge> &mat, int i, int j, bool swap_partner) {
    edge e1 = mat[i];
    edge e2 = mat[j];
    mat[i] = { e1[0], e2[swap_partner] };
    mat[j] = { e1[1], e2[!swap_partner] };
}

std::vector<edge> two_opt(map_2d &graph, std::vector<edge> mat) {
    auto begin = std::chrono::system_clock::now();

    if (mat.empty()) 
        for (auto it = graph.begin(); it != graph.end(); it++) 
            mat.push_back({ it->first, (++it)->first });
 
    next: 
        for (int i = 0; i < mat.size(); i++) {
            for (int j = i + 1; j < mat.size(); j++) {
                int curr_cost = graph[mat[i][0]][mat[i][1]] + graph[mat[j][0]][mat[j][1]];

                if (curr_cost - graph[mat[i][0]][mat[j][0]] - graph[mat[i][1]][mat[j][1]] > 0) {
                    exchange(mat, i, j, 0); 
                    goto next;
                }
                if (curr_cost - graph[mat[i][0]][mat[j][1]] - graph[mat[i][1]][mat[j][0]] > 0) {
                    exchange(mat, i, j, 1); 
                    goto next;
                }
            }
        }

    int sum = 0; 
    for (auto &[a, b]: mat) sum += graph[a][b];
    std::cout << "2-opt matching with weight " << sum <<
        " in " << ((std::chrono::duration<float>) (std::chrono::system_clock::now() - begin)).count() << " s \n"; 

    return mat;
}
