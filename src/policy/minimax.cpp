#include <cstdlib>
// #include <iostream>
#include "../state/state.hpp"
#include "./minimax.hpp"
#define infinity 2147483640

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
    // legal_actions is a vector of Move
    int heuristic = -infinity;
    Move move ={{0,0} , {0,0}};

    if(!state->legal_actions.size())
        state->get_legal_actions();

    for (auto i : state->legal_actions) {
        int tmp = get_minimax_value(state->next_state(i), depth-1, false);
        if (tmp > heuristic) {
            heuristic = tmp;
            move = i;
        }
    }
    return move;
}
int Minimax::get_minimax_value(State *state, int depth, bool maxingPlayer) {
    if(!state->legal_actions.size())
        state->get_legal_actions();
    if (state->game_state == WIN && maxingPlayer) return infinity - 1;
    else if (state->game_state == WIN && !maxingPlayer) return -infinity - 1;
    if (depth == 0 || !state->legal_actions.size()) {
        return state->evaluate(maxingPlayer);
    }
    if (maxingPlayer) {

        int maxEval = -infinity;
        for (auto i : state->legal_actions) {
            int eval = Minimax::get_minimax_value(state->next_state(i), depth - 1, false);
            maxEval = std::max(maxEval, eval);
        }
        return maxEval;
    }
    else {
        int minEval = infinity;
        for (auto i : state->legal_actions) {
            int eval = Minimax::get_minimax_value(state->next_state(i), depth - 1, true);
            minEval = std::min(minEval, eval);
        }
        return minEval;
    }
}