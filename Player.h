#include <vector>
#include "Piece.h"

using namespace std;

class Player {
public:
    int player;
    int king_row;
    int king_col;
    vector<Piece *> pieces;

    Player();
    Player(int, Piece **, bool);
    ~Player();
    void to_string();
    Player *deepcopy(Piece **);
};
