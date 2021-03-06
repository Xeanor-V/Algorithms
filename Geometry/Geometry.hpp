/**
 * 
 * Geometry Headers
 * Authors : David Vega and Rohin Mohanadas
 * 
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

};

/**
 * Right Hand method for determmining the orientation of two vectors
 * using 'o' as origin of vectors
 * CCW = 1, CW = -1, Colinear = 0.
 * */
int RightHand(Point o, Point p, Point q) {
    Point aux = p.Move(o);
    double ccw = p.Move(o).cross(q.Move(o));
    return Equal(ccw, 0)? 0: (ccw < 0)? -1: 1;
}


/* *
 * Check f line a-b is parallel to line c-d
 * */
bool parallel_segments(Point a, Point b, Point c, Point d){
    return abs((a-b).cross(c-d)) < ERROR;
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

/* *
 * Check if line segments intersect
 * Output : false if the line segments do not intersect
 *          true if the line segments intersect
 * */
bool segments_intersection(Point a, Point b, Point c, Point d){
    // Check if a or b are same as c or d
    if(a.dist(c)<ERROR || a.dist(d)<ERROR || b.dist(c)<ERROR || b.dist(d)<ERROR)
        return true;
    // Check if both line segments are points
    if(a.dist(b)<ERROR && b.dist(d)<ERROR)
        return false;
    // Check if either line segments are points and lie on the other
    if(a.dist(b)<ERROR)
        return point_on_segment(a,c,d);
    if(c.dist(d)<ERROR)
        return point_on_segment(c,a,b);
    // Parallel line segments cases
    // first check if all 4 points are collinear
    if(parallel_segments(a,b,c,d) && parallel_segments(a,c,b,d) && parallel_segments(a,d,c,b)){
        // yes, colliner now check overlap
        if((point_on_segment(a,c,d))||(point_on_segment(b,c,d))||(point_on_segment(c,a,b))||(point_on_segment(d,a,b)))
            return true;
        return false;
    }

    if((a-b).cross(a-c) * (a-b).cross(a-d) > 0)
        return false;
    if((c-d).cross(c-a) * (c-d).cross(c-b) > 0)
        return false;   

    return true; 
}

/**
 * 
 * Find the projection of point p onto line a-b ( onto the closest point)
 * if a perpendicular projection is not possible, return on of the two endpoints depending upon the distance
 * 
 * */
Point projection(Point p, Point a, Point b){
    if(a.dist(b)<ERROR){
        return a;
    }
    double result = (p-a).dot(b-a)/a.dist(b);
    if(result < 0) return a;
    if(result > a.dist(b)) return b;

    return a + (b-a) * (result/a.dist(b));
}

/**
 * Takes in a vector of ordered points of a polygon given in either clockwise / counter clockwise direction
 * Returns the area of the polygon ( -ve value for CW Point vector and +ve for CCW)
 * */
double polygon_area(vector<Point> polygon){
        double area= 0;
        for(int i=0;i<polygon.size();i++){
            area+= polygon[i].cross(polygon[(i+1)%polygon.size()]);
        }
        area = area/2; 
        return area;
}


/**
 * Checks if where a point p lies with respect to polygon P
 * Returns : -1 if p lies on the polygon
 * 0 if p lies outside the polygon and
 * 1 if p lies inside the polygon
 * 
 * Algorithm : Even–odd rule
 * */
int point_inside_polygon( Point p,  vector<Point> polygon) {
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
 * Returns : vector of points representing the polygon (Full polygon, last point is also the start)
 * */
vector<Point> ConvexHull(vector<Point> P){
    sort(P.begin(), P.end());
    vector<Point> Up, Down;
    for (int i = 0; i < P.size(); ++i) {
        while (Up.size() > 1) {
            int p = Up.size() - 1;
            // Allow colineals: <=
            if (RightHand(Up[p-1],Up[p], P[i]) < 0) break;
            Up.pop_back();
        }
        Up.push_back(P[i]);
    }
    Up.pop_back();
    for (int i = P.size() - 1; i >= 0; --i) {
        while (Down.size() > 1) {
            int p = Down.size() - 1;
            // Allow colineals: <=
            if (RightHand(Down[p - 1],Down[p], P[i]) < 0) break;
            Down.pop_back();
        }
        Down.push_back(P[i]);
    }
    Up.insert(Up.end(),
        Down.begin(), Down.end());

    if(  Up.size() == 1  ||  ( (Up.size()-1) == 2 && Up[0] == Up[1]) )
    {
        vector<Point> aux(2);
        aux[1] = aux[0] = Up[0];
        return aux;
    }
    return Up; // Convex hull.
}

/**
 * Helper methods for closest two pair of points.
 * Using globals for recursion.
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

/**
 * Input 4 points a, b, c, d ( which denote 2 line segments a-b and c-d)
 * Output the minimum distance between the 2 line segments
 * */
double segment_distance(Point a, Point b, Point c, Point d){
    if (segments_intersection(a,b,c,d)) 
        return 0.0f;  
    else {

        vector<double> D(4,DBL_MAX);
        Point p[4];
        // Find projection of each point onto the other line and find the minimum distance from the point to those projections
        p[0] = projection(a,c,d), p[1] = projection(b,c,d), p[2] = projection(c,a,b), p[3] = projection(d,a,b);

        D[0] = a.dist(p[0]);
        D[1] = b.dist(p[1]);
        D[2] = c.dist(p[2]);
        D[3] = d.dist(p[3]);

        vector<double>::iterator it = min_element(D.begin(),D.end());
        return *it;
    }   
}

/**
 * Maximum collinear finds the maximum number of collinear points (redundance?)
 * Returns : integer with the maximum number.
 * */
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







