#include <vector>
#include "types.hpp"

std::pair<std::vector<int>, int> postman(adj_map &graph, matrix_2d &dis, matrix_2d &pre, float alpha);

std::vector<int> eulerian_circuit(map_2d &graph);