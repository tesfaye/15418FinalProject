#include <iostream>
#include <string>
#include "Player.h"

#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

using namespace std;

Player::Player() {
    this->player = -1;
    this->king_row = -1;
    this->king_col = -1;
    vector<Piece *> pieces;
    this->pieces = pieces;
}

Player::Player(int player, Piece **board, bool flag) {
    this->player = player;
    vector<Piece *> pieces;

    if (flag) {
        // black player
        if (player) {
	    // start game
            /*pieces.push_back(new Rook(player, 0, 0));
            pieces.push_back(new Knight(player, 0, 1));
            pieces.push_back(new Bishop(player, 0, 2));
            pieces.push_back(new Queen(player, 0, 3));
            pieces.push_back(new King(player, 0, 4));
            pieces.push_back(new Bishop(player, 0, 5));
            pieces.push_back(new Knight(player, 0, 6));
            pieces.push_back(new Rook(player, 0, 7));

            pieces.push_back(new Pawn(player, 1, 0));
            pieces.push_back(new Pawn(player, 1, 1));
            pieces.push_back(new Pawn(player, 1, 2));
            pieces.push_back(new Pawn(player, 1, 3));
            pieces.push_back(new Pawn(player, 1, 4));
            pieces.push_back(new Pawn(player, 1, 5));
            pieces.push_back(new Pawn(player, 1, 6));
            pieces.push_back(new Pawn(player, 1, 7));

            this->king_row = 0;
            this->king_col = 4;*/

	    // mid game
	    pieces.push_back(new Rook(player, 0, 3));
	    pieces.push_back(new Rook(player, 0, 4));
	    pieces.push_back(new King(player, 1, 6));
	    pieces.push_back(new Bishop(player, 2, 3));
	    pieces.push_back(new Queen(player, 3, 4));
	    pieces.push_back(new Bishop(player, 4, 4));
	    pieces.push_back(new Knight(player, 4, 5));

	    pieces.push_back(new Pawn(player, 1, 0, false));
	    pieces.push_back(new Pawn(player, 1, 1, false));
	    pieces.push_back(new Pawn(player, 1, 2, false));
	    pieces.push_back(new Pawn(player, 2, 2, false));
	    pieces.push_back(new Pawn(player, 1, 5, false));
	    pieces.push_back(new Pawn(player, 1, 7, false));

	    this->king_row = 1;
	    this->king_col = 6;

	    // end game
            /*pieces.push_back(new Knight(player, 1, 4));
            pieces.push_back(new King(player, 6, 3));
            pieces.push_back(new Bishop(player, 5, 5));

            this->king_row = 6;
            this->king_col = 3;*/
    	}

    	// white player
        else {
	    // start game
            /*pieces.push_back(new Rook(player, 7, 0));
            pieces.push_back(new Knight(player, 7, 1));
            pieces.push_back(new Bishop(player, 7, 2));
            pieces.push_back(new Queen(player, 7, 3));
            pieces.push_back(new King(player, 7, 4));
            pieces.push_back(new Bishop(player, 7, 5));
            pieces.push_back(new Knight(player, 7, 6));
            pieces.push_back(new Rook(player, 7, 7));

            pieces.push_back(new Pawn(player, 6, 0));
            pieces.push_back(new Pawn(player, 6, 1));
            pieces.push_back(new Pawn(player, 6, 2));
            pieces.push_back(new Pawn(player, 6, 3));
            pieces.push_back(new Pawn(player, 6, 4));
            pieces.push_back(new Pawn(player, 6, 5));
            pieces.push_back(new Pawn(player, 6, 6));
            pieces.push_back(new Pawn(player, 6, 7));

            this->king_row = 7;
            this->king_col = 4;*/

	    // mid game
	    pieces.push_back(new King(player, 7, 2));
	    pieces.push_back(new Rook(player, 7, 3));
	    pieces.push_back(new Rook(player, 7, 7));
	    pieces.push_back(new Bishop(player, 6, 4));
	    pieces.push_back(new Bishop(player, 5, 4));
	    pieces.push_back(new Queen(player, 5, 7));

	    pieces.push_back(new Pawn(player, 6, 0, false));
	    pieces.push_back(new Pawn(player, 6, 1, false));
	    pieces.push_back(new Pawn(player, 5, 2, false));
	    pieces.push_back(new Pawn(player, 6, 5, false));
	    pieces.push_back(new Pawn(player, 6, 6, false));
	    pieces.push_back(new Pawn(player, 6, 7, false));

	    this->king_row = 7;
	    this->king_col = 2;

	    // end game
            /*pieces.push_back(new Rook(player, 2, 5));
            pieces.push_back(new King(player, 1, 1));

            this->king_row = 1;
            this->king_col = 1;*/
        }
    }

    else {
        // black player
        if (player) {
            pieces.push_back(new Knight(player, 1, 4));
            pieces.push_back(new King(player, 6, 3));
            pieces.push_back(new Bishop(player, 5, 5));
	    pieces.push_back(new Queen(player, 0, 7));
	    pieces.push_back(new Pawn(player, 4, 0, false));

            this->king_row = 6;
            this->king_col = 3;
    	}

    	// white player
        else {
            pieces.push_back(new Rook(player, 2, 5));
            pieces.push_back(new King(player, 1, 1));
	    pieces.push_back(new Queen(player, 2, 1));
	    pieces.push_back(new Knight(player, 2, 6));
	    pieces.push_back(new Pawn(player, 6, 6, true));
	    pieces.push_back(new Pawn(player, 3, 2, false));

            this->king_row = 1;
            this->king_col = 1;
        }
    }


    // puts the pieces on board
    for (int i = 0; i < pieces.size(); i++) {
        pieces[i]->put_on_board(board);
    }

    this->pieces = pieces;
}

Player::~Player() {
    vector<Piece *> pieces = this->pieces;

    for (int i = 0; i < pieces.size(); i++ ) {
        delete pieces[i];
    }
}

void Player::to_string() {
    cout << this->player << "\n";
    for (int i = 0; i < (this->pieces).size(); i++) {
        (this->pieces[i])->to_string();
    }
}

Player *Player::deepcopy(Piece **board) {
    Player *new_player = new Player();

    new_player->player = this->player;
    new_player->king_row = this->king_row;
    new_player->king_col = this->king_col;

    vector<Piece *> new_pieces;
    vector<Piece *> pieces = this->pieces;
    for (int i = 0; i < pieces.size(); i++) {
        Piece *piece = pieces[i];
        new_pieces.push_back(piece->deepcopy());
    }

    for (int i = 0; i < new_pieces.size(); i++) {
        Piece *piece = new_pieces[i];
        piece->put_on_board(board);
    }

    new_player->pieces = new_pieces;

    return new_player;
}
