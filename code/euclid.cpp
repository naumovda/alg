#include <iostream>

using namespace std;

int modExp(int x, int y, int N)
{
    if (y==0) return 1;

    int z = modExp(x, y/2, N);

    if (y%2==0)
        return (int)(z*z%N);
    else
        return (int)(x*z*z%N);
}

bool primality2(int N, int k)
{
    //int k=2;
    //cout << "N=" << N << endl;
    int a;
    while(k--)
    {
        a = rand()%N;
        cout << "a=" << a << endl;
        cout << "a^N-1 mod N =" << modExp(a, N-1, N) << endl;
        if (modExp(a, N-1, N)!=1)
        {
            cout << N << " is not prime" << endl;

            return false;
        }

    }
    cout << N << " is prime" << endl;
    return true;
}

int generatePrim()
{
    int a;

    do
    {
        a = rand();
    } while(!primality2(a, 2));

    return a;
}

void euclid(int a, int b, int &x, int &y, int &d)
{
    if (b==0)
    {
        x = 1;
        y = 0;
        d = a;

        return;
    }

    int x1, y1, d1;

    euclid(b, a%b, x1, y1, d1);

    x = y1;
    y = x1 - (a/b)*y1;
    d = d1;
}

int testEuclid()
{
    int a = 40;
    int b = 3;

    int x, y, d;

    euclid(a, b, x, y, d);

    while (x < 0) x += b;
    while (y < 0) y += a;

    cout << "input: a=" << a << " b = " << b << endl;
    cout << "result: x=" << x << " y = " << y << " d=" << d <<endl;

    cout << primality2(129, 2);
    return 0;
}

int testPrim()
{
    int a = generatePrim();
    int b = generatePrim();

    cout << endl << "random = " << a << endl;
    cout << endl << "random = " << b << endl;
}

int main()
{
    testPrim();

    return 0;
}
