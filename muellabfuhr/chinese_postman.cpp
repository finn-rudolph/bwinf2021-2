#include <set>
#include <stack>
#include <iostream>
#include "chinese_postman.hpp"
#include "io.hpp"
#include "perfect_matching.hpp"

std::pair<std::vector<int>, int> postman(adj_map &graph, matrix_2d &dis, matrix_2d &pre, float alpha) {
    std::vector<int> odds;
    for (int v = 0; v < graph.size(); v++)
        if (graph[v].size() & 1) odds.push_back(v);

    write_complete_graph(dis, odds, "graph.txt");
    std::vector<edge> matching = cluster(dis, odds, alpha);

    adj_map augmented(graph.size());
    int weight_sum = 0;

    for (int u = 0; u < graph.size(); u++) {
        for (const auto &[v, w]: graph[u]) {
            augmented[u][v] = 1;
            weight_sum += w;
        }
    }
    weight_sum /= 2;

    for (auto &[start, target, _]: matching) {
        int next = pre[target][start];
        int curr = start;

        while (next != -1) {
            augmented[curr][next] += 1;
            augmented[next][curr] += 1;
            weight_sum += graph[curr][next];
            curr = next;
            next = pre[target][next];
        }
    }

    std::vector<int> postman_tour = eulerian_circuit(augmented);
    return { postman_tour, weight_sum };
}

std::vector<int> eulerian_circuit(adj_map &graph) {
    std::vector<int> circuit;
    std::stack<int> subtour;
    subtour.push(0);

    while (!subtour.empty()) {
        int curr = subtour.top();

        if (graph[curr].empty()) {
            subtour.pop();
            circuit.push_back(curr);
        } else {
            int next = graph[curr].begin()->first;
            graph[curr][next] = graph[next][curr] -= 1;

            if (graph[curr][next] == 0) {
                graph[curr].erase(next);
                graph[next].erase(curr);
            }
            subtour.push(next);
        }
    }
    return circuit;
}