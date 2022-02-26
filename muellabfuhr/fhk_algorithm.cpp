#include "fhk_algorithm.hpp"
#include "utility.hpp"
using namespace std;

const int num_tours = 5;

vector<vector<int>> fhk(adj_map &graph) {
    matrix_2d dis, pre;
    for (int v = 0; v < graph.size(); v++) {
        auto [distances, predecessors] = dijkstra(graph, v);
        dis.push_back(distances);
        pre.push_back(predecessors);
    }

    auto [cpp_tour, cpp_cost] = postman(graph, dis, pre);

    cout << "Lösung des Chinese Postman Problems erstellt, Gesamtkosten " << cpp_cost << "\n";
    print_vector(cpp_tour);

    int lower_bound = farthest_edge_cost(graph, dis);
    int pre_split = 0;
    vector<vector<int>> tours;

    for (int i = 1; i <= num_tours - 1; i++) {
        int max_cost = ((float) i / (float) num_tours) * (float) (cpp_cost - lower_bound) 
            + 0.5 * (float) lower_bound;

        int cost = 0;
        int split = 0; // index in cp_tour, not actual vertex
        while (cost <= max_cost) {
            cost += graph[cpp_tour[split]][cpp_tour[split + 1]];
            split += 1;
        }
        split -= 1;
        cost -= 1;
        int residual = max_cost - cost;

        if (
            dis[cpp_tour[split]][0] > 
                graph[cpp_tour[split]][cpp_tour[split + 1]] + dis[cpp_tour[split + 1]][0]
                - 2 * residual
        ) {
            split += 1;
        }

        tours.push_back(construct_tour(cpp_tour, pre, pre_split, split));
        pre_split = split;
    }
    tours.push_back(construct_tour(cpp_tour, pre, pre_split, cpp_tour.size() - 1));
    return tours;
}

vector<int> construct_tour(vector<int> &cpp_tour, matrix_2d &pre, int first, int last) {
    vector<int> tour(cpp_tour.begin() + first, cpp_tour.begin() + last + 1);
    close_tour(tour, pre, true);
    close_tour(tour, pre, false);

    return tour;
}

void close_tour(vector<int> &tour, matrix_2d &pre, bool append_front) {
    int curr = pre[0][append_front ? *tour.begin(): *(--tour.end())];

    while (curr != -1) {
        if (append_front) tour.insert(tour.begin(), curr);
        else tour.push_back(curr);
        curr = pre[0][curr];
    }
}

int farthest_edge_cost(adj_map &graph, matrix_2d &dis) {
    int farthest = 0;
    for (int a = 0; a < graph.size(); a++) {
        for (const auto &[b, w]: graph[a]) {
            farthest = max(dis[0][a] + w + dis[b][0], farthest);
        }
    }

    return farthest;
}

pair<vector<int>, vector<int>> dijkstra(adj_map &graph, int start) {
    vector<int> dis(graph.size(), INT_MAX), pre(graph.size(), -1);
    vector<bool> visited(graph.size(), false);

    auto is_closer = [&dis](int a, int b) -> bool {
        return dis[a] > dis[b];
    };

    priority_queue<int, vector<int>, decltype(is_closer)> queue(is_closer);
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