#include "edmonds_search.hpp"
#include <vector>
#include <climits>
#include <unordered_map>

class union_find {
    private:
        adj_set tree;
        std::vector<blossom*> vtb;
        std::unordered_map<blossom*, std::vector<int>> btv;
    
    public:
        union_find(int n) {
            for (int i = 0; i < n; i++) vtb.push_back(0);
        }

        void add_edge(int u, int v) {
            tree[u].insert(v);
            tree[v].insert(u);
        }

        blossom* unite(int u, int v) {
            if (tree[u].find(v) != tree[u].end()) {
                for (int vertex: btv[vtb[v]]) vtb[vertex] = vtb[u];
                return vtb[u];
            }
        }

        blossom* find(int u) {
            return vtb[u];
        }
};

class split_findmin {
    private:
        std::vector<std::vector<int>> L;
        std::vector<int> belonging;
        std::vector<int> key;

    public:
        void init(std::vector<int> &vertices) {
            L.push_back(vertices);
            for (int i = 0; i < vertices.size(); i++) {
                key.push_back(INT_MAX);
                belonging.push_back(0);
            }
        }

        std::vector<int> &list(int u) {
            return L[belonging[u]];
        }

        void split(int u) {
            std::vector<int> prev_list = list(u);
            auto u_it = prev_list.begin();
            while (*u_it != u) u_it++;

            std::vector<int> second(++u_it, prev_list.end());
            L.push_back(second);
            prev_list.resize(u_it - prev_list.begin());
        }

        void decrease_key(int u, int x) {
            if (x < key[u]) key[u] = x;
        }

        int find_min(std::vector<int> &list) {
            int min = key[list[0]];
            for (int v: list) if (key[v] < min) min = key[v];
            return min;
        }
};

void edmonds_search(adj_map &graph) {
    std::vector<int> y;
    int t;
}