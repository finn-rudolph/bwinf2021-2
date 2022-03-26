#include <set>
#include <unordered_map>
#include "types.hpp"

void exchange(matrix_2d &dis, std::vector<edge> &mat, int i, int j, bool swap_partner);

std::vector<edge> two_opt(matrix_2d &dis, std::vector<edge> mat = { });

void radix_sort_msd(int* arr, int length, int h);

void assign_cluster(
    matrix_2d &dis,
    std::vector<std::vector<int>> &clusters, 
    int u,
    int v,
    int &open,
    int &odd,
    int threshold,
    std::unordered_map<int, int> &assigned_to
);

std::vector<edge> cluster(matrix_2d &dis, std::vector<int> odds, float alpha);
