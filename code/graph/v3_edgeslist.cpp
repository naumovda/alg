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

void DFS_visit(Vertex u, int &time, int vertex_count, set<Vertex> &vertexes, vector<Edge> &graph,
               vector<Vertex> &d, vector<Vertex> &f, vector<Vertex> &c, vector<Vertex> &p,
               queue<Vertex> &L)
{
    c[u] = c_grey;
    time += 1;
    d[u] = time;

    //for all v = Adj[u]
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
            p[v] = u;
            DFS_visit(v, time, vertex_count, vertexes, graph, d, f, c, p, L);
        }
    }

    c[u] = c_black;
    time += 1;
    f[u] = time;

    L.push(u);
}

void DFS(int vertex_count, set<Vertex> &vertexes,
         vector<Edge> &graph, Vertex s,
         vector<Vertex> &d, vector<Vertex> &f, vector<Vertex> &c, vector<Vertex> &p,
         queue<Vertex> &L
         )
{
    int time = 0;

    for (auto v: vertexes)
    {
        d[v] = INF;
        f[v] = INF;
        c[v] = c_white;
        p[v] = -1;
    }

    DFS_visit(s, time, vertex_count, vertexes, graph, d, f, c, p, L); //start from vertex s

    for (auto v: vertexes)
    {
        if (c[v] == c_white)
        {
            DFS_visit(v, time, vertex_count, vertexes, graph, d, f, c, p, L);
        }
    }
}

void TopoSort(int vertex_count, set<Vertex> &vertexes,
         vector<Edge> &graph,
         vector<Vertex> &d, vector<Vertex> &f, vector<Vertex> &c, vector<Vertex> &p,
         queue<Vertex> &L)
{
    for (auto v: vertexes)
    {
        d[v] = INF;
        f[v] = INF;
        c[v] = c_white;
        p[v] = -1;
    }

    while (!L.empty())
        L.pop();

    int time = 0;

    DFS_visit(0, time, vertex_count, vertexes, graph, d, f, c, p, L);
}

void test_BFS()
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
    vector<int> f(vertex_count, INF);
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
}

void test_DFS()
{
     int vertex_count = 6;

    //initialize vertexes;
    set<Vertex> vertexes = {0, 1, 2, 3, 4, 5};

    //initialize graph data
    vector<Edge> graph;
    graph.push_back(Edge(0, 1));
    graph.push_back(Edge(0, 3));
    graph.push_back(Edge(1, 5));
    graph.push_back(Edge(2, 0));
    graph.push_back(Edge(2, 4));
    graph.push_back(Edge(3, 1));
    graph.push_back(Edge(3, 2));
    graph.push_back(Edge(4, 3));
    graph.push_back(Edge(4, 5));
    graph.push_back(Edge(5, 3));
    graph.push_back(Edge(5, 4));

    queue<Vertex> L;

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

    Vertex s = 0; //start from vertex 1

    vector<int> d(vertex_count, INF);
    vector<int> f(vertex_count, INF);
    vector<int> c(vertex_count, c_white);
    vector<int> p(vertex_count, -1);

    DFS(vertex_count, vertexes, graph, s, d, f, c, p, L);

    cout << "DFS" << endl;

    cout << "time in: ";
    for (auto item: d)
    {
        cout << item << " ";
    }
    cout << endl;

    cout << "time out: ";
    for (auto item: f)
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
}

void test_TopoSort()
{
    int vertex_count = 6;

    //initialize vertexes;
    set<Vertex> vertexes = {0, 1, 2, 3, 4, 5};

    //initialize graph data
    vector<Edge> graph;
    graph.push_back(Edge(0, 1));
    graph.push_back(Edge(0, 3));
    graph.push_back(Edge(1, 5));
    graph.push_back(Edge(2, 0));
    graph.push_back(Edge(2, 4));
    graph.push_back(Edge(3, 1));
    graph.push_back(Edge(3, 2));
    graph.push_back(Edge(4, 3));
    graph.push_back(Edge(4, 5));
    graph.push_back(Edge(5, 3));
    graph.push_back(Edge(5, 4));

    queue<Vertex> L;

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

    Vertex s = 0; //start from vertex 1

    vector<int> d(vertex_count, INF);
    vector<int> f(vertex_count, INF);
    vector<int> c(vertex_count, c_white);
    vector<int> p(vertex_count, -1);

    TopoSort(vertex_count, vertexes, graph, d, f, c, p, L);

    cout << "Topo sort:" << endl;

    Vertex u;
    while (!L.empty())
    {
        u = L.front();
        L.pop();

        cout << u << " ";
    }
    cout << endl;
}

int main(void)
{
    //test_BFS();

    //test_DFS();

    test_TopoSort();

    return 0;
}
