#include <unordered_set>
#include <unordered_map>
#include "blossom.hpp"

// max matching first

std::unordered_map<int, int> blossom(adj_map &G, bool min_max) {
    std::vector<bool> matched;

    // STEP 1
    std::unordered_map<int, int> M, N;
    adj_map H = G;

    // STEP 2
    step2:
    std::unordered_set<int> even, odd;
    std::unordered_set<int> V_F;
    unw_map_2d E_F;
    for (int v = 0; v < G.size(); v++) if (!matched[v]) { 
        even.insert(v);
        V_F.insert(v);
    }

    // STEP 4
    step4:
    int u = -1, v = -1;

    for (int u_: even) {
        if (u != -1) break;
        for (auto &[v_, w]: G[u]) {
            if (odd.find(v_) == odd.end()) {
                u = u_;
                v = v_;
                break;
            } 
        }
    }
    if (u == -1) return M;

    // STEP 5
    if (V_F.find(v) != V_F.end()) {
        odd.insert(v);
        V_F.insert(v);
        even.insert(M[v]);
        V_F.insert(M[v]);
        E_F[u].insert(v);
        E_F[v].insert(M[v]);
    }

    // STEP 6
    else if (even.find(v) != even.end()) {
        std::vector<int> path_F = dfs(V_F, E_F, u, v); 
        if (path_F[0] != -1) {
            // blossom found: blossom saved in path_F
            goto step4;

    // STEP 7
        } else {

            goto step2;
        }

    }

    // STEP 8
    return M;
}

// { -1 } indicates, that no path exists
std::vector<int> dfs(std::unordered_set<int> &V_F, unw_map_2d &E_F, int curr, int dest) {
    for (int next: E_F[curr]) {
        if (next == dest) return { dest };
        else { 
            std::vector<int> path = dfs(V_F, E_F, next, dest);
            if (path[0] == -1) return path;
            path.push_back(curr);
            return path;
        }
    }
    return { -1 };
}