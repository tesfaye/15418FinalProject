#include <string>
#include <vector>
#include "Piece.h"

using namespace std;

class Knight: public Piece {
public:
    Knight(int player, int row, int col): Piece(player, row, col) {
        if (player) {
            this->piece = 'n';
            this->value = -30;
        }
        else {
            this->piece = 'N';
            this->value = 30;
        }
    };

    // creates a deepcopy of the Knight and returns it
    Knight *deepcopy() {
        return new Knight(this->player, this->row, this->col);
    };

    vector<pair<int, int> > find_valid_moves(Piece **board) {
        Piece *temp;
        int player = this->player;
        int row = this->row;
        int col = this->col;

        vector<pair<int, int> > coords;

        // eight possible places knights can go to
        if (row + 2 < BOARD_DIM && col + 1 < BOARD_DIM) {
            temp = board[INDEX(row + 2, col + 1)];
            if (temp == NULL || temp->player != player)
                coords.push_back(make_pair(row + 2, col + 1));
        }

        if (row + 2 < BOARD_DIM && col - 1 >= 0) {
            temp = board[INDEX(row + 2, col - 1)];
            if (temp == NULL || temp->player != player)
                coords.push_back(make_pair(row + 2, col - 1));
        }

        if (row - 2 >= 0 && col + 1 < BOARD_DIM) {
            temp = board[INDEX(row - 2, col + 1)];
            if (temp == NULL || temp->player != player)
                coords.push_back(make_pair(row - 2, col + 1));
        }

        if (row - 2 >= 0 && col - 1 >= 0) {
            temp = board[INDEX(row - 2, col - 1)];
            if (temp == NULL || temp->player != player)
                coords.push_back(make_pair(row - 2, col - 1));
        }

        if (row + 1 < BOARD_DIM && col + 2 < BOARD_DIM) {
            temp = board[INDEX(row + 1, col + 2)];
            if (temp == NULL || temp->player != player)
                coords.push_back(make_pair(row + 1, col + 2));
        }

        if (row + 1 < BOARD_DIM && col - 2 >= 0) {
            temp = board[INDEX(row + 1, col - 2)];
            if (temp == NULL || temp->player != player)
                coords.push_back(make_pair(row + 1, col - 2));
        }

        if (row - 1 >= 0 && col + 2 < BOARD_DIM) {
            temp = board[INDEX(row - 1, col + 2)];
            if (temp == NULL || temp->player != player)
                coords.push_back(make_pair(row - 1, col + 2));
        }

        if (row - 1 >= 0 && col - 2 >= 0) {
            temp = board[INDEX(row - 1, col - 2)];
            if (temp == NULL || temp->player != player)
                coords.push_back(make_pair(row - 1, col - 2));
        }

        return coords;
    };
};