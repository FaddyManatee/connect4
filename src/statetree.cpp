#include <queue>

#include "../include/statetree.hpp"

StateTree::StateTree(const Grid& g, int ply) {
    score = 0;
    this->ply = 0;
    state = g;

    for (int x = 0; x < 7; x++)
        child[x] = nullptr;

    expand(ply);
}

void StateTree::expand(int maxPly) {
    auto expand = this;
    std::queue<StateTree*> q;

    while (expand->ply < maxPly            ||
           expand->state.countHoriz() == 3 ||
           expand->state.countVert()  == 3 ||
           expand->state.countDiag()  == 3)
    {    
        for (int x = 0; x < 7; x++) {
            auto st = new StateTree(*expand);
            expand->child[x] = st;
            expand->child[x]->ply = expand->ply + 1;

            st->state.dropChequer(x);
            st->evaluate();
            st->state.nextPlayer();

            // Don't push state to queue if its a final game state.
            if (st->state.outcome() == 0)
                q.push(st);
        }

        expand = q.front();
        q.pop();
    }
}

void StateTree::evaluate() {
    // Sum of chequer chains for human (red) player.
    // Sum of chequer chains for computer (yellow) player.
    // Weight accordingly.
}

StateTree::~StateTree() {

}
