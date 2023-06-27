#include "../include/minimax.hpp"

Minimax::Minimax(Grid g, int ply) {
    root = StateTree(g, ply);
}

void Minimax::prune() {

}

int Minimax::minimize() {
    // Select minimizing state, return its column number.
    prune();
    return 0;
}
