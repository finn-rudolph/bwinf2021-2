#include "utility.hpp"

void print_graph(adj_map &graph) {
    for (int i = 0; i < graph.size(); i++) {
        cout << i << ": \n";
        for (auto it = graph[i].begin(); it != graph[i].end(); it++) {
            cout << it->first<< " " << it->second << endl;
        }
        cout << "\n" << endl;
    }
}

void print_map_2d(map_2d &map) {
    for (auto it = map.begin(); it != map.end(); it++) {
        cout << it->first << ": \n";
        for (auto jt = it->second.begin(); jt != it->second.end(); jt++) {
            cout << jt->first<< " " << jt->second << endl;
        }
        cout << "\n" << endl;
    }
}

void print_vector(vector<int> &vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec.at(i) << " ";
    }
    cout << "\n" << endl;
}