#include <algorithm>
#include <queue>

#include <iostream>
#include <unistd.h>

#include "../include/statetree.hpp"

StateTree::StateTree(const Grid& g, int ply) {
    this->ply = 0;
    score = {0, 0, 0};
    state = g;
    isLeaf = false;

    for (int x = 0; x < 7; x++)
        child[x] = nullptr;

    expand(ply);
}

void StateTree::expand(int maxPly) {
    auto expand = this;
    std::queue<StateTree*> q;

    while (expand->state.countHoriz() == 3 ||
           expand->state.countVert()  == 3 ||
           expand->state.countDiag()  == 3 ||
           expand->ply < maxPly)
    {     
        for (int x = 0; x < 7; x++) {
            auto st = new StateTree(*expand);
            expand->child[x] = st;
            st->ply = expand->ply + 1;

            st->state.dropChequer(x);
            st->calcScore();
            st->state.nextPlayer();

            // Don't push state to queue if it is a leaf state.
            if (st->state.outcome() != 0 || st->ply == maxPly)
                st->isLeaf = true;
            else
                q.push(st);
        }

        expand = q.front();
        if (expand == nullptr)
            break;
        q.pop();
    }

    evaluate();
}

void StateTree::calcScore() {
    /**
     * IDEAS:
     * Sum of chequer chains for human (red) player.
     * Sum of chequer chains for computer (yellow).
     * Weight accordingly.
     * 
     * Density of chequers for human (red) player.
     * Density of chequers for computer (yellow). 
     */
    score.local = 0;
}

void StateTree::evaluate() {
    //usleep(950000);
    if (isLeaf) {
        score.minimax = score.local;
        //std::cout << "leaf\n";
        return;
    }

    for (int x = 0; x < 7; x++) {
        if (child[x] == nullptr) {
            //std::cout << "null";
            continue;
        }

        //child[x]->state.drawGrid();
        //std::cout << "\n";
        child[x]->evaluate();
    }

    if (ply % 2 == 1) {
        auto min = std::min_element(std::begin(child), std::end(child),
        [](StateTree* a, StateTree* b) {
            return a->score.local < b->score.local;
        });
        score.minimax = (*min)->score.local;
        score.col = std::distance(std::begin(child), min);
    }
    else {
        auto max = std::max_element(std::begin(child), std::end(child),
        [](StateTree* a, StateTree* b) {
            return a->score.local < b->score.local;
        });
        score.minimax = (*max)->score.local;
        score.col = std::distance(std::begin(child), max);  
    }
}

StateTree::~StateTree() {

}
