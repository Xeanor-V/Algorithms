/**
 * Coordinate Geometry Headers
 * Authors
 * David Vega and Rohin Mohanadas
 * */

// #include <bits/stdc++.h>

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip> 

const double ERROR = 1e-9;
#define PI 3.14159265

using namespace std;

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
    double magnitude() { return hypot(x,y); }
    double dot(const Point p) { return x*p.x + y*p.y; }
    double cross(const Point p) { return x*p.y-p.x*y; }
    double dist(const Point p) { return(sqrt( (*this-p).dot(*this-p))); }
    double angle() { return atan2(y,x) * 180/M_PI; }
    bool operator<(const Point cmp) const {
        if (!Equal(x, cmp.x)) return x < cmp.x;
        return Equal(y, cmp.y)? false: y < cmp.y;
    }
    bool operator==(const Point& cmp) {
    return Equal(x, cmp.x) && Equal(y, cmp.y);
    } 
};

// Angulo entre vectores v y w.
// double Angulo(Point v, Point w) {
//     return acos(v.dot(w) / (v.magnitude() * w.magnitude()));
// }

// translate p tomando como origen al Point o .
Point translate(Point o, Point p) {
    return p-o;
}

// Test de mano derecha: CCW = 1, CW = -1, Colineal = 0.
// int orientation( Point o,  Point p,  Point q) {
//     double ccw = translate(o, p).cross(translate(o, q) ) ;
//     return Equal(ccw, 0)? 0: (ccw < 0)? -1: 1;
// }



// Saber si un Point esta en el perimetro de un poligono.
// bool onPolygon( Point p,  vector<Point>  P) {
//     for (int i = 1; i < P.size(); ++i) {
//         Point l = min(P[i - 1], P[i]);
//         Point r = max(P[i - 1], P[i]);
//         if (orientation(l, r, p) == 0 &&
//             !(p < l || r < p)) return true;
//     }
//     return false;
// }




/**
 * Takes in a vector of ordered points of a polygon given in either clockwise / counter clockwise direction
 * Returns the area of the polygon ( -ve value for CW point vector and +ve for CCW)
 * */
double polygon_area(vector<Point> polygon){
        double area= 0;
        for(int i=0;i<polygon.size();i++){
            area+= polygon[i].cross(polygon[(i+1)%polygon.size()]);
        }
        area = area/2; 
        return area;
}

void print(Point p){
    cout<<"x : "<<p.x<<" and y: "<<p.y<<"\n";
}

bool segments_parallel(Point a, Point b, Point c, Point d){ // if (a,b) || (c,d)
    return abs((a-b).cross(c-d)) < ERROR; // sin(x) = 0
}

bool point_on_segment(Point p, Point a, Point b){ // p belongs to [a,b] or not
    if (p.dist(a) < ERROR) return true;
    if (p.dist(b) < ERROR) return true;
    if (segments_parallel(p,a,p,b) && (p-a).dot(p-b) < 0) return true; // to check
    return false;
}

bool point_on_polygon(Point p, const vector<Point> &a){
    for (int i=0;i<a.size();i++)
        if (point_on_segment(p,a[i],a[(i+1)%a.size()]))
            return true;
    return false;
}

int pointandpoly( Point p,  vector<Point> P) {
    if (point_on_polygon(p, P)) return -1;
    bool result = false;
    int j = P.size()-1;
    for(int i=0;i<P.size();i++){
         if( ( (P[i].y > p.y) != (P[j].y > p.y) ) && (p.x < P[i].x + (P[j].x - P[i].x)*(p.y - P[i].y)/( P[j].y - P[i].y)))
            result = !result;
        j = i;
    }
    return result? 1:0;
}

// int AngleSummation(const point p, const vector<point> P) {
//     if (point_on_polygon(p, P)) return -1;
//     double angulo = 0;
//     for (int i = 1; i < P.size(); ++i)
//         angulo += orientation(p, P[i - 1], P[i]) * Angulo(
//             translate(p, P[i - 1]), translate(p, P[i]));
//     return (fabs(angulo) > M_PI)? 1: 0;
// }


        // if ((poly[i][1] > y) != (poly[j][1] > y)) and \
        //         (x < poly[i][0] + (poly[j][0] - poly[i][0]) * (y - poly[i][1]) /
        //                           (poly[j][1] - poly[i][1])):