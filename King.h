#include <string>
#include <vector>
#include "Piece.h"

using namespace std;

class King: public Piece {
public:
    King(int player, int row, int col): Piece(player, row, col) {
        if (player) {
            this->piece = 'k';
            this->value = -90;
        }
        else {
            this->piece = 'K';
            this->value = 90;
        }
    };
    King(int player, int row, int col, bool first): Piece(player, row, col) {
        if (player) {
            this->piece = 'k';
            this->value = -90;
        }
        else {
            this->piece = 'K';
            this->value = 90;
        }
        this->first = first;
    };

    // creates a deepcopy of the King and returns it
    King *deepcopy() {
        return new King(this->player, this->row, this->col);
    };

    vector<pair<int, int> > find_valid_moves(Piece **board) {
        Piece *temp;
        int player = this->player;
        int row = this->row;
        int col = this->col;

        vector<pair<int, int> > coords;

        // eight possible places king can go to
        if (col + 1 < BOARD_DIM) {
            temp = board[INDEX(row, col + 1)];
            if (temp == NULL || temp->player != player)
                coords.push_back(make_pair(row, col + 1));
        }

        if (col - 1 >= 0) {
            temp = board[INDEX(row, col - 1)];
            if (temp == NULL || temp->player != player)
                coords.push_back(make_pair(row, col - 1));
        }

        if (row + 1 < BOARD_DIM) {
            temp = board[INDEX(row + 1, col)];
            if (temp == NULL || temp->player != player)
                coords.push_back(make_pair(row + 1, col));
        }

        if (row - 1 >= 0) {
            temp = board[INDEX(row - 1, col)];
            if (temp == NULL || temp->player != player)
                coords.push_back(make_pair(row - 1, col));
        }

        if (row + 1 < BOARD_DIM && col + 1 < BOARD_DIM) {
            temp = board[INDEX(row + 1, col + 1)];
            if (temp == NULL || temp->player != player)
                coords.push_back(make_pair(row + 1, col + 1));
        }

        if (row + 1 < BOARD_DIM && col - 1 >= 0) {
            temp = board[INDEX(row + 1, col - 1)];
            if (temp == NULL || temp->player != player)
                coords.push_back(make_pair(row + 1, col - 1));
        }

        if (row - 1 >= 0 && col + 1 < BOARD_DIM) {
            temp = board[INDEX(row - 1, col + 1)];
            if (temp == NULL || temp->player != player)
                coords.push_back(make_pair(row - 1, col + 1));
        }

        if (row - 1 >= 0 && col - 1 >= 0) {
            temp = board[INDEX(row - 1, col - 1)];
            if (temp == NULL || temp->player != player)
                coords.push_back(make_pair(row - 1, col - 1));
        }

        return coords;
    };
};
