#include <iostream>
#include <vector>

#include <chrono>
#include <ctime>    

using namespace std;

int main(void)
{
    auto start = std::chrono::system_clock::now();

    int size;
    int value;

    cin >> size;

    if (size < 3)
    {
        throw std::invalid_argument("Data array must contain at least 3 values");
    }

    vector<int> data(size);

    int i = 0;
    while (i < size)
    {
        cin >> value;
        data[i] = value;
        i++;
    }      
    
    auto middle = std::chrono::system_clock::now();

    int max1 = data[0];
    int max2 = data[1];
    int max3 = data[2];
    
    int tmp;
    
    if (max1 < max2)
    {
        tmp = max1;
        max1 = max2;
        max2 = tmp;
    }

    if (max1 < max3)
    {
        tmp = max1;
        max1 = max3;
        max3 = tmp;
    }
            
    if (max2 < max3)
    {
        tmp = max2;
        max2 = max3;
        max3 = tmp;
    }
                
    int min1 = max3;
    int min2 = max2;

    int idx = 3;
    while (idx < data.size())
    {
        if (data[idx] > max1)
        {
            max3 = max2;
            max2 = max1;
            max1 = data[idx];
        }
        else if (data[idx] > max2)
        {
            max3 = max2;
            max2 = data[idx];
        }
        else if (data[idx] > max3)
        {
            max3 = data[idx];
        };
        
        if (data[idx] < min1)
        {
            min2 = min1;
            min1 = data[idx];
        }
        else if (data[idx] < min2)
        {
            min2 = data[idx];
        };

        idx++;
    }

    long long m1 = max1;
    m1 *= max2;
    m1 *= max3;

    long long m2 = min1;
    m2 *= min2;
    m2 *= max1;

    if (m1 > m2)
    { 
        cout << m1;
    }
    else
    {
        cout << m2;
    }

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::chrono::duration<double> elapsed_seconds_mid = middle - start;
    
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << endl << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
    std::cout << "elapsed time load: " << elapsed_seconds_mid.count() << "s" << std::endl;
    
    return 0;
}