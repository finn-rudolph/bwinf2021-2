#include "utility.hpp"
using namespace std;

void print_graph(adj_map &graph) {
    for (int a = 0; a < graph.size(); a++) {
        cout << a << ": ";
        for (const auto &[b, w]: graph[a]) {
            cout << b << " -> " << w<< ";   ";
        }
    }
    cout << "\n" << endl;
}

void print_map_2d(map_2d &map) {
    for (const auto &[a, m]: map) {
        cout << a << ": ";
        for (const auto &[b, w]: m) {
            cout << b << " -> " << w << ";   ";
        }
        cout << "\n";
    }
    cout << "\n" << endl;
}

void print_vector(vector<int> &vector) {
    for (const auto &e: vector) {
        cout << e << " ";
    }
    cout << "\n" << endl;
}