#include "fhk_algorithm.hpp"
#include "utility.hpp"
using namespace std;

const int num_tours = 5;

vector<vector<int>> fhk(adj_map &graph) {
    matrix_2d dis, pre;
    for (int i = 0; i < graph.size(); i++) {
        vector<vector<int>> shortest_paths = dijkstra(graph, i);
        dis.push_back(shortest_paths[0]);
        pre.push_back(shortest_paths[1]);
    }

    vector<int> cp_tour;
    int cp_cost;
    tie(cp_tour, cp_cost) = postman(graph, dis, pre);

    cout << "Computed Euler Circuit with cost " << cp_cost << ":\n";
    print_vector(cp_tour);

    int lower_bound = shortest_path_tour(graph, dis);
    int pre_split = 0;
    vector<vector<int>> tours;

    for (int i = 1; i <= num_tours - 1; i++) {
        int max_cost = ((float) i / (float) num_tours) * (float) (cp_cost - lower_bound) 
            + 0.5 * (float) lower_bound;

        int cost = 0;
        int split = 0; // index in cp_tour, not actual vertex
        while (cost <= max_cost) {
            cost += graph[cp_tour[split]][cp_tour[split + 1]];
            split += 1;
        }
        split -= 1;
        cost -= 1;
        int residual = max_cost - cost;

        if (
            dis[cp_tour[split]][0] > 
                graph[cp_tour[split]][cp_tour[split + 1]] + dis[cp_tour[split + 1]][0]
                - 2 * residual
        ) {
            split += 1;
        }

        tours.push_back(construct_tour(cp_tour, pre, pre_split, split));
        pre_split = split;
    }
    tours.push_back(construct_tour(cp_tour, pre, pre_split, cp_tour.size() - 1));
    return tours;
}

vector<int> construct_tour(vector<int> &cp_tour, matrix_2d &pre, int first, int last) {
    vector<int> tour(cp_tour.begin() + first, cp_tour.begin() + last + 1);
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

int shortest_path_tour(adj_map &graph, matrix_2d &dis) {
    int farthest = 0;
    for (int i = 0; i < graph.size(); i++) {
        for (auto it = graph[i].begin(); it != graph[i].end(); it++) {
            farthest = max(dis[0][i] + it->second + dis[it->first][0], farthest);
        }
    }

    return farthest;
}

vector<vector<int>> dijkstra(adj_map &graph, int start) {
    vector<int> dis(graph.size(), INT_MAX), pre(graph.size(), -1);
    vector<bool> visited(graph.size(), false);

    auto is_closer = [&dis](int a, int b) -> bool {
        return dis[a] < dis[b];
    };

    priority_queue<int, vector<int>, decltype(is_closer)> queue(is_closer);
    queue.push(start);
    dis[start] = 0;

    while (queue.size() != 0) {
        int curr = queue.top();
        queue.pop();
        visited[curr] = true;

        for (auto it = graph[curr].begin(); it != graph[curr].end(); it++) {
            if (!visited[it->first] && dis[it->first] > dis[curr] + it->second) {
                dis[it->first] = dis[curr] + it->second;
                pre[it->first] = curr;
                queue.push(it->first);
            }
        }
    }

    return { dis, pre };
}