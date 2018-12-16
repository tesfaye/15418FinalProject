#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <cilk/reducer_max.h>
#include <cilk/reducer_min.h>
#include <atomic>
#include "BoardState.h"

using namespace std;

// vector<BoardState *> moves;

Piece **create_board() {
	return new Piece*[BOARD_DIM * BOARD_DIM]();
}

void print_af(Piece **board) {
    for (int i = 0; i < BOARD_DIM; i++) {
        for (int j = 0; j < BOARD_DIM; j++) {
            if (board[INDEX(i, j)] != NULL) {
                Piece *piece = board[INDEX(i, j)];
                cout << "|" << piece->piece;
            }
            else cout << "| ";
        }
        cout << "|\n";
    }
}

BoardState::BoardState() {
    this->curr_player = 0;
    Piece **board = create_board();
    this->players[0] = new Player(0, board);
    this->players[1] = new Player(1, board);
    this->board = board;
}

BoardState::BoardState(int curr, Player *white, Player *black, Piece ** board) {
    this->curr_player = curr;
    this->players[0] = white;
    this->players[1] = black;
    this->board = board;
}

BoardState::~BoardState() {
    delete(this->players[0]);
    delete(this->players[1]);
    delete(this->board);
}

BoardState *BoardState::deepcopy() {
    // initializes new board
    Piece **board = create_board();

    // deepcopy the players while putting new pieces on new board
    Player *white = (this->players[0])->deepcopy(board);
    Player *black = (this->players[1])->deepcopy(board);

    return (new BoardState(this->curr_player, white, black, board));
}

bool BoardState::check() {
    Piece **board = this->board;
    int other_player_index = !(this->curr_player);
    Player *player = this->players[this->curr_player];
    Player *other_player = this->players[other_player_index];

    // allocate the check board
    bool check_board[BOARD_DIM * BOARD_DIM];
    for (int i = 0; i < BOARD_DIM * BOARD_DIM; i++) {
        check_board[i] = false;
    }

    for (int i = 0; i < (other_player->pieces).size(); i++) {
        Piece *piece = other_player->pieces[i];
        // cout << piece->piece << " " << piece->row << " " << piece->col << "\n";
        piece->put_on_check_board(board, check_board);
    }

    // an opponent piece can eat the king
    bool in_check = check_board[INDEX(player->king_row, player->king_col)];

    // free the check board

    return in_check;
}

void BoardState::move_piece(int r1, int c1, int r2, int c2) {
    Piece *piece = this->board[INDEX(r1, c1)];
    Piece *eaten = this->board[INDEX(r2, c2)];

    // other player info
    int o_p = !(this->curr_player);
    Player *other_player = this->players[o_p];

    if (eaten != NULL) {
        if (eaten->player == piece->player) return;
        int index;
        for (int i = 0; i < (other_player->pieces).size(); i++) {
            if (eaten == other_player->pieces[i]) {
                index = i;
                break;
            }
        }

        // remove it from the pieces vector of other player
        other_player->pieces.erase(other_player->pieces.begin() + index);
    }

    piece->move_on_board(this->board, r2, c2);

    this->curr_player = !(this->curr_player);
}

BoardState *BoardState::make_moves(int row, int col, int i) {
    BoardState *new_board_state = this->deepcopy();
    Piece **new_board = new_board_state->board;

    // find the exact same piece in the deepcopy
    Player *new_player = new_board_state->players[new_board_state->curr_player];
    Piece *new_piece = new_player->pieces[i];

    // other player info
    int o_p = !(new_board_state->curr_player);
    Player *other_player = new_board_state->players[o_p];

    Piece *eaten = new_board[INDEX(row, col)];
    if (eaten != NULL) {
        int index;
        for (int i = 0; i < (other_player->pieces).size(); i++) {
            if (eaten == other_player->pieces[i]) {
                index = i;
                break;
            }
        }

        // remove it from the pieces vector of other player
        other_player->pieces.erase(other_player->pieces.begin() + index);
    }

    new_piece->move_on_board(new_board, row, col);

    // update king location if necessary
    if (tolower(new_piece->piece) == 'k') {
        new_player->king_row = row;
        new_player->king_col = col;
    }

    if (!(new_board_state->check())) {
        // cout << "not check\n";
        // player made move, other player's turn
        new_board_state->curr_player = !(this->curr_player);
        return new_board_state;
    }
    else {
        // cout << "check\n";
        delete new_board_state;
        return NULL;
    }
}

