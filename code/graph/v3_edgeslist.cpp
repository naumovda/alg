#include <vector>
#include <set>
#include <queue>

#include <iostream>

using namespace std;

const int INF = 1e6; //infinity

const int c_white = 0;
const int c_grey = 1;
const int c_black = 2;

struct Edge
{
    int from;
    int to;
    int time_in;
    int time_out;

    Edge(int _from, int _to)
    {
        from = _from;
        to = _to;
        time_in = -1;
        time_out = -1;
    }
};

typedef int Vertex;

void BFS(int vertex_count, set<Vertex> &vertexes,
         vector<Edge> &graph, Vertex s,
         vector<Vertex> &d, vector<Vertex> &c, vector<Vertex> &p
         )
{
    queue<Vertex> q;
    q.push(s);
    d[s] = 0;
    c[s] = c_grey;

    while (!q.empty())
    {
        Vertex u = q.back();
        q.pop();

        set<Vertex> adj;

        //find adj(u)
        for(auto e: graph)
        {
            if (e.from == u)
                adj.insert(e.to);
        }

        for (auto v: adj)
        {

            if (c[v] == c_white)
            {
                q.push(v);
                d[v] = d[u] + 1;
                p[v] = u;
                c[v] = c_grey;
            }
        }

        c[u] = c_black;
    }

}

int main(void)
{
    int vertex_count = 8;

    //initialize vertexes;
    set<Vertex> vertexes = {0, 1, 2, 3, 4, 5, 6, 7};

    //initialize graph data
    vector<Edge> graph;
    graph.push_back(Edge(0, 2));
    graph.push_back(Edge(1, 0));
    graph.push_back(Edge(2, 0));
    graph.push_back(Edge(2, 3));
    graph.push_back(Edge(3, 1));
    graph.push_back(Edge(4, 1));
    graph.push_back(Edge(4, 3));
    graph.push_back(Edge(5, 6));
    graph.push_back(Edge(6, 4));
    graph.push_back(Edge(7, 6));


    //output results
    cout << "Vertexes: ";
    for (auto v: vertexes)
    {
        cout << v << " ";
    }
    cout << endl;

    cout << "Edges: ";
    for (auto e: graph)
    {
        cout << "(" << e.from << "," << e.to << ") ";
    }
    cout << endl;

    Vertex s = 1; //start from vertex 1
    vector<int> d(vertex_count, INF);
    vector<int> c(vertex_count, c_white);
    vector<int> p(vertex_count, -1);

    BFS(vertex_count, vertexes, graph, s, d, c, p);

    cout << "BFS" << endl;
    cout << "d: ";
    for (auto item: d)
    {
        cout << item << " ";
    }
    cout << endl;

    cout << "p: ";
    for (auto item: p)
    {
        cout << item << " ";
    }
    cout << endl;

    cout << "c: ";
    for (auto item: c)
    {
        cout << item << " ";
    }
    cout << endl;

    return 0;
}
