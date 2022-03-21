#include <set>
#include "types.hpp"

std::vector<edge> perfect_matching(map_2d &graph, edge &largest_edge);

float circle_intersection(float r1, float r2, float distance);

std::vector<edge> two_opt(map_2d &graph, std::vector<edge> mat = { });
