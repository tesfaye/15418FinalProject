#include <iostream>
#include <string>
#include "Piece.h"

using namespace std;

Piece::Piece(int player, int row, int col) {
	this->player = player;
	this->row = row;
	this->col = col;
    this->piece = ' ';
    this->first = true;
    this->value = 0;
}

Piece::~Piece() {}

// prints out all info for debugging purposes
void Piece::to_string() {
    cout << this->player << " ";;
    cout << this->row << " ";;
    cout << this->col << " ";;
    cout << this->piece << "\n";;
}

// put piece on board
void Piece::put_on_board(Piece **board) {
    board[INDEX(this->row, this->col)] = this;
}

// move piece from one place to another place on board
void Piece::move_on_board(Piece **board, int r1, int c1) {
    Piece *piece2 = board[INDEX(r1, c1)];
    if (piece2 != NULL && piece2->player == this->player) return;
    if (piece2 != NULL) {
        delete piece2;
    }
    board[INDEX(this->row, this->col)] = NULL;
    board[INDEX(r1, c1)] = this;
    this->row = r1;
    this->col = c1;
    if (this->first) this->first = false;
}

void Piece::put_on_check_board(Piece **board, bool *check_board) {
    vector<pair<int, int> >coords = this->find_valid_moves(board);

    for (int i = 0; i < coords.size(); i++) {
        int r = coords[i].first;
        int c = coords[i].second;

        // fill out the check board
        check_board[INDEX(r, c)] = true;
    }
}

// finds all possible coordinates this piece can move to, given board
/*vector<pair<int, int> > Piece::find_valid_moves(Piece **board) {
    vector<pair<int, int> > coords;

    switch (tolower(this->piece)) {
        // pawn
        case 'p':
            coords = find_pawn_moves(this, board);
            break;

        // knight
        case 'n':
            coords = find_knight_moves(this, board);
            break;

        // bishop
        case 'b':
            coords = find_bishop_moves(this, board);
            break;

        // rook
        case 'r':
            coords = find_rook_moves(this, board);
            break;

        // queen
        case 'q':
            coords = find_queen_moves(this, board);
            break;

        // king
        case 'k':
            coords = find_king_moves(this, board);
            break;

        // NULL piece
        default:
            break;
    }

    for (int i = 0; i < coords.size(); i++) {
        cout << coords[i].first << " " << coords[i].second << " \n";
    }

    return coords;
}*/
