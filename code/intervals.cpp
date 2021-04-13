#include <iostream>
#include <limits.h>

#define inf (-INT_MAX)

int op(int a, int b)
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
    void propagate(int index);
    void insert(int index, int value);
    int func(int left, int right);
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
    std::swap(body[a], body[b]);
}

void tree::print()
{    
    for (int i=0; i<size; i++)
        printf("|%2d", i);
    printf("|\n");
    for (int i=0; i<size; i++)
        printf("|%2d", body[i]);
    printf("|\n");
}

void tree::propagate(int index)
{
    while (index > 0)
    {
        body[index/2] = op(body[index], body[index+1]);
        index /= 2;
    }
}

void tree::insert(int index, int value)
{
    body[size/2 + index] = value;
    propagate(size/2 + index);
}

int tree::func(int left, int right)
{
    int res = inf;
    if (left % 2 == 1)
        res = op(res, body[left++]);
    if (right % 2 == 0)
        res = op(res, body[right--]);        
    if (right > left)
        res = op(res, func(left/2, right/2));                
    return res;
}

int main(void)
{
    int size;

    std::cin >> size;
    
    tree t = tree(size);
    for (int i=0; i<=t.size; i++) t.body[i] = inf;
    for (int i=0; i<size; i++)
    {
        int value;
        std::cin >> value;
        t.insert(i, value);
    }

    int left, right;

    std::cin >> left;
    std::cin >> right;

    t.print();

    printf("\nmax(%d, %d)=%d", left, right, t.func(left, right));

    return 0;
}