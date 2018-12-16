#include <string>
#include <vector>
#include "Piece.h"

using namespace std;

class Rook: public Piece {
public:
    Rook(int player, int row, int col): Piece(player, row, col) {
        if (player) {
            this->piece = 'r';
            this->value = -50;
        }
        else {
            this->piece = 'R';
            this->value = 50;
        }
    };
    Rook(int player, int row, int col, bool first): Piece(player, row, col) {
        if (player) {
            this->piece = 'r';
            this->value = -50;
        }
        else {
            this->piece = 'R';
            this->value = 50;
        }
        this->first = first;
    };

    // creates a deepcopy of the Rook and returns it
    Rook *deepcopy() {
        return new Rook(this->player, this->row, this->col, this->first);
    };

    vector<pair<int, int> > find_valid_moves(Piece **board) {
        Piece *temp;
        int row, col;
        int player = this->player;

        vector<pair<int, int> > coords;

        // up
        row = this->row;
        col = this->col;
        while (row > 0) {
            row--;
            temp = board[INDEX(row, col)];

            if (temp != NULL) {
                if (temp->player != player) coords.push_back(make_pair(row, col));
                break;
            }

            coords.push_back(make_pair(row, col));
        }

        // down
        row = this->row;
        col = this->col;
        while (row < BOARD_DIM - 1) {
            row++;
            temp = board[INDEX(row, col)];

            if (temp != NULL) {
                if (temp->player != player) coords.push_back(make_pair(row, col));
                break;
            }

            coords.push_back(make_pair(row, col));
        }

        // left
        row = this->row;
        col = this->col;
        while (col > 0) {
            col--;
            temp = board[INDEX(row, col)];

            if (temp != NULL) {
                if (temp->player != player) coords.push_back(make_pair(row, col));
                break;
            }

            coords.push_back(make_pair(row, col));
        }

        // right
        row = this->row;
        col = this->col;
        while (col < BOARD_DIM - 1) {
            col++;
            temp = board[INDEX(row, col)];

            if (temp != NULL) {
                if (temp->player != player) coords.push_back(make_pair(row, col));
                break;
            }

            coords.push_back(make_pair(row, col));
        }

        return coords;
    };
};
