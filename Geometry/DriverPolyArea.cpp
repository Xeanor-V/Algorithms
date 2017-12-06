#include "Geometry.hpp"

using namespace std;


int main(){
    int test,count;
    cin>>test;
    while(test!=0){
        if(test==0)
            break;

        count = test;
        vector<point> polygon(count);
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
}