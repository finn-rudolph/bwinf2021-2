#include <cmath>
#include <iostream>
#include <climits>
#include <chrono>
#include "perfect_matching.hpp"

void exchange(matrix_2d &dis, std::vector<edge> &mat, int i, int j, bool swap_partner) {
    edge e1 = mat[i], e2 = mat[j];
    mat[i] = { e1[0], e2[swap_partner], dis[e1[0]][e2[swap_partner]] };
    mat[j] = { e1[1], e2[!swap_partner], dis[e1[1]][e2[!swap_partner]] };
}

std::vector<edge> two_opt(matrix_2d &dis, std::vector<int> &vertex_set) {
    std::vector<edge> mat;
    for (int i = 0; i < vertex_set.size(); i += 2) {
        int u = vertex_set[i], v = vertex_set[i + 1], w = dis[u][v];
        mat.push_back({ u, v, w });
    }

    next:
        for (int i = 0; i < mat.size(); i++) {
            for (int j = i + 1; j < mat.size(); j++) {
                int curr_cost = mat[i][2] + mat[j][2];

                if (curr_cost > dis[mat[i][0]][mat[j][0]] + dis[mat[i][1]][mat[j][1]]) {
                    exchange(dis, mat, i, j, 0); 
                    goto next;
                }
                if (curr_cost > dis[mat[i][0]][mat[j][1]] + dis[mat[i][1]][mat[j][0]]) {
                    exchange(dis, mat, i, j, 1); 
                    goto next;
                }
            }
        }
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
    matrix_2d &dis,
    std::vector<std::vector<int>> &clusters, 
    int u,
    int v,
    int &open,
    int &odd_cl,
    int threshold,
    std::unordered_map<int, int> &assigned_to
) {
    int min = INT_MAX, min_j = -1;

    for (int j = 0; j < clusters.size(); j++) {
        if (open <= odd_cl && !(clusters[j].size() & 1)) continue;
        if (open > odd_cl && assigned_to.find(v) != assigned_to.end() && j == assigned_to[v]) continue;

        float avg = 0;
        for (int vtx: clusters[j]) avg += dis[u][vtx];
        avg /= (float) clusters[j].size();
        if (avg < min) { 
            min = avg;
            min_j = j;
        }
    }

    if (min <= threshold || open <= odd_cl) {
        clusters[min_j].push_back(u);
        odd_cl += (clusters[min_j].size() & 1) ? 1 : -1;
        assigned_to[u] = min_j;
    } else {
        clusters.push_back({ u });
        odd_cl += 1;
        assigned_to[u] = clusters.size() - 1;
    }
    open -= 1;
}

std::vector<edge> cluster(matrix_2d &dis, std::vector<int> odds, float alpha) {
    auto begin = std::chrono::system_clock::now();

    int n = odds.size(), m = n * (n - 1) / 2;
    int edges[m * 3], pos = 0;

    for (int i = 0; i < odds.size(); i++) {
        for (int j = i + 1; j < odds.size(); j++) {
            int e[3] = { odds[i], odds[j], dis[odds[i]][odds[j]] };
            std::move(e, e + 3, edges + pos);
            pos += 3;
        }
    }

    radix_sort_msd(edges, m, 31);

    int threshold = edges[((int) (alpha * (m - 1)) * 3 + 2)]; // weight of α-Quantile
    std::vector<std::vector<int>> clusters;
    std::unordered_map<int, int> assigned_to;
    int open = n, odd_cl = 0;

    for (int i = m - 1; i >= 0 && open > 0; i--) {
        int u = edges[i * 3], v = edges[i * 3 + 1];

        if (assigned_to.find(u) == assigned_to.end()) 
            assign_cluster(dis, clusters, u, v, open, odd_cl, threshold, assigned_to);
        if (assigned_to.find(v) == assigned_to.end())
            assign_cluster(dis, clusters, v, u, open, odd_cl, threshold, assigned_to);
    }
    
    std::vector<edge> mat;
    int sum = 0;
    for (std::vector<int> &cl: clusters) {
        std::vector<edge> part_mat = two_opt(dis, cl);
        for (edge &e: part_mat) {
            mat.push_back(e);
            sum += e[2];
        }
    }
    std::cout << "Perfect Matching with cost " << sum <<
        " in " << ((std::chrono::duration<float>) (std::chrono::system_clock::now() - begin)).count() << " s \n"; 
    return mat;
}
