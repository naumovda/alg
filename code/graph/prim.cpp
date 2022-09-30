#include <vector>
#include <set>
#include <queue>

#include <iostream>

using namespace std;

const int INF = 1e6; //infinity

const int c_white = 0;
const int c_grey = 1;
const int c_black = 2;

class Edge
{
    public:
    int from;
    int to;
    int weight;

    Edge(int _from, int _to, int _weight)
    {
        from = _from;
        to = _to;
        weight = _weight;
    }
};

bool operator <(const Edge &v1, const Edge &v2)
{
   return v1.weight > v2.weight;
}

typedef int Vertex;

void test_Prima()
{
    int vertex_count = 8;

    //initialize vertexes;
    set<Vertex> vertexes = {0, 1, 2, 3, 4, 5, 6, 7};

    //initialize graph data
    vector<Edge> graph;
    graph.push_back(Edge(0, 1, 10));
    graph.push_back(Edge(0, 2, 7));
    graph.push_back(Edge(0, 5, 26));
    graph.push_back(Edge(0, 6, 20));
    graph.push_back(Edge(0, 7, 9));
    graph.push_back(Edge(1, 7, 7));
    graph.push_back(Edge(3, 4, 11));
    graph.push_back(Edge(3, 5, 4));
    graph.push_back(Edge(4, 5, 15));
    graph.push_back(Edge(4, 6, 30));
    graph.push_back(Edge(4, 7, 22));
    graph.push_back(Edge(6, 7, 10));

    set<Vertex> mst;
    set<Vertex> n_mst = vertexes;

    Vertex s = 0;
    mst.insert(s);
    n_mst.erase(s);

    vector<Edge> mst_e;

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


    cout << "MST: ";
    for (auto v: mst)
    {
        cout << v << " ";
    }
    cout << endl;

    cout << "Not MST: ";
    for (auto v: n_mst)
    {
        cout << v << " ";
    }
    cout << endl;

    while (mst.size() != vertex_count)
    {
        Edge min_edge(-1, -1, INF);

        for (auto e: graph)
        {
            if (mst.count(e.to) != mst.count(e.from))
            {
                if (min_edge.weight > e.weight)
                    min_edge = e;
            }
        }

        n_mst.erase(min_edge.from);
        n_mst.erase(min_edge.to);
        mst.insert(min_edge.from);
        mst.insert(min_edge.to);

        mst_e.push_back(min_edge);
    }

    cout << "MST edges: ";
    for (auto e: mst_e)
    {
        cout << "(" << e.from << "," << e.to << ") ";
    }
    cout << endl;
}

void test_PrimaPrior()
{
    int c;

    int vertex_count = 8;

    //initialize vertexes;
    set<Vertex> vertexes = {0, 1, 2, 3, 4, 5, 6, 7};

    //initialize graph data
    vector<Edge> graph;
    graph.push_back(Edge(0, 1, 10));
    graph.push_back(Edge(0, 2, 7));
    graph.push_back(Edge(0, 5, 26));
    graph.push_back(Edge(0, 6, 20));
    graph.push_back(Edge(0, 7, 9));
    graph.push_back(Edge(1, 7, 7));
    graph.push_back(Edge(3, 4, 11));
    graph.push_back(Edge(3, 5, 4));
    graph.push_back(Edge(4, 5, 15));
    graph.push_back(Edge(4, 6, 30));
    graph.push_back(Edge(4, 7, 22));
    graph.push_back(Edge(6, 7, 10));

    set<Vertex> mst;
    set<Vertex> n_mst = vertexes;

    Vertex s = 0;
    //mst.insert(s);
    //n_mst.erase(s);

    vector<Edge> mst_e;

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

    priority_queue<Edge> pque;
    for (auto e: graph)
    {
        pque.push(e);
    }
    cout << "pque " << pque.size() << endl;
    cin >> c;

    while (mst.size() != vertex_count)
    {
        Edge min_edge = pque.top();
        cout << "que size = " << pque.size() << endl;
        cout << "min edge = " << min_edge.from << " " << min_edge.to << " " << min_edge.weight << endl;
        pque.pop();
        cout << "que size = " << pque.size() << endl;

        if ((mst.size()==0)||(mst.count(min_edge.to) != mst.count(min_edge.from)))
        {
            n_mst.erase(min_edge.from);
            n_mst.erase(min_edge.to);
            mst.insert(min_edge.from);
            mst.insert(min_edge.to);

            mst_e.push_back(min_edge);
        }
        cout << "mst size =" << mst.size() << endl;
        cout << "mst size =" << mst_e.size() << endl;

        cin >> c;
    }

    cout << "MST edges: ";
    for (auto e: mst_e)
    {
        cout << "(" << e.from << "," << e.to << ") ";
    }
    cout << endl;
}

int main(void)
{
    test_PrimaPrior();

    return 0;
}
