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
    bool operator<(const Point& cmp) {
        if (!Equal(x, cmp.x)) return x < cmp.x;
        return Equal(y, cmp.y)? false: y < cmp.y;
    }
    bool operator==(const Point& cmp) {
        return Equal(x, cmp.x) && Equal(y, cmp.y);
    } 
    double dot(const Point p) { return x*p.x + y*p.y; }
    double cross(const Point p) { return x*p.y-p.x*y; }
    double dist(const Point p) { return(sqrt( (*this-p).dot(*this-p))); }
    double angle() { return atan2(y,x) * 180/M_PI; }
};

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

/**
 * Line definition by two points.
 * */
struct Line {
    Point p, q;
    //Long a, b, c; // <comment/>
    double a, b, c; // <uncomment/>

    Line() : p(), q(), a(), b(), c() {}

    Line(Long A, Long B, Long C)
        : p(), q(), a(A), b(B), c(C) {
        if (Equal(a, 0)) {
            c /= -b; b = -1;
            p = Point(0, c);
            q = Point(1, c);
        } else if (Equal(b, 0)) {
            c /= -a; a = -1;
            p = Point(c, 0);
            q = Point(c, 1);
        } else {
            p = Point(-c/a, 0);
            q = Point(-(b+c)/a, 1);
        } if (q < p) swap(p, q);
    }

    Line(const Point& P, const Point& Q)
        : p(P), q(Q), a(), b(), c() {
        // Asegura p como Point menor.
        if (q < p) swap(p, q);
        a = q.y - p.y;
        b = p.x - q.x;
        if (!a) c = p.y, b = -1;
        else if (!b) c = p.x, a = -1;
        else {
            /* <comment>
            c = abs(__gcd(a, b));
            a /= c, b /= c;
            // </comment>*/
            c = -a*p.x - b*p.y;
        }
    }

    // ¡PELIGRO! Ordena por ecuacion de recta.
    bool operator<(const Line& cmp) const {
        if (!Equal(a, cmp.a)) return a < cmp.a;
        if (!Equal(b, cmp.b)) return b < cmp.b;
        return Equal(c, cmp.c)? false: c < cmp.c;
    }
};