#include <bits/stdc++.h>
using namespace std;
 
typedef long long Long;
const double ERROR = 1e-9;
const double M_2PI = 2 * M_PI;
bool Equal(double a, double b) { 
    return fabs(a - b) < ERROR;
}
struct Point{
    double x;
    double y;
    Point(double x=0.0, double y=0.0): x(x),y(y){}
    Point operator+(const Point p) { return Point(x+p.x,y+p.y); }
    Point operator-(const Point p) { return Point(x-p.x,y-p.y); }
    Point operator*(const double v) { return Point(x*v,y*v); }
    bool operator<(const Point& cmp) const {
        if (!Equal(x, cmp.x)) return x < cmp.x;
        return Equal(y, cmp.y)? false: y < cmp.y;
    }
    bool operator==(const Point& cmp) {
        return Equal(x, cmp.x) && Equal(y, cmp.y);
    } 

    double magnitude() { return hypot(x,y); }
    double dot(const Point p) { return x*p.x + y*p.y; }
    double cross(const Point p) { return x*p.y-p.x*y; }
    double dist(const Point p) { return(sqrt( (*this-p).dot(*this-p))); }
    double angle() { return atan2(y,x) * 180/M_PI; }

    /**
     * Moves a vector 'p' to origin 'o'
     * */
    Point Move(Point o) {
        return Point(x - o.x, y - o.y);
    }

    /**
     * Right Hand method for determmining the orientation of two vectors
     * using 'o' as origin of vectors
     * CCW = 1, CW = -1, Colineal = 0.
     * */
    int RightHand(Point o, Point q) {
        Point aux = Move(o);
        double ccw = aux.cross(q.Move(o));
        return Equal(ccw, 0)? 0: (ccw < 0)? -1: 1;
    }
};

//  method to find maximum colinear point
int maxPointOnSameLine(vector< Point > points)
{
    int N = points.size();
    if (N < 2)
        return N;
 
    int maxPoint = 0;
    int curMax, overlapPoints, verticalPoints;
 
    // map to store slope pair
    map<Point, int> slopeMap;
 
    //  looping for each point
    for (int i = 0; i < N; i++)
    {
        curMax = overlapPoints = verticalPoints = 0;
 
        //  looping from i + 1 to ignore same pair again
        for (int j = i + 1; j < N; j++)
        {
            //  If both point are equal then just
            // increase overlapPoint count
            if (points[i] == points[j])
                overlapPoints++;
 
            // If x co-ordinate is same, then both
            // point are vertical to each other
            else if (points[i].x == points[j].x)
                verticalPoints++;
 
            else
            {
                int yDif = points[j].y - points[i].y;
                int xDif = points[j].x - points[i].x;
                int g = __gcd(xDif, yDif);
 
                // reducing the difference by their gcd
                yDif /= g;
                xDif /= g;
 
                // increasing the frequency of current slope
                // in map
                slopeMap[Point(yDif, xDif)]++;
                curMax = max(curMax, slopeMap[Point(yDif, xDif)]);
            }
 
            curMax = max(curMax, verticalPoints);
        }
 
        // updating global maximum by current point's maximum
        maxPoint = max(maxPoint, curMax + overlapPoints + 1);
 
        // printf("maximum colinear point which contains current
        // point are : %d\n", curMax + overlapPoints + 1);
        slopeMap.clear();
    }
 
    return maxPoint;
}
 
//  Driver code
int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int N;
    while(cin>>N)
    {
        if(N == 0) break;
        vector< Point > points;
        for(int i = 0 ; i < N; i++)
        {
            int x,y;
            cin>>x>>y;
            points.push_back(Point(x,y));
        }
     
        cout << maxPointOnSameLine(points) << endl;
    }
 
    return 0;
}