#include "../include/minimax.hpp"

Minimax::Minimax(Grid g, int ply) {
    root = StateTree(g, ply);
}
