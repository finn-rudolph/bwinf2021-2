#include "chinese_postman.hpp"
#include "perfect_matching.hpp"
#include "utility.hpp"
using namespace std;

pair<vector<int>, int> postman(adj_map &graph, matrix_2d &dis, matrix_2d &pre) {
    map_2d odds_graph;
    pair<int, int> largest_edge;
    tie(odds_graph, largest_edge) = create_odds_graph(graph, dis);

    set<pair<int, int>> matching = perfect_matching(odds_graph, largest_edge);

    map_2d edge_copies;
    int weight_sum;
    tie(edge_copies, weight_sum) = create_multigraph(graph, matching, pre);

    vector<int> cp_tour = euler_tour(edge_copies);
    return { cp_tour, weight_sum };
}

pair<map_2d, pair<int, int>> create_odds_graph(adj_map &graph, matrix_2d &dis) {
    set<int> odds;
    for (int i = 0; i < graph.size(); i++) {
        if (graph[i].size() % 2 == 1) {
            odds.insert(i);
        }
    }

    map_2d odds_graph;
    int max_cost = 0;
    pair<int, int> largest_edge;

    for (auto it = odds.begin(); it != odds.end(); it++) {
        for (auto jt = it; jt != odds.end(); jt++) {
            if (*it != *jt) {
                odds_graph[*it][*jt] = odds_graph[*jt][*it] = dis[*it][*jt];

                if (dis[*it][*jt] > max_cost) {
                    largest_edge = { *it, *jt };
                    max_cost = dis[*it][*jt];
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
    map_2d edge_copies;
    int weight_sum = 0;

    for (int i = 0; i < graph.size(); i++) {
        for (auto it = graph[i].begin(); it != graph[i].end(); it++) {
            edge_copies[i][it->first] = 1;
            weight_sum += it->second;
        }
    }

    for (auto it = matching.begin(); it != matching.end(); it++) {
        int v1 = it->first;
        int v2 = pre[it->second][it->first];

        while (v2 != -1) {
            edge_copies[v1][v2] += 1;
            edge_copies[v2][v1] += 1;
            weight_sum += graph[v1][v2];
            v1 = v2;
            v2 = pre[it->second][v2];
        }
    }

    return { edge_copies, weight_sum };
}

vector<int> euler_tour(map_2d &graph) {
    vector<int> tour{ 0 };
    vector<int> subtour;

    int start = 0;
    while (!graph.empty()) {
        dfs_tour(start, graph, subtour);

        if (graph[start].empty()) {
            graph.erase(start);
        }

        for (int i = 0; i < tour.size(); i++) {
            if (tour[i] == start) {
                tour.insert(tour.begin() + i, subtour.begin(), subtour.end());
                break;
            }
        }

        for (auto it = graph.begin(); it != graph.end(); it++) {
            if (!it->second.empty()) {
                start = it->first; break;
            }
        }
        subtour.clear();
    }
    return tour;
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

void dfs_tour(int start, map_2d &graph, vector<int> &subtour) {
    if (!graph[start].empty()){
        int next = graph[start].begin()->first;
        cout << start << " to " << next << endl;
        remove_edge(graph, start, next);
        dfs_tour(next, graph, subtour);
    }
    subtour.push_back(start);
}