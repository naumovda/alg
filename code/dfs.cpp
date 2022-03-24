#include <iostream>

#include <array>
#include <vector>
#include <stack>
#include <set>

using namespace std;

struct Move
{
    int off_i;
    int off_j;

    Move(int _i, int _j)
    {
        off_i = _i; off_j = _j;
    }
};

class State
{
private:
    int i;
    int j;

public:
    State(int _i, int _j)
    {
        i = _i; j = _j;
    }

    void do_move(Move m)
    {
        i += m.off_i;
        j += m.off_j;
    }

    void undo_move(Move m)
    {
        i -= m.off_i;
        j -= m.off_j;
    }

    int depth;

    int get_i()
    {
        return i;
    }

    int get_j()
    {
        return j;
    }

    friend bool operator==(const State& left, const State& right);
    friend bool operator!=(const State& left, const State& right);
    friend bool operator <(const State& left, const State& right);
};

bool operator==(const State& left, const State& right)
{
    return (left.i == right.i) && (left.j == right.j);
}

bool operator!=(const State& left, const State& right)
{
    return !(left==right);
}

bool operator <(const State& left, const State& right)
{
    return (left.i < right.i || left.j < right.j);
}

class Labirinth
{
private:
    string *_map;

    int width;
    int height;
public:
    Labirinth()
    {
        width = 10;
        height = 6;

        _map = new string [height];
        _map[0] = string("**********");
        _map[1] = string("* **   * *");
        _map[2] = string("*    **  *");
        _map[3] = string("* ****   *");
        _map[4] = string("*      * *");
        _map[5] = string("**********");
    }

    ~Labirinth()
    {
        delete _map;
    }

    int get_width()
    {
        return width;
    }

    int get_height()
    {
        return height;
    }

    vector<Move> get_moves(int i, int j)
    {
        vector<Move> m;

        if (_map[i-1][j]==' ') m.push_back(Move(-1, 0));
        if (_map[i+1][j]==' ') m.push_back(Move( 1, 0));
        if (_map[i][j-1]==' ') m.push_back(Move(0, -1));
        if (_map[i][j+1]==' ') m.push_back(Move(0,  1));

        return m;
    }
};

bool dfs(Labirinth &L, State initial, State goal, vector<Move> &path)
{
    if (initial == goal)
        return true;

    stack<State> open_states;
    set<State> close_states;

    initial.depth = 0;

    open_states.push(initial);

    while (!open_states.empty())
    {
        State current = open_states.top();
        open_states.pop();

        close_states.insert(current);

        vector<Move> moves = L.get_moves(current.get_i(), current.get_j());
        for (Move mv: moves)
        {
            current.do_move(mv);

            auto it = close_states.find(current);
            if (it == close_states.end())
            {
                if (current == goal)
                {
                    return true;
                }

                current.depth++;
                open_states.push(current);
            }

            current.undo_move(mv);
        }
    }

    return false;
}

int main()
{
    Labirinth L;

    cout << "Start lab" << endl;
    cout << " w = " << L.get_width() << endl;
    cout << " h = " << L.get_height() << endl;

    vector<Move> m = L.get_moves(1, 1);

    cout << "Moves:" << endl;
    for (Move item: m)
        cout << item.off_i << " " << item.off_j << endl;

    State initial(1,1);
    State goal(5, 8);

    vector<Move> path;

    cout << "Search:" << endl;
    cout << dfs(L, initial, goal, path);

    return 0;
}
