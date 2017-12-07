#include "Geometry.hpp"

using namespace std;

int main(){

    int test;
    cin>>test;
    while(test--){
        cout<<fixed;
        cout<<setprecision(2);
        vector<Point> input(4);
        cin>>input[0].x>>input[0].y>>input[1].x>>input[1].y>>input[2].x>>input[2].y>>input[3].x>>input[3].y;
        cout<<segment_distance(input[0],input[1],input[2],input[3])<<"\n";
    }
}