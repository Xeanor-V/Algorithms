#include "Geometry.hpp"

using namespace std;

/* Polygon Area
int main(){
    int test,count;
    cin>>test;
    while(test!=0){
        if(test==0)
            break;

        count = test;
        vector<Point> polygon(count);
        int i = 0;
        while(count--){
            cin>>polygon[i].x>>polygon[i].y;
            i++;
        }
        double area = polygon_area(polygon);
        
        cout<<fixed;
        cout<<setprecision(1);
        
        if(area<0){
            cout<<"CW "<<abs(area)<<"\n";
        }else{
            cout<<"CCW "<<abs(area)<<"\n";
        }
        cin>>test;
    }
} //*/

/* Convex Hull 
int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    while(cin>>n)
    {
        if(n == 0) break;
        vector<Point> poly,res;
        for(int i = 0 ; i < n ; i++)
        {
            double x,y;
            cin>>x>>y;
            poly.push_back(Point(x,y));
        }
        res = ConvexHull(poly);
        if(  res.size() == 1  ||  ( (res.size()-1) == 2 && res[0] == res[1]) )
        {
            cout<<1<<'\n';
            cout<<res[0].x<<' '<<res[0].y<<'\n';
            continue;
        }
        cout<<res.size()-1<<'\n';
        for(int i = 0; i < res.size()-1; i++)
        {
            cout<<res[i].x<<' '<<res[i].y<<'\n';
        }
    }
    return 0;
}
// */


///* closest Pair of points
int main()
{
    //cin.tie(0);
    //ios_base::sync_with_stdio(0);
    int n;
    while(cin>>n)
    {
        if(n == 0) break;
        vector<Point> points(n);
        for(int i = 0 ; i < n; i++)
        {
            double x,y;
            scanf("%lf %lf", &x, &y);
            points[i] = Point(x,y);
        }
        if(n <= 1) return 0;
        pair<double, pair< Point, Point> > res = Closest_pair_points(points);
        printf("%lf %lf ", res.second.second.x, res.second.second.y);
        printf("%lf %lf\n", res.second.first.x, res.second.first.y);

    }
    return 0;
}