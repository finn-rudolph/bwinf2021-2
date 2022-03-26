#include <vector>
#include <set>
#include <queue>
#include <unordered_map>
#include <iterator>
#include <cmath>
#include <iostream>
#include <climits>
#include <chrono>
#include "perfect_matching.hpp"

// This algorithm only works for complete and metric graphs.

std::vector<edge> perfect_matching(map_2d &graph, edge &largest_edge) {
    if (graph.empty()) return { };
    auto [max1, max2, max_cost] = largest_edge;

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

void exchange(map_2d &graph, std::vector<edge> &mat, int i, int j, bool swap_partner) {
    edge e1 = mat[i];
    edge e2 = mat[j];
    mat[i] = { e1[0], e2[swap_partner], graph[e1[0]][e2[swap_partner]] };
    mat[j] = { e1[1], e2[!swap_partner], graph[e1[1]][e2[!swap_partner]] };
}

std::vector<edge> two_opt(map_2d &graph, std::vector<edge> mat) {
    auto begin = std::chrono::system_clock::now();

    if (mat.empty()) 
        for (auto it = graph.begin(); it != graph.end(); it++) 
            mat.push_back({ it->first, (++it)->first });
 
    next: 
        for (int i = 0; i < mat.size(); i++) {
            for (int j = i + 1; j < mat.size(); j++) {
                int curr_cost = mat[i][2] + mat[j][2];

                if (curr_cost - graph[mat[i][0]][mat[j][0]] - graph[mat[i][1]][mat[j][1]] > 0) {
                    exchange(graph, mat, i, j, 0); 
                    goto next;
                }
                if (curr_cost - graph[mat[i][0]][mat[j][1]] - graph[mat[i][1]][mat[j][0]] > 0) {
                    exchange(graph, mat, i, j, 1); 
                    goto next;
                }
            }
        }

    int sum = 0; 
    for (auto &[a, b, w]: mat) sum += w;
    std::cout << "2-opt matching with weight " << sum <<
        " in " << ((std::chrono::duration<float>) (std::chrono::system_clock::now() - begin)).count() << " s \n"; 

    return mat;
}

void radix_sort_msd(int* arr, int length, int h) {
    if (length <= 1 || h == -1) return;
    int u = 0, v = length - 1;

    while (u < v) {
        if ((arr[u * 3 + 2] >> h) & (int) 1) {
            std::swap_ranges(arr + u * 3, arr + u * 3 + 3, arr + v * 3);
            v -= 1;
        } else {
            u += 1;
        }

    }

    if (!((arr[u * 3 + 2] >> h) & (int) 1)) u += 1;
    radix_sort_msd(arr, u, h - 1);
    radix_sort_msd(arr + u * 3, length - u, h - 1);
}

void assign_cluster(
    map_2d &graph,
    std::vector<std::set<int>> &clusters, 
    int u,
    int v,
    int &open,
    int &odd,
    int threshold,
    std::unordered_map<int, int> &assigned_to
) {
    int min = INT_MAX, min_j = -1;

    for (int j = 0; j < clusters.size(); j++) {
        if (open <= odd && !(clusters[j].size() & 1)) continue;
        if (open > odd && assigned_to.find(v) != assigned_to.end() && j == assigned_to[v]) continue;
        float avg = 0;
        for (int vtx: clusters[j]) avg += graph[u][vtx];
        avg /= (float) clusters[j].size();
        if (avg < min) { 
            min = avg;
            min_j = j;
        }
    }

    if (min <= threshold || open <= odd) {
        clusters[min_j].insert(u);
        odd += (clusters[min_j].size() & 1) ? 1 : -1;
        assigned_to[u] = min_j;
    } else {
        clusters.push_back({ u });
        odd += 1;
        assigned_to[u] = clusters.size() - 1;
    }
    open -= 1;
}

std::vector<std::set<int>> cluster(map_2d &graph, float alpha, float beta) {
    int n = graph.size(), m = n * (n - 1) / 2;
    int edges[m * 3];
    int count = 0, i = 0;

    for (auto it = graph.begin(); it != graph.end(); it++) {
        auto jt = it->second.begin();
        std::advance(jt, i);
        while (jt != it->second.end()) {
            int edge[3] = { it->first, jt->first, jt->second };
            std::move(edge, edge + 3, edges + count);
            jt++;
            count += 3;
        }
        i += 1;
    }

    radix_sort_msd(edges, m, 31);

    int threshold = edges[((int) (alpha * (m - 1)) * 3 + 2)];
    int beta_i = (int) (beta * (m - 1));
    
    std::vector<std::set<int>> clusters;
    std::unordered_map<int, int> assigned_to;
    int open = n, odd = 0;

    for (int i = m - 1; i >= 0 && open > 0; i--) {
        int u = edges[i * 3], v = edges[i * 3 + 1], w = edges[i * 3 + 2];

        if (assigned_to.find(u) == assigned_to.end()) 
            assign_cluster(graph, clusters, u, v, open, odd, threshold, assigned_to);
        if (assigned_to.find(v) == assigned_to.end())
            assign_cluster(graph, clusters, v, u, open, odd, threshold, assigned_to);
    }
    
    return clusters;
}
