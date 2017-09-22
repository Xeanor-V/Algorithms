//Authors: David Vega Ramirez / Rohin Mohanadas
//Implementation of interval res.
#include <bits/stdc++.h>
using namespace std;


template<typename Type>
void Print_Vector(vector<Type> vec)
{
	for(int i = 0; i < vec.size(); i++)
	{
		if(i) cout<<' ';
		cout<<vec[i];
	}
	cout<<'\n';
}

// Struct range for convenience 
struct Range{
	double L,R;
	int index;
	Range(double l,double r,int idx):
	L(l),R(r),index(idx){}
	//custom sort
	bool operator < (const Range& i) const 
	{ 
		return (R < i.R); 
	}
};

double getDelta(double x, double y)
{
	return abs(x-y);
}


vector<int> getCover(double L, double R, vector<Range> ranges)
{
	vector <int> res;
	vector <int> trash;
	sort(ranges.begin(), ranges.end()) ;
	double point = L;
	int last = ranges.size() - 1;
	double delta = getDelta(L,R);
	bool same = delta<1e-9?true:false;
	while(point < R)
	{
		int index = -1;
		for(int i = ranges.size()-1; i>=0; i--)
		{
			//Check if we can res the interval or that segment is not worth it
			if(ranges[i].L > point) continue;
			if(ranges[i].R < point) return trash;
			index = i;
			point = ranges[i].R; 
			break;
		}
		if(index != -1)
		{
			//Add to the results and check if we only need one
			res.push_back(ranges[index].index);
			ranges.erase(ranges.begin() + index);
		}
		else
		{
			return trash;	
		}
		if(same) break;
	}
	if (point < R) return trash;
	return res;
}



int main()
{
	double L,R;
	int n;
	while(cin>>L>>R)
	{
		cin>>n;
		vector< Range > ranges;
		for(int i = 0 ; i < n; i++ )
		{
			double x,y;
			cin>>x>>y;
			ranges.push_back(Range(x,y,i));
		}
		vector <int> res = getCover(L,R,ranges);
		if(res.size() == 0) cout<<"impossible\n";
		else{
			cout<<res.size()<<'\n';
			for(int i = 0 ; i < res.size(); i++)
			{
				if(i) cout<<' ';
				cout<<res[i];
			}
			cout<<'\n';
		}
	}
	//Print_Vector(res);
}


/*

double L,R;
    while(cin>>L>>R)
    {
        int N;
        cin>>N;
        vector <double> Right;
        vector < pair<double,int> > LToIndex;
        for(int i = 0 ; i < N; i++)
        {
            double x,y;
            cin>>x>>y;
            x = x<L?L:x;
            y = y>R?R:y;
            Right.push_back(y);
            LToIndex.push_back( make_pair(x,i) );
        } 
        sort(LToIndex.begin(), LToIndex.end());

        pair<double, double> res;

        res.first = LToIndex[0].first;
        res.second = Right[LToIndex[0].second];

        vector<int>res;
        int size = 1;
        res.push_back(LToIndex[0].second);
        for(int i = 1; i < N; i++)
        {
            int Index = LToIndex[i].second;
            double delta = abs(LToIndex[i].first - res.first);
            if( delta <= 0.0000000000001 && Right[Index] >= res.second)
            {
                res.clear();
                res.second = Right[Index];
                res.push_back(Index);
                size = 1;
            }
            else if(LToIndex[i].first > res.first && LToIndex[i].first <= res.second && Right[Index] > res.second )
            {
                res.push_back(Index);
                res.second = Right[Index];
                size++;
            }        
        }

        double delta1 = abs(res.first - L), delta2 = abs(res.second - R);
        //cout<<delta1<<'-'<<delta2<<endl;
        if(delta1 > 0.0000000000001 || delta2 > 0.0000000000001 ) cout<<"impossible\n";
        else
        {
            //cout<<res.first<<' '<<res.second<<'\n';

            cout<<res.size()<<'\n';
            for(int i = 0 ; i < size; i++)
            {
                if(i) cout<<' ';
                cout<<res[i];
            }
            cout<<'\n'; 
        }
	}
	*/