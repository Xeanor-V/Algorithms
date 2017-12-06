#include "coordinate.hpp"

using namespace std;

int main(){
    int test,i;
    cin>>test;
    // i = test;
    while(test!=0){
        if(test==0)
            break;
        vector<point> polygon(test);
        for(int j = 0; j<test;j++){
            cin>>polygon[j].x>>polygon[j].y;
        }
         //cout<<"Polygon siize"<<polygon.size()<<"\n";
        // for(int j = 0; j<test;j++){
        //     cout<<polygon[j].x<<" "<<polygon[j].y<<"\n";
        // }        
        int points;
        cin>>points;
        while(points--){
            point p;
            cin>>p.x>>p.y;
            switch(pointandpoly(p,polygon)){
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