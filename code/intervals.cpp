#include <iostream>
#include <iomanip>
#include <limits.h>

using namespace std;

#define inf (-1) //(-INT_MAX)

int f_max(int a, int b)
{
    return a>b?a:b;
}

struct tree
{
    int *body;
    int size;
    int numnodes;

    tree(int maxsize);
    ~tree();
    
    void swap(int a, int b);
    void print();

    void propagate(int index, int (*f)(int, int));
    void insert(int index, int value, int (*f)(int, int));    
    int calculate(int left, int right, int (*f)(int, int));
};

tree::tree(int maxsize)
{
    int k = 1;
    while (k <= maxsize) k *= 2;

    body = new int[k + 1];
    size = k;
    numnodes = 0;
}

tree::~tree()
{
    delete body;
}

void tree::swap(int a, int b)
{
    swap(body[a], body[b]);
}

void tree::print()
{    
    for (int i=0; i<size; i++)
        cout << "|" << setw(2) << i;
    cout << "|" << endl;            
    for (int i=0; i<size; i++)
        cout << "|" << setw(2) << body[i];    
    cout << "|" << endl;
}

void tree::propagate(int index, int (*f)(int, int))
{
    while (index > 0)
    {
        body[index/2] = f(body[index], body[index/2]);
        index /= 2;
    }
}

void tree::insert(int index, int value, int (*f)(int, int))
{
    body[size/2 + index] = value;
    numnodes++;

    propagate(size/2 + index, f);
}

int tree::calculate(int left, int right, int (*f)(int, int))
{
    int res = inf;
    if (left % 2 == 1)
        res = f(res, body[left++]);
    if (right % 2 == 0)
        res = f(res, body[right--]);        
    if (right > left)
        res = f(res, calculate(left/2, right/2, f));                
    return res;
}

int main(void)
{
    int size;

    cin >> size;
    
    tree t = tree(size);

    for (int i=0; i<=t.size; i++) 
        t.body[i] = inf;
    
    for (int i=0; i<size; i++)
    {
        int value;
        
        cin >> value;
        
        t.insert(i, value, f_max);

        // cout << "=" << i << endl;
        // t.print();
    }

    int left, right, start = size;

    cin >> left;
    cin >> right;

    t.print();

    cout << "size=" << t.size << endl;
    cout << "max(" << left << "," << right << ")=" 
         << t.calculate(left+start, right+start, f_max);

    return 0;
}