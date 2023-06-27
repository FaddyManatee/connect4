#include "../include/statetree.hpp"

StateTree::StateTree(const Grid& g, int ply) {
    value = 0;
    this->ply = 0;
    state = g;
    std::queue<StateTree*> q;

    for (int x = 0; x < 7; x++)
        child[x] = nullptr;

    expand(q, ply);
}

void StateTree::expand(std::queue<StateTree*>& q, int maxPly) {
    auto expand = this;

    while (expand->ply < maxPly) {    
        for (int x = 0; x < 7; x++) {
            auto st = new StateTree(*expand);
            child[x] = st;
            child[x]->ply = expand->ply + 1;

            st->state.dropChequer(x + 1);
            // TODO: Don't push state to queue if its a final game state.
            if (st->state.outcome() == 0)
                q.push(st);
        }

        expand = q.front();
        q.pop();
    }
}

StateTree::~StateTree() {

}
