#include <iostream>
#include <iomanip>
#include <vector>

#include <chrono>
#include <ctime>    

constexpr auto DEBUG = 0;

using namespace std;

class Point
{
public:
    int x;
    int y;

    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }

    friend bool operator== (const Point& p1, const Point& p2);
    friend bool operator!= (const Point& p1, const Point& p2);
};

bool operator== (const Point& p1, const Point& p2)
{
    return (p1.x == p2.x && p2.y == p2.y);
}

bool operator!= (const Point& p1, const Point& p2)
{
    return !(p1 == p2);
}

long getDistanceSqr(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

double getAngleCos(Point p1, Point p2, Point p3)
{
    int
        x1 = p2.x - p1.x,
        x2 = p2.x - p3.x,
        y1 = p2.y - p1.y,
        y2 = p2.y - p3.y;

    double d1 = x1 * x1 + y1 * y1;
    double d2 = x2 * x2 + y2 * y2;
    
    double r = x1 * x2 + y1 * y2;

    return r / sqrt(d1 * d2);
}

double getPolygonPerimeter(vector<Point> data)
{
    size_t size = data.size();

    double perimeter = sqrt(getDistanceSqr(data[0], data[data.size()-1]));;
    for (int i = 0; i < size-1; i++)
    {
        perimeter += sqrt(getDistanceSqr(data[i], data[i + 1]));
    }

    return perimeter;
}

vector<Point> getMinPolygon(vector<Point> &greeds)
{
    vector<Point> points = {};

    Point point = greeds[0];
    Point prev_point = Point(point.x, point.y - 1);

    size_t idx = 0;
    while (true)
    {
        Point next_point(0, 0);
        size_t idx_point = -1;
        double min_cosAngle = 1;

        for (size_t idx_next = idx + 1; idx_next < greeds.size(); idx_next++)
        {
            Point new_point = greeds[idx_next];
            double cosAngle = getAngleCos(prev_point, point, new_point);

            if (cosAngle < min_cosAngle)
            {
                min_cosAngle = cosAngle;
                next_point = new_point;
                idx_point = idx_next;
            }
        }

        points.push_back(point);

        if (idx_point == -1)
            break;

        prev_point = point;        
        point = next_point;
        idx = idx_point;
    }

    if (points[0] != points[points.size() - 1])
    {
        points.push_back(points[0]);
    }

    return points;
}

int main(void)
{
    auto start = std::chrono::system_clock::now();

    const int min_idx = -10000;
    const int max_idx = 10000;

    //const int min_idx = -1;
    //const int max_idx = 4;

    int size;
    int x, y;

    if (DEBUG)
        cout << "size: ";

    cin >> size;

    if (size < 5)
    {
        throw std::invalid_argument("Data array must contain at least 5 values");
		return -1;
    }

    vector<int>greeds_max(max_idx - min_idx + 1, min_idx - 1);
    vector<int>greeds_min(max_idx - min_idx + 1, max_idx + 1);

    int i = 0;
    while (i < size)    
    {
        if (DEBUG)
            cout << "\n [" << i << "] x, y: ";
        
        cin >> x;
		cin >> y;
        
        greeds_min[x - min_idx] = min(greeds_min[x - min_idx], y);
        greeds_max[x - min_idx] = max(greeds_max[x - min_idx], y);

        i++;
    }  

    vector<Point> points = {};

    for (int i = 0; i <= max_idx - min_idx; i++)
    {
        if (greeds_max[i] > min_idx - 1) // min_idx - 1 is a default value
        {
            points.push_back(Point(i + min_idx, greeds_max[i]));
        }  
    }

    int offset = 0;
    if (greeds_max[max_idx - min_idx] == greeds_min[max_idx - min_idx])
    {
        offset = 1;
    }

    for (int i = max_idx - min_idx - offset; i >= 0; i--)
    {
        if (greeds_min[i] < max_idx + 1) // max_idx - 1 is a default value
        {
            points.push_back(Point(i + min_idx, greeds_min[i]));
        }
    }

    vector<Point> polygon = getMinPolygon(points);

    double perimetr = getPolygonPerimeter(polygon);

    cout << setprecision(2) << fixed << perimetr << endl;

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;    
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << endl << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
    
    return 0;
}