#include <vector>
#include <limits.h>
/*#include <cilk/cilk.h>
#include <pthread.h>
#include <tbb/mutex.h>*/
#include "Piece.h"
#include "Player.h"

using namespace std;

class BoardState {
public:
    int curr_player;
    Player *players[2];
    Piece **board;

    BoardState(bool);
    BoardState(int, Player *, Player *, Piece **);
    ~BoardState();
    BoardState *deepcopy();

    bool check();
    // bool checkmate();

    bool move_piece(int, int, int, int);
    vector<BoardState *> castle();
    BoardState *make_moves(int, int, int);
    BoardState *castle(int, int);
    vector<BoardState *> find_legal_moves();

    int eval();
    int minimax(int);
    int negamax(int);
    BoardState *mm(int, int, int, BoardState **);
};
