#include <bits/stdc++.h>
#include <string>
#include <sstream>
using namespace std;

int main(){
    double input;
    int num;
    int ctr = 0;
    string line;

    while(getline(cin,line)){
        ctr = 0;
        // cout<<line<<endl;
        if(line.compare("END")==0)
            return 0;
        istringstream iss(line);
        iss>>input;
        if(input == 0 || input == 1){
            cout<<"MEMBER"<<endl;
        }else{
            while(input >=0 && input <=1){
                input *= 3;
                num = (int)input;
                if(num == 1){
                    cout<<"NON-MEMBER"<<endl;
                }else{
                    input -= num;
                }
                if(ctr++>20){
                    cout<<"MEMBER"<<endl;
                    break;
                }
    
            }
        }
    }


}