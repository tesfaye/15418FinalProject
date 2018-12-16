#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

#define BOARD_DIM 8
#define INDEX(r, c) ((r) * BOARD_DIM + (c))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#include <stdbool.h>
#include <vector>

using namespace std;

class Piece {
public:
	int player;
	int row;
	int col;
    char piece;
    bool first;
    int value;

	Piece(int, int, int);
    virtual ~Piece();
	void to_string();
    virtual Piece *deepcopy() = 0;
    void put_on_board(Piece **);
    void move_on_board(Piece **, int, int);
    void put_on_check_board(Piece **, bool *);
    virtual vector<pair<int, int> >find_valid_moves(Piece **board) = 0;
};

#endif /* PIECE_INCLUDED */
