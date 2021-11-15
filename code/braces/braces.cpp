#include <iostream>
#include <string>
#include <exception>

using namespace std;

class stack{
    private:
        int size;
        int length;
        char *values;

    public:
        stack(int custom_size)
        {
            size = custom_size;
            values = new char[size];
            length = -1;
        }

        ~stack()
        {
            delete [] values;
        }

        bool empty()
        {
            return length == -1;
        }

        char pop()
        {
            if (empty())
            {
                throw runtime_error("Empty Stack");
            }

            return values[length--];
        }
        
        char peak()
        {
            if (empty())
            {
                throw runtime_error("Empty Stack");
            }
            
            return values[length];
        }

        void push(char value)
        {
            if (size == length)
            {
                throw runtime_error("Size Error");
            }

            values[++length] = value;
        }
};

bool is_open_brace(char c)
{
    return (c=='(') || 
        (c=='{') || 
        (c=='[');
};

bool is_close_brace(char c)
{
    return (c==')') || 
        (c=='}') || 
        (c==']');
};

bool is_pair_braces(char c1, char c2)
{
    return 
        (c1=='(' && c2==')' ) || 
        (c1=='{' && c2=='}' ) || 
        (c1=='[' && c2==']' );
};

int main(void)
{    
    cout << "\nStack example";

    stack s = stack(100);

    char c, c1;
      
    string str;

    cout << "\nInput string = ";
    cin >> str;
    cout << "\nSource string = " << str;

    bool is_balance = true;

    for (int i=0; i < str.size(); i++)
    {
        if (is_open_brace(str[i]))
        {
            try
            {
                s.push(str[i]);
            }
            catch(runtime_error &e)
            {
                cout << "\nError in push() " << e.what();
                return 0;
            }
        } else if (is_close_brace(str[i])) {
            try
            {
                c1 = s.pop();
            }
            catch(runtime_error &e)
            {                
                is_balance = false;
                break;
            }            
            if (!is_pair_braces(c1, str[i]))
            {
                is_balance = false;
                break;
            }
        }
    }
    is_balance = is_balance && s.empty();
    
    if (is_balance)
    {
        cout << "\nbalance: YES";
    } else {
        cout << "\nbalance: NO";
    }

    return 0;
}