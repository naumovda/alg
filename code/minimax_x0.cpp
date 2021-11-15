#include <iostream>
#include <array>
#include <vector>

using namespace std;

static char blank = ' ';
static char px = 'x';
static char p0 = '0';

static int INF = 999;

typedef char e_player;

e_player get_opponent(e_player player)
{
    if (player == px) return p0;
    return px;
}


struct Move
{
    unsigned char row, col;
    e_player player;

    Move()
    {
        row = 0;
        col = 0;
        player = px;
    }

    Move(unsigned char _row, unsigned char _col, e_player _player)
    {
        row = _row;
        col = _col;
        player = _player;
    }

    void Print()
    {
        cout << "r=" << (int)row << " c=" << (int)col << " pl=" << player << endl;
    }

};

class State
{
private:
    unsigned char sz ;
    e_player field[3][3];

public:
    State(unsigned char _sz)
    {
        sz = _sz;
        for (unsigned char row=0; row<_sz; ++row)
            for (unsigned char col=0; col<_sz; ++col)
                field[row][col] = blank;
    }

    State(unsigned char _sz , char _field[3][3])
    {
        sz = _sz;
        for (unsigned char row=0; row<_sz; ++row)
            for (unsigned char col=0; col<_sz; ++col)
                field[row][col] = _field[row][col];
    }

    void DoMove(Move &m)
    {
        field[m.row][m.col] = m.player;
    }

    void UndoMove(Move &m)
    {
        field[m.row][m.col] = blank;
    }

    bool IsWin(e_player player)
    {
        if ((field[0][0] == player) && (field[0][1] == player) && (field[0][2] == player))
            return true;

        if ((field[1][0] == player) && (field[1][1] == player) && (field[1][2] == player))
            return true;

        if ((field[2][0] == player) && (field[2][1] == player) && (field[2][2] == player))
            return true;

        if ((field[0][0] == player) && (field[1][0] == player) && (field[2][0] == player))
            return true;

        if ((field[0][1] == player) && (field[1][1] == player) && (field[2][1] == player))
            return true;

        if ((field[0][2] == player) && (field[1][2] == player) && (field[2][2] == player))
            return true;

        if ((field[0][0] == player) && (field[1][1] == player) && (field[2][2] == player))
            return true;

        if ((field[0][2] == player) && (field[1][1] == player) && (field[2][0] == player))
            return true;

        return false;
    }

    int nc(e_player player)
    {
        int count = 0;
        e_player player_o = get_opponent(player);

        if ((field[0][0] != player_o) && (field[0][1] != player_o) && (field[0][2] != player_o))
            count++;

        if ((field[1][0] != player_o) && (field[1][1] != player_o) && (field[1][2] != player_o))
            count++;

        if ((field[2][0] != player_o) && (field[2][1] != player_o) && (field[2][2] != player_o))
            count++;

        if ((field[0][0] != player_o) && (field[1][0] != player_o) && (field[2][0] != player_o))
            count++;

        if ((field[0][1] != player_o) && (field[1][1] != player_o) && (field[2][1] != player_o))
            count++;

        if ((field[0][2] != player_o) && (field[1][2] != player_o) && (field[2][2] != player_o))
            count++;

        if ((field[0][0] != player_o) && (field[1][1] != player_o) && (field[2][2] != player_o))
            count++;

        if ((field[0][2] != player_o) && (field[1][1] != player_o) && (field[2][0] != player_o))
            count++;

        return count;
    }

    int score(e_player player)
    {
        if (IsWin(player))
            return INF;

        if (IsWin(get_opponent(player)))
            return (-1)*INF;

        return nc(player) - nc(get_opponent(player));
    }

    vector<Move> GetMoves(e_player pl)
    {
        vector <Move> moves;

        Move m;

        for (unsigned char row=0; row<sz; ++row)
           for (unsigned char col=0; col<sz; ++col)
                if (field[row][col] == blank)
                {
                    m.row = row;
                    m.col = col;
                    m.player = pl;

                    moves.push_back(m);
                }

        return moves;
    }

    void Print()
    {
        cout << endl;
        for (unsigned char row=0; row<sz; ++row)
        {
            cout << '[';
            for (unsigned char col=0; col<sz; ++col)
                cout << field[row][col];
            cout << ']' << endl;
        }
    }
};

int minimax(State st, int level, e_player original, e_player player, e_player opponent, Move &mv)
{
    int best_score;

    if (player == original)
        best_score = (-1) * INF;
    else
        best_score = INF;

    Move best_move;

    vector<Move> moves = st.GetMoves(player);

    if ((level == 0) || (moves.empty()))
    {
        mv = best_move;

        //st.Print();
        //cout << st.score(player) << " T" << endl;

        return st.score(player);
    }

    for (auto m : moves) {
        st.DoMove(m);

        int score = minimax(st, level-1, original, opponent, player, best_move);
        st.UndoMove(m);

        if (player == original)
        {
            if ((score > best_score)||(best_score==-INF))
            {
                best_move = m;
                best_score = score;
            }
        }
        else
        {
            if ((score < best_score)||(best_score==INF))
            {
                best_move = m;
                best_score = score;
            }
        }
    }

    mv = best_move;

    //st.Print();
    //cout << best_score << endl;

    return best_score;
}

int get_best_move(State st, int level, e_player player, e_player opponent, Move &mv)
{
    return minimax(st, level, player, player, opponent, mv);
}


int main()
{
    State base(3);

    //Move m(1, 1, px);

    //base.DoMove(m);


   //cout << "Base state" << endl;
    //base.Print();
    //cout << "Score: " << base.score(px);

   /*
   vector<Move> moves = base.GetMoves(px);

   cout << "Moves" << endl;
   for (auto m : moves) {
        m.Print();
   }

   base.DoMove(moves[2]);

   cout << "Next state" << endl;
   base.Print();

   moves = base.GetMoves(p0);

   cout << "New moves" << endl;
   for (auto m : moves) {
        m.Print();
   }
   */


   Move best_move;
   int score = get_best_move(base, 8, px, p0, best_move);

   cout << "Minimax by 4 levels" << endl;
   cout << "  best score = " << score << endl;

   best_move.Print();

}
