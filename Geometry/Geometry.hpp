/**
 * Geometry Headers
 * Authors
 * David Vega and Rohin Mohanadas
 * */

#include <bits/stdc++.h>
using namespace std;
typedef long long Long;
const double ERROR = 1e-9;
const double M_2PI = 2 * M_PI;

/**
 * Floating point comparison
 * */
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

/**
 *  translate a point to the a new coordinate system with origin at o
 * */
Point translate(Point o, Point p) {
    return p-o;
}

/**
 * Takes in a vector of ordered points of a polygon given in either clockwise / counter clockwise direction
 * Returns the area of the polygon ( -ve value for CW Point vector and +ve for CCW)
 * */
double polygon_area(vector<Point> polygon)
{
        double area= 0;
        for(int i=0;i<polygon.size();i++){
            area+= polygon[i].cross(polygon[(i+1)%polygon.size()]);
        }
        area = area/2; 
        return area;
}

/* *
 * Check f line a-b is parallel to line c-d
 * */
bool parallel_segments(Point a, Point b, Point c, Point d){ // if (a,b) || (c,d)
    return abs((a-b).cross(c-d)) < ERROR; // sin(x) = 0
}

/* *
 * Check if point p lies on line a-b
 * */
bool point_on_segment(Point p, Point a, Point b){ // p belongs to [a,b] or not
    if (p.dist(a) < ERROR) return true;
    if (p.dist(b) < ERROR) return true;
    if (parallel_segments(p,a,p,b) && (p-a).dot(p-b) < 0) return true; // to check
    return false;
}

/**
 * Check if point p lies on the polygon a
 * */
bool point_on_polygon(Point p, const vector<Point> polygon){
    for (int i=0;i<polygon.size();i++)
        if (point_on_segment(p,polygon[i],polygon[(i+1)%polygon.size()]))
            return true;
    return false;
}

/**
 * Checks if where a point p lies with respect to polygon P
 * Returns : -1 if p lies on the polygon
 * 0 if p lies outside the polygon and
 * 1 if p lies inside the polygon
 * 
 * Algorithm : Even–odd rule
 * */
int pointandpoly( Point p,  vector<Point> polygon) {
    if (point_on_polygon(p, polygon)) return -1;
    bool result = false;
    int j = polygon.size()-1;
    for(int i=0;i<polygon.size();i++){
         if( ( (polygon[i].y > p.y) != (polygon[j].y > p.y) ) && (p.x < polygon[i].x + (polygon[j].x - polygon[i].x)*(p.y - polygon[i].y)/( polygon[j].y - polygon[i].y)))
            result = !result;
        j = i;
    }
    return result? 1:0;
}

/**
 * Convex hull of a given set of points
 * Returns : vector of points representing the polygon
 * */
vector<Point> ConvexHull(vector<Point> P){
    sort(P.begin(), P.end());
    vector<Point> Up, Down;
    for (int i = 0; i < P.size(); ++i) {
        while (Up.size() > 1) {
            int p = Up.size() - 1;
            // Allow colineals: <=
            if (Up[p-1].RightHand(Up[p], P[i]) < 0) break;
            Up.pop_back();
        }
        Up.push_back(P[i]);
    }
    Up.pop_back();
    for (int i = P.size() - 1; i >= 0; --i) {
        while (Down.size() > 1) {
            int p = Down.size() - 1;
            // Allow colineals: <=
            if (Down[p - 1].RightHand(Down[p], P[i]) < 0) break;
            Down.pop_back();
        }
        Down.push_back(P[i]);
    }
    Up.insert(Up.end(),
        Down.begin(), Down.end());
    return Up; // Convex hull.
}

/**
 * Helper methods for closest two pair of points.
 * */
double best_distance_pair;
Point global_point1,global_point2;

// comparison first done by y coordinate, then by x coordinate
bool Comparison_Y(Point a, Point b) {
    if(a.y < b.y) return true;
    if(a.y > b.y) return false;
    return a.x < b.x;
}
bool comparison_X(Point a, Point b)  {
    return a.x < b.x;
}

void merge(Point* a, Point* aux, int lo, int mid, int hi)   {
    int i, j, k;
    for(k = lo; k <= hi; k++)
        aux[k] = a[k];

    i = lo; j = mid + 1; k = lo;
    while(i <= mid && j <= hi)
        a[k++] = Comparison_Y(aux[i], aux[j]) ? aux[i++] : aux[j++];

    // Copy the rest of the left side of the array into the target array
    while(i <= mid)
        a[k++] = aux[i++];
}

double Closest_pair_points_process(Point* pointsByX, Point* pointsByY, Point* aux, int lo, int hi)    {
    if(hi <= lo)
    	 return numeric_limits<double>::infinity();

    int mid = lo + (hi - lo)/2;
    double delta =  Closest_pair_points_process(pointsByX, pointsByY, aux, lo, mid);
    double dist =  Closest_pair_points_process(pointsByX, pointsByY, aux, mid+1, hi);
    if(dist < delta)
        delta = dist;

    merge(pointsByY, aux, lo, mid, hi);

    int M = 0, i, j;
    for(i = lo; i <= hi; i++)
        if(abs(pointsByY[i].x - pointsByX[mid].x) < delta)
            aux[M++] = pointsByY[i];

    double distance, t;
    for(i = 0; i < M; i++)  {
        for(j = i+1; j < M && (aux[j].y - aux[i].y < delta); j++) {
            distance = aux[i].dist(aux[j]);
            if(distance < delta)    {
                delta = distance;
                if(delta < best_distance_pair) {
                	best_distance_pair = delta;
                    global_point1 = aux[i];
                    global_point2 = aux[j];
                }
            }
        }
    }
    return delta;
}

/**
 * Closest pair of tho points of a given vector of points
 * Returns : pair< double, pair<Point,Point> > the first element is the distance
 * the second elements are the points.
 * */
 pair< double, pair<Point,Point> > Closest_pair_points(vector<Point> points)
 {
 	int N = points.size();
 	Point P[N], pointsByY[N], aux[N];

 	for(int i = 0 ; i < N; i++)
 		P[i] = points[i];
 	sort(P, P + N, comparison_X);
        for(int i=0; i<N; i++)
            pointsByY[i] = P[i];

    best_distance_pair = numeric_limits<double>::infinity();
    Closest_pair_points_process(P,pointsByY,aux,0,points.size()-1);
    return make_pair(best_distance_pair, make_pair(global_point1,global_point2));
 }








