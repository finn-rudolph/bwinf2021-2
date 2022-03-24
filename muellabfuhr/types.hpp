#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <unordered_set>

#ifndef TYPES
#define TYPES

typedef std::vector<std::unordered_map<int, int>> adj_map;
typedef std::unordered_map<int, std::unordered_map<int, int>> map_2d;
typedef std::unordered_map<int, std::unordered_set<int>> unw_map_2d;

typedef std::vector<std::vector<int>> matrix_2d;

typedef std::array<int, 2> edge;

#endif
