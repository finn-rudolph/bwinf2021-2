#include <set>
#include <unordered_map>
#include "types.hpp"

void exchange(map_2d &graph, std::vector<edge> &mat, int i, int j, bool swap_partner);

std::vector<edge> two_opt(map_2d &graph, std::vector<edge> mat = { });

void radix_sort_msd(int* arr, int length, int h);

void assign_cluster(
    map_2d &graph,
    std::vector<std::vector<int>> &clusters, 
    int u,
    int v,
    int &open,
    int &odd,
    int threshold,
    std::unordered_map<int, int> &assigned_to
);

std::vector<edge> cluster(map_2d &graph, float alpha, float beta);
