#include <string>
#include <vector>
#include "Piece.h"

using namespace std;

class Queen: public Piece {
public:
    Queen(int player, int row, int col): Piece(player, row, col) {
        if (player) {
            this->piece = 'q';
            this->value = -900;
        }
        else {
            this->piece = 'Q';
            this->value = 900;
        }
    };

    // creates a deepcopy of the Queen and returns it
    Queen *deepcopy() {
        return new Queen(this->player, this->row, this->col);
    };

    vector<pair<int, int> > find_valid_moves(Piece **board) {
        Piece *temp;
        int row, col;
        int player = this->player;

        vector<pair<int, int> > coords;

        // upwards left
        row = this->row;
        col = this->col;
        while (row > 0 && col > 0) {
            row--;
            col--;
            temp = board[INDEX(row, col)];

            if (temp != NULL) {
                if (temp->player != player) coords.push_back(make_pair(row, col));
                break;
            }

            coords.push_back(make_pair(row, col));
        }

        // upwards right
        row = this->row;
        col = this->col;
        while (row > 0 && col < BOARD_DIM - 1) {
            row--;
            col++;
            temp = board[INDEX(row, col)];

            if (temp != NULL) {
                if (temp->player != player) coords.push_back(make_pair(row, col));
                break;
            }

            coords.push_back(make_pair(row, col));
        }

        // downwards left
        row = this->row;
        col = this->col;
        while (row < BOARD_DIM - 1 && col > 0) {
            row++;
            col--;
            temp = board[INDEX(row, col)];

            if (temp != NULL) {
                if (temp->player != player) coords.push_back(make_pair(row, col));
                break;
            }

            coords.push_back(make_pair(row, col));
        }

        // downwards right
        row = this->row;
        col = this->col;
        while (row < BOARD_DIM - 1 && col < BOARD_DIM - 1) {
            row++;
            col++;
            temp = board[INDEX(row, col)];

            if (temp != NULL) {
                if (temp->player != player) coords.push_back(make_pair(row, col));
                break;
            }

            coords.push_back(make_pair(row, col));
        }

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
