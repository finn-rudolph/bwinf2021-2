#include "chinese_postman.hpp"
#include "perfect_matching.hpp"
#include "utility.hpp"
using namespace std;

pair<vector<int>, int> postman(adj_map &graph, matrix_2d &dis, matrix_2d &pre) {
    auto [odds_graph, largest_edge] = create_odds_graph(graph, dis);

    set<pair<int, int>> matching = perfect_matching(odds_graph, largest_edge);

    auto [augmented, weight_sum] = create_multigraph(graph, matching, pre);

    vector<int> postman_tour = eulerian_circuit(augmented);
    return { postman_tour, weight_sum };
}

pair<map_2d, pair<int, int>> create_odds_graph(adj_map &graph, matrix_2d &dis) {
    set<int> odds;
    for (int v = 0; v < graph.size(); v++) {
        if (graph[v].size() % 2 == 1) {
            odds.insert(v);
        }
    }

    map_2d odds_graph;
    int max_cost = 0;
    pair<int, int> largest_edge;

    for (const auto &a: odds) {
        for (const auto &b: odds) {
            if (a != b) {
                odds_graph[a][b] = odds_graph[b][a] = dis[a][b];

                if (dis[a][b] > max_cost) {
                    largest_edge = { a, b };
                    max_cost = dis[a][b];
                }
            }
        }
    }

    return { odds_graph, largest_edge };
}

pair<map_2d, int> create_multigraph(
    adj_map &graph, 
    set<pair<int, int>> &matching, 
    matrix_2d &pre
) {
    map_2d augmented;
    int weight_sum = 0;

    for (int a = 0; a < graph.size(); a++) {
        for (const auto &[b, w]: graph[a]) {
            augmented[a][b] = 1;
            weight_sum += w;
        }
    }
    weight_sum /= 2;

    for (auto [start, target]: matching) {
        int b = pre[target][start];
        int a = start;

        while (b != -1) {
            augmented[a][b] += 1;
            augmented[b][a] += 1;
            weight_sum += graph[a][b];
            a = b;
            b = pre[target][b];
        }
    }
    return { augmented, weight_sum };
}

vector<int> eulerian_circuit(map_2d &graph) {
    vector<int> circuit;
    stack<int> subtour;
    subtour.push(0);

    while (!subtour.empty()) {
        int curr = subtour.top();

        if (graph[curr].empty()) {
            subtour.pop();
            circuit.push_back(curr);
        } else {
            int next = graph[curr].begin()->first;
            remove_edge(graph, curr, next);
            subtour.push(next);
        }
    }
    return circuit;
}

void remove_edge(map_2d &graph, int v1, int v2) {
    graph.at(v1).at(v2) -= 1;
    graph.at(v2).at(v1) -= 1;

    if (graph.at(v1).at(v2) == 0) {
        graph.at(v1).erase(v2);
        graph.at(v2).erase(v1);
    }

    if (graph.at(v1).empty()) {
        graph.erase(v1);
    }

    if (graph.at(v2).empty()) {
        graph.erase(v2);
    }
}

void dfs(int start, map_2d &graph, vector<int> &subtour) {
    if (!graph[start].empty()) {
        int next = graph[start].begin()->first;
        remove_edge(graph, start, next);
        dfs(next, graph, subtour);
    }
    subtour.push_back(start);
}