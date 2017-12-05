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

#define PI 3.14159265

using namespace std;

struct point{
    double x;
    double y;
    point(double x=0.0, double y=0.0): x(x),y(y){}
    point operator+(const point p) { return point(x+p.x,y+p.y); }
    point operator-(const point p) { return point(x-p.x,y-p.y); }
    point operator*(const double v) { return point(x*v,y*v); }
    double dot(const point p) { return x*p.x + y*p.y; }
    double cross(const point p) { return x*p.y-p.x*y; }
    double dist(const point p) { return(sqrt( (*this-p).dot(*this-p))); }
    double angle() { return atan2(y,x) * 180/PI; }
};
/**
 * Takes in a vector of ordered points of a polygon given in either clockwise / counter clockwise direction
 * Returns the area of the polygon ( -ve value for CW point vector and +ve for CCW)
 * */
double polygon_area(vector<point> polygon){
        double area= 0;
        for(int i=0;i<polygon.size();i++){
            area+= polygon[i].cross(polygon[(i+1)%polygon.size()]);
        }
        area = area/2; 
        return area;
}