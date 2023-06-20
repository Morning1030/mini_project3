#include <cstdlib>
// #include <iostream>
#include "../state/state.hpp"
#include "./submission.hpp"
#define infinity 20000005

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move AlphaBeta::get_move(State *state, int depth){
    // legal_actions is a vector of Move
    int heuristic = -20000000;
    Move move ={{0,0} , {0,0}};

    if(!state->legal_actions.size())
        state->get_legal_actions();

    for (auto i : state->legal_actions) {
        int tmp = get_alphabeta_value(state->next_state(i), depth-1, false, -infinity, infinity);
        if (tmp > heuristic) {
            heuristic = tmp;
            move = i;
        }
    }
    return move;
}
int AlphaBeta::get_alphabeta_value(State *state, int depth, bool maxingPlayer, int alpha, int beta) {
    if(!state->legal_actions.size())
        state->get_legal_actions();

     if (state->game_state == WIN && maxingPlayer) return infinity+2;
     else if (state->game_state == WIN && !maxingPlayer) return -infinity-2;

    if (depth == 0 || state->game_state == WIN) {
        return state->evaluate(maxingPlayer);
    }
    if (maxingPlayer) {
        int value = -infinity;
        for (auto i : state->legal_actions) {
            int eval = get_alphabeta_value(state->next_state(i), depth - 1, false, alpha, beta);
            value = std::max(value, eval);
            alpha = std::max(alpha, value);
            if (alpha >= beta) break;
        }
        return value;
    }
    else {
        int value = infinity;
        for (auto i : state->legal_actions) {
            int eval = get_alphabeta_value(state->next_state(i), depth - 1, true, alpha, beta);
            value = std::min(value, eval);
            beta = std::min(beta, value);
            if (alpha >= beta) break;
        }
        return value;
    }
}   