BoardState *BoardState::castle(int king_index, int rook_index) {
    BoardState *new_board_state = this->deepcopy();
    Piece **new_board = new_board_state->board;
    Player *new_player = new_board_state->players[new_board_state->curr_player];

    Piece *king = new_player->pieces[king_index];
    Piece *rook = new_player->pieces[rook_index];

    if (rook->col < king->col) {
        king->move_on_board(new_board, king->row, 2);
        rook->move_on_board(new_board, rook->row, 3);

        // update king_row and king_col
        new_player->king_row = king->row;
        new_player->king_col = 2;
    }

    else {
        king->move_on_board(new_board, king->row, 6);
        rook->move_on_board(new_board, rook->row, 5);

        // update king_row and king_col
        new_player->king_row = king->row;
        new_player->king_col = 6;
    }

    if (!(new_board_state->check())) {
        // cout << "not check\n";
        // player made move, other player's turn
        new_board_state->curr_player = !(this->curr_player);
        return new_board_state;
    }
    else {
        // cout << "check\n";
        delete new_board_state;
        return NULL;
    }
}

vector<BoardState *> BoardState::find_legal_moves() {
    vector<BoardState *> moves;
    Piece *king, *rook1, *rook2;
    Piece **board = this->board;
    Player *player = this->players[this->curr_player];
    bool no_pieces;
    int king_index, rook1_index, rook2_index;
    int row = (this->curr_player) ? 0 : 7;
    int king_col = 4;
    int rook1_col = 0;
    int rook2_col = 7;

    // find all the pieces this player currently still has
    vector<Piece *> player_pieces = player->pieces;

    // castle check
    /*king = board[INDEX(row, king_col)];

    if (king != NULL && king->first) {
        for (int i = 0; i < player_pieces.size(); i++) {
            if (king == player_pieces[i]) {
                king_index = i;
                break;
            }
        }

        rook1 = board[INDEX(row, rook1_col)];
        rook2 = board[INDEX(row, rook2_col)];

        for (int i = 0; i < player_pieces.size(); i++) {
            if (rook1 == player_pieces[i]) rook1_index = i;
            else if (rook2 == player_pieces[i]) rook2_index = i;
        }

        if (rook1 != NULL && rook1->first) {
            for (int i = 0; i < player_pieces.size(); i++) {
                if (rook1 == player_pieces[i]) {
                    rook1_index = i;
                    break;
                }
            }

            // make sure there are no pieces in between the king and rook
            no_pieces = true;
            for (int i = rook1_col + 1; i <= king_col - 1; i++) {
                if (board[INDEX(row, i)] != NULL) {
                    no_pieces = false;
                    break;
                }
            }

            if (no_pieces) {
                // create deepcopy of board to put into moves vector
                BoardState *new_board = this->castle(king_index, rook1_index);
                // add this to possible moves vector if the move doesn't
                // result in a check
                if (new_board != NULL) moves.push_back(new_board);
            }
        }

        if (rook2 != NULL && rook2->first) {
            for (int i = 0; i < player_pieces.size(); i++) {
                if (rook2 == player_pieces[i]) {
                    rook2_index = i;
                    break;
                }
            }

            // make sure there are no pieces in between the king and rook
            no_pieces = true;
            for (int i = king_col + 1; i < rook2_col - 1; i++) {
                if (board[INDEX(row, i)] != NULL) {
                    no_pieces = false;
                    break;
                }
            }

            if (no_pieces) {
                // create deepcopy of board to put into moves vector
                BoardState *new_board = this->castle(king_index, rook1_index);

                // add this to possible moves vector if the move doesn't
                // result in a check
                if (new_board != NULL) moves.push_back(new_board);
            }
        }
    }*/


    // for each piece, find all possible moves
    for (int i = 0; i < player_pieces.size(); i++) {
        Piece *piece = player_pieces[i];
        vector<pair<int, int> > piece_moves = piece->find_valid_moves(board);

        // for each move, create a deepcopy board state with the only
        // change being the moved piece
        for (int j = 0; j < piece_moves.size(); j++) {
            // coordinate points
            pair<int, int> coord = piece_moves[j];

            // cout << piece->piece << " " << coord.first << " " << coord.second << "\n";

            // create deepcopy of board to put into moves vector
            BoardState *new_board = this->make_moves(coord.first, coord.second, i);

            // add this to possible moves vector if the move doesn't
            // result in a check
            if (new_board != NULL) moves.push_back(new_board);
        }
    }

    /*if (moves.size() == 0) {
        print_af(board);
        cout << "checkmate\n";
    }*/

    return moves;
}

