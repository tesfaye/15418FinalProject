#include <string>
#include <vector>
#include "Piece.h"

using namespace std;

class Pawn: public Piece {
public:
    Pawn(int player, int row, int col): Piece(player, row, col) {
        if (player) {
            this->piece = 'p';
            this->value = -10;
        }
        else {
            this->piece = 'P';
            this->value = 10;
        }
    };
    Pawn(int player, int row, int col, bool first): Piece(player, row, col) {
        if (player) {
            this->piece = 'p';
            this->value = -10;
        }
        else {
            this->piece = 'P';
            this->value = 10;
        }
        this->first = first;
    };

    // creates a deepcopy of the Pawn and returns it
    Pawn *deepcopy() {
        return new Pawn(this->player, this->row, this->col, this->first);
    };

    vector<pair<int, int> > find_valid_moves(Piece **board) {
        Piece *temp;
        bool first = this->first;
        int player = this->player;
        int row = this->row;
        int col = this->col;

        vector<pair<int, int> > coords;

        // white player
        if (!player) {
            // first move, pawn can go two steps
            if (first) {
                if (board[INDEX(row - 2, col)] == NULL) {
                    coords.push_back(make_pair(row - 2, col));
                }
            }

            // make sure pawn doesn't step out of bounds
            if (row > 0) {
                // move one step forward if no piece is there
                if (board[INDEX(row - 1, col)] == NULL) {
                    coords.push_back(make_pair(row - 1, col));
                }

                // eat piece left diagonal
                if (col > 0) {
                    temp = board[INDEX(row - 1, col - 1)];
                    if (temp != NULL && temp->player != player) {
                        coords.push_back(make_pair(row - 1, col - 1));
                    }
                }

                // eat piece right diagonal
                if (col < BOARD_DIM - 1) {
                    temp = board[INDEX(row - 1, col + 1)];
                    if (temp != NULL && temp->player != player) {
                        coords.push_back(make_pair(row - 1, col + 1));
                    }
                }
            }
        }

        // black player
        else {
            // first move, pawn can go two steps
            if (first) {
                if (board[INDEX(row + 2, col)] == NULL) {
                    coords.push_back(make_pair(row + 2, col));
                }
            }

            // make sure pawn doesn't step out of bounds
            if (row > 0) {
                // move one step forward if no piece is there
                if (board[INDEX(row + 1, col)] == NULL) {
                    coords.push_back(make_pair(row + 1, col));
                }

                // eat piece left diagonal
                if (col > 0) {
                    temp = board[INDEX(row + 1, col - 1)];
                    if (temp != NULL && temp->player != player) {
                        coords.push_back(make_pair(row + 1, col - 1));
                    }
                }

                // eat piece right diagonal
                if (col < BOARD_DIM - 1) {
                    temp = board[INDEX(row + 1, col + 1)];
                    if (temp != NULL && temp->player != player) {
                        coords.push_back(make_pair(row + 1, col + 1));
                    }
                }
            }
        }

        return coords;
    };
};
