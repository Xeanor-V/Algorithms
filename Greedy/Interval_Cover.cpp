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


struct Range{
	double L,R;
	int index;
	Range(double l,double r,int idx):
	L(l),R(r),index(idx){}
	bool operator < (const Range& i) const 
	{ 
		return (L < i.L); 
	}
};

double getDelta(double x, double y)
{
	return abs(x-y);
}


vector <int> getCover(double L, double R, vector<Range> ranges)
{
	double epsilon = 1e-9;
	for(int i = 0 ; i < ranges.size(); i++)
	{
		ranges[i].L = ranges[i].L<L?L:ranges[i].L;
		ranges[i].R = ranges[i].R>R?R:ranges[i].R;
	}
	sort(ranges.begin(), ranges.end());
	pair<double,double> cover;
	cover.first = ranges[0].L;
	cover.second = ranges[0].R;
	double delta = getDelta(R,cover.second);
	vector <int> res;
	res.push_back(ranges[0].index);
	bool noCover = false;
	int last = 1;
	while(delta > epsilon )
	{
		noCover = true;
		for(int i = last ; i < last; i++)
		{
			if(getDelta(ranges[i].L,cover.first) < epsilon && ranges[i].R > cover.second)
			{
				res.clear();
				res.push_back(ranges[i].index);
				cover.second = ranges[i].R;
				last = i + 1;
				noCover = false;
				break;
			}
		}
		if(noCover) break;
	}
	delta = getDelta(R,cover.second);
	Print_Vector(res);
	return vector<int>();
}



int main()
{
	double L,R;
	int n;
	cin>>L>>R;
	cin>>n;
	vector< Range > ranges;
	for(int i = 0 ; i < n; i++ )
	{
		double x,y;
		cin>>x>>y;
		ranges.push_back(Range(x,y,i));
	}
	
	getCover(L,R,ranges);
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

        pair<double, double> cover;

        cover.first = LToIndex[0].first;
        cover.second = Right[LToIndex[0].second];

        vector<int>res;
        int size = 1;
        res.push_back(LToIndex[0].second);
        for(int i = 1; i < N; i++)
        {
            int Index = LToIndex[i].second;
            double delta = abs(LToIndex[i].first - cover.first);
            if( delta <= 0.0000000000001 && Right[Index] >= cover.second)
            {
                res.clear();
                cover.second = Right[Index];
                res.push_back(Index);
                size = 1;
            }
            else if(LToIndex[i].first > cover.first && LToIndex[i].first <= cover.second && Right[Index] > cover.second )
            {
                res.push_back(Index);
                cover.second = Right[Index];
                size++;
            }        
        }

        double delta1 = abs(cover.first - L), delta2 = abs(cover.second - R);
        //cout<<delta1<<'-'<<delta2<<endl;
        if(delta1 > 0.0000000000001 || delta2 > 0.0000000000001 ) cout<<"impossible\n";
        else
        {
            //cout<<cover.first<<' '<<cover.second<<'\n';

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