int BoardState::eval() {
    vector<Piece *> white_pieces = (this->players[0])->pieces;
    vector<Piece *> black_pieces = (this->players[1])->pieces;

    int value = 0;
    for (int i = 0; i < white_pieces.size(); i++) {
        value += white_pieces[i]->value;
    }
    for (int i = 0; i < black_pieces.size(); i++) {
        value += black_pieces[i]->value;
    }

    if (this->curr_player) {
        if (this->check()) value += 900;
    }

    else {
        if (this->check()) value -= 900;
    }

    return value;
}

int BoardState::minimax(int depth, int alpha, int beta) {
    if (depth == 0) return this->eval();

    // white player tries to maximize move
    if (!(this->curr_player)) {
        bool term;
        int max_eval = INT_MIN;
        vector<BoardState *> all_moves = this->find_legal_moves();


        //std::atomic_bool done(false);
        //done.store(false);
        //bool *done = (bool*) calloc(1, sizeof(bool));
        int *values = (int*) calloc(all_moves.size(), sizeof(int));

        cilk_for (int i =0; i < all_moves.size(); i++) {
            BoardState *move = all_moves[i];
            int eval = move->minimax(depth - 1, alpha, beta);
            values[i] = eval;
        }

        cilk::reducer< cilk::op_max<int> > rm;
        cilk_for (int i = 0; i < all_moves.size(); i++) {
            rm->calc_max(values[i]);
        }
        max_eval = MAX(max_eval, rm.get_value());
        free(values);

        return max_eval;
    }

    // black player tries to minimize move
    else {
        bool term;
        int min_eval = INT_MAX;
        vector<BoardState *> all_moves = this->find_legal_moves();

        //std::atomic_bool done(false);
        //done.store(false);
        //bool *done = (bool*) calloc(1, sizeof(bool));
        int *values = (int*) calloc(all_moves.size(), sizeof(int));
        cilk_for (int i =0; i < all_moves.size(); i++) {
            BoardState *move = all_moves[i];
            int eval = move->minimax(depth - 1, alpha, beta);
            values[i] = eval;
        }


        cilk::reducer< cilk::op_min<int> > rm;
        cilk_for (int i = 0; i < all_moves.size(); i++) {
            rm->calc_min(values[i]);
        }
        min_eval = MIN(min_eval, rm.get_value());
        free(values);

        return min_eval;
    }
}

int BoardState::negamax(int depth) {
    if (depth == 0) return this->eval();

    int value = INT_MIN;
    vector<BoardState *> all_moves = this->find_legal_moves();

    int *values = (int*) calloc(all_moves.size(), sizeof(int));

    cilk_for (int i = 0; i < all_moves.size(); i++) {
        values[i] = -1 * (all_moves[i]->negamax(depth - 1));
    }

    cilk::reducer< cilk::op_max<int> > rm;
    cilk_for (int i = 0; i < all_moves.size(); i++) {
        rm->calc_max(values[i]);
    }
    value = MAX(value, rm.get_value());
    free(values);

    return value;
}

BoardState *BoardState::mm(int depth, int alpha, int beta, BoardState **stuff) {
    if (depth == 0) return this;

    // white player tries to maximize move
    if (!(this->curr_player)) {
        int max_eval = INT_MIN;
        BoardState *max_move;
        vector<BoardState *> all_moves = this->find_legal_moves();

        for (int i = 0; i < all_moves.size(); i++) {
            BoardState *move = all_moves[i];
            int eval = move->minimax(depth - 1, alpha, beta);
            if (eval >= max_eval) {
                max_eval = eval;
                max_move = move->mm(depth - 1, alpha, beta, stuff);
                stuff[depth - 1] = move;
            }
            alpha = MAX(alpha, eval);
            if (beta <= alpha) break;
        }

        return max_move;
    }

    // black player tries to minimize move
    else {
        int min_eval = INT_MAX;
        BoardState *min_move;
        vector<BoardState *> all_moves = this->find_legal_moves();

        for (int i = 0; i < all_moves.size(); i++) {
            BoardState *move = all_moves[i];
            int eval = move->minimax(depth - 1, alpha, beta);
            if (eval <= min_eval) {
                min_eval = eval;
                min_move = move->mm(depth - 1, alpha, beta, stuff);
                stuff[depth - 1] = move;
            }
            beta = MIN(beta, eval);
            if (beta <= alpha) break;
        }

        return min_move;
    }
}
