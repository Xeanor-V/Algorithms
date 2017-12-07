#include "Geometry.hpp"

using namespace std;

int main(){
    int test,i;
    cin>>test;

    while(test!=0){
        if(test==0)
            break;
        vector<Point> polygon(test);
        for(int j = 0; j<test;j++){
            cin>>polygon[j].x>>polygon[j].y;
        }      
        int points;
        
        cin>>points;

        while(points--){
            Point p;
            cin>>p.x>>p.y;
            switch(point_inside_polygon(p,polygon)){
                case 0: cout<<"out\n";
                break;
                case 1: cout<<"in\n";
                break;
                case -1: cout<<"on\n";
                break;
            }
        }
        cin>>test;
    }
}