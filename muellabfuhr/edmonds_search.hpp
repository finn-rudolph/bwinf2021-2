#include "types.hpp"

typedef struct {
    public:
        int z, t_root, t_in, t_out, delta_t;
} blossom;

void edmonds_search(adj_map &graph);