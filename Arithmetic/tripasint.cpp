#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
using namespace std;

int main(){
    int members;

    while(1){
        cin>>members;
        cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' ); 
        // cin>>ws;
        // cout<<members<<endl;
        if(members==0){
            break;
        }else{
            // double temp;
            string line;
            // fflush(stdin);
            int costs[members] = {0};
            int sum = 0;
            int i = 0;
            int k;
            while(i<members){
                // cin>>temp;
                getline(cin,line);
                int length = line.find(".");
                // cout<<temp;
                for( k = 0;k<length;k++){
                    costs[i] = costs[i]*10 + line[k] - '0';
                }
                for(int j = 0 ;j<2;j++){
                    costs[i] = costs[i]*10 + line[k+j+1] - '0';
                }
                sum+=costs[i];
                //cout<<costs[i]<<endl;
                i++;
            }
            // cout<<"sum is "<<sum;
            double perhead = sum / (double) members ;
            double actualPerhead = perhead;
            perhead = round(perhead);
            // cout<<"perhead "<<perhead<<" actualPerhead "<<actualPerhead<<endl;
            // if(perhead!=actualPerhead){
            //     cout<<"perhead "<<perhead<<" actualPerhead "<<actualPerhead<<endl;
            // }

            double half = 2.0d;
            i = 0;
            double exchange = 0.0d;
            while(i<members){
//cout<<"delta "<<perhead - costs[i]<<endl;
                exchange += fabs(perhead - costs[i++]);
                //cout<<"exchange "<<exchange<<endl;
            }
            if(perhead > actualPerhead)
                exchange = exchange + (actualPerhead-perhead)*members;
            else
                exchange = exchange + (perhead - actualPerhead)*members;
            // cout<<"exchange: "<<exchange<<endl;
            cout<<"$"<<setprecision(2)<<fixed<<exchange/(half*100)<<endl;
        }
    }
    // cout<<(double)15.01-(double)9.0<<endl;
}