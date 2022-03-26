#include <queue>
#include <iostream>
#include <climits>
#include "fhk_algorithm.hpp"
#include "io.hpp"

std::vector<std::vector<int>> fhk(adj_map &graph, int k, float alpha) {
    matrix_2d dis, pre;
    for (int v = 0; v < graph.size(); v++) {
        auto [distances, predecessors] = dijkstra(graph, v);
        dis.push_back(distances);
        pre.push_back(predecessors);
    }

    auto [cpp_tour, cpp_cost] = postman(graph, dis, pre, alpha);

    std::cout << "Created Chinese Postman tour with cost: " << cpp_cost << "\n";
    print_vector(cpp_tour);

    int lower_bound = farthest_edge_cost(graph, dis);
    int pre_split = 0;
    int cost = 0;
    std::vector<std::vector<int>> tours;

    for (int i = 1; i <= k - 1; i++) {
        int max_cost = ((float) i / (float) k) * 
            (float) (cpp_cost - lower_bound) + 0.5 * (float) lower_bound;

        int split = pre_split; // index in cpp_tour
        while (cost <= max_cost) {
            cost += graph[cpp_tour[split]][cpp_tour[split + 1]];
            split += 1;
        }

        int residual = max_cost - cost - graph[cpp_tour[split]][cpp_tour[split + 1]];

        if (
            dis[cpp_tour[split]][0] <= graph[cpp_tour[split]][cpp_tour[split + 1]] 
                + dis[cpp_tour[split + 1]][0]
                - 2 * residual
        ) {
            split -= 1;
            cost -= graph[cpp_tour[split]][cpp_tour[split + 1]];
        }
        
        tours.push_back(construct_tour(cpp_tour, pre, pre_split, split));
        pre_split = split;
    }
    tours.push_back(construct_tour(cpp_tour, pre, pre_split, cpp_tour.size() - 1));
    return tours;
}

std::vector<int> construct_tour(std::vector<int> &cpp_tour, matrix_2d &pre, int start, int end) {
    std::vector<int> tour(cpp_tour.begin() + start, cpp_tour.begin() + end + 1);
    close_tour(tour, pre, 1);
    close_tour(tour, pre, 0);

    return tour;
}

void close_tour(std::vector<int> &tour, matrix_2d &pre, bool append_front) {
    int curr = pre[0][append_front ? *tour.begin() : *(--tour.end())];

    while (curr != -1) {
        if (append_front) tour.insert(tour.begin(), curr);
        else tour.push_back(curr);
        curr = pre[0][curr];
    }
}

int farthest_edge_cost(adj_map &graph, matrix_2d &dis) {
    int farthest = 0;
    for (int u = 0; u < graph.size(); u++) {
        for (const auto &[v, w]: graph[u]) {
            farthest = std::max(dis[0][u] + w + dis[v][0], farthest);
        }
    }
    return farthest;
}

std::pair<std::vector<int>, std::vector<int>> dijkstra(adj_map &graph, int start) {
    std::vector<int> dis(graph.size(), INT_MAX), pre(graph.size(), -1);
    std::vector<bool> visited(graph.size(), false);

    auto is_closer = [&dis](int u, int v) -> bool {
        return dis[u] > dis[v];
    };

    std::priority_queue<int, std::vector<int>, decltype(is_closer)> queue(is_closer);
    queue.push(start);
    dis[start] = 0;

    while (!queue.empty()) {
        int curr = queue.top();
        queue.pop();
        visited[curr] = true;

        for (const auto &[next, w]: graph[curr]) {
            if (!visited[next] && dis[next] > dis[curr] + w) {
                dis[next] = dis[curr] + w;
                pre[next] = curr;
                queue.push(next);
            }
        }
    }

    return { dis, pre };
}