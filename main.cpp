#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <stdlib.h>
#include <cilk/cilk_api.h>
#include "BoardState.h"

#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

using namespace std;

void print_board(Piece **board) {
    for (int i = 0; i < BOARD_DIM; i++) {
        cout << i << " ";
        for (int j = 0; j < BOARD_DIM; j++) {
            if (board[INDEX(i, j)] != NULL) {
                Piece *piece = board[INDEX(i, j)];
                cout << "|" << piece->piece;
            }
            else cout << "| ";
        }
        cout << "|\n";
    }
    cout << "   0 1 2 3 4 5 6 7\n";
}

int main(int argc, const char* argv[]) {
    if(argc != 5) {
        printf("Usage ./chess -d <depth> -t <cilk workers>\n");
        return 1;
    }
    using namespace std::chrono;
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::duration<double> dsec;

    int workers = atoi(argv[4]);
    if (0!= __cilkrts_set_param("nworkers",argv[4]))
    {
        printf("Failed to set worker count\n");
        return 1;
    }
    int depth = atoi(argv[2]);
    printf("depth : %d\n", depth);
    printf("workers : %d\n\n", workers);

    BoardState *state = new BoardState();

    /*print_board(state->board);

    cout << "\n\n\n";

    vector<BoardState *> moves = state->find_legal_moves();

    for (int i = 0; i < moves.size(); i++) {
        print_board(moves[i]->board);
    }*/


    auto compute_start = Clock::now();
    // cout << "minimax " << state->minimax(depth, INT_MIN, INT_MAX) << "\n";
    cout << "negamax " << state->negamax(depth, INT_MIN, INT_MAX) << "\n";
    auto compute_time = duration_cast<dsec>(Clock::now() - compute_start).count();
    printf("Computation Time: %lf.\n", compute_time);
    /*BoardState **stuff = (BoardState **)malloc(depth * sizeof(BoardState*));
    print_board(state->ab(depth, INT_MIN, INT_MAX, stuff)->board);

    cout << "\n\n\n\n";

    for (int i = depth - 1; i >= 0; i--) {
        print_board(stuff[i]->board);
    }*/

    /*while (true) {
        int r1, c1, r2, c2;
        char temp;
        // string temp1, temp2, temp3;

        cout << "move> ";
        cin >> r1 >> c1 >> r2 >> c2;

        cout << "\n\n\n";

        state->move_piece(r1, c1, r2, c2);

        print_board(state->board);
        cout << "\n\n\n";

        // other player makes a move
        BoardState **stuff = (BoardState **)malloc(5 * sizeof(BoardState *));
        state->ab(5, INT_MIN, INT_MAX, stuff);

        BoardState *freed = state;
        state = stuff[4];
        free(freed);
        free(stuff);

        print_board(state->board);
        // state->curr_player = !(state->curr_player);
        cout << "\n\n\n";
    }*/

    delete state;

    return 0;
}
