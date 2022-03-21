#include <vector>
#include <map>

#ifndef TYPES
#define TYPES

typedef std::vector<std::map<int, int>> adj_map;

typedef std::map<int, std::map<int, int>> map_2d;

typedef std::vector<std::vector<int>> matrix_2d;

typedef struct {
    int a;
    int b;
} edge;

#endif
