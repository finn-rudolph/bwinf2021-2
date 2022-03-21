#include <vector>
#include <set>
#include <queue>
#include <cmath>
#include <iostream>
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
    int cost_sum = 0;

    while (!order.empty()) {
        int a = order.top();
        order.pop();
        int b = order.top();
        order.pop();

        cost_sum += graph[a][b];
        matching.insert({ a, b });
    }
    std::cout << "Computed Minimum Weighted Perfect Matching with cost " << cost_sum << '\n'; 

    return matching;
}

float circle_intersection(float r1, float r2, float distance) {
    return (std::pow(distance, 2) + std::pow(r1, 2) - std::pow(r2, 2)) / (2 * distance);
}

std::vector<edge> two_opt(map_2d &graph) {
    std::vector<edge> mat;
    for (auto it = graph.begin(); it != graph.end(); it++) 
        mat.push_back({ it->first, (++it)->first });

    for (auto p: mat) std::cout << p.a << " " << p.b << "\n";


    edge exchange[2] = { { 0, 0 } };
    int best_ind[2] = { 0 };
    int impr = 1;
    while (impr > 0) {   
        impr = 0;    
        for (int i = 0; i < mat.size(); i++) {
            for (int j = i + 1; j < mat.size(); j++) {
                int curr_cost = graph[mat[i].a][mat[i].b] + graph[mat[j].a][mat[j].b];
                if (graph[mat[i].a][mat[j].a] + graph[mat[i].b][mat[j].b] - curr_cost > impr) {
                    exchange[0] = { mat[i].a, mat[j].a };
                    exchange[1] = { mat[i].b, mat[j].b };
                    best_ind[0] = i; best_ind[1] = j;
                    impr = graph[mat[i].a][mat[j].a] + graph[mat[i].b][mat[j].b] - curr_cost;
                }
                if (graph[mat[i].a][mat[j].b] + graph[mat[i].b][mat[j].a] - curr_cost > impr) {
                    exchange[0] = { mat[i].a, mat[j].b };
                    exchange[1] = { mat[i].b, mat[j].a };
                    best_ind[0] = i; best_ind[1] = j;
                    impr = graph[mat[i].a][mat[j].b] + graph[mat[i].b][mat[j].a] - curr_cost;
                }
            }
        }
        if (impr > 0) {
            mat[best_ind[0]] = exchange[0];
            mat[best_ind[1]] = exchange[1];
        }
    }
    int sum = 0; 
    std::cout << "2-opt matching:\n";
    for (auto &[a, b]: mat) {
        std::cout << a << " " << b << '\n';
        sum += graph[a][b];
    }
    std::cout << sum <<  '\n' << std::endl;
    return mat;
}
