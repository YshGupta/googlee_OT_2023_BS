#include<bits/stdc++.h>
using namespace std ;

const int pinf = INT_MAX ;
const int ninf = INT_MIN ;
#define pii pair<int,int>

bool ok( int mid , int n , int a[] , int b[] , int c[])
{
	int candec  = 0 , toinc = 0 ;
	for(int i =0 ; i < n ; i++)
	{
		if(a[i] < mid)
		{
			//have to inc to mid 
			toinc += ( mid - a[i]);
		}
		if( a[i] > mid)
		{
			//can dec 
			int ele = max( mid , b[i]);
			candec += ( a[i] - ele);
		}
	}
	if( candec >= toinc)return 1;
	return 0 ;
}

vector<int> solve( int n , int a[] , int b[] , int c[])
{
	//1. find the maximum possible minimum value

	int l = pinf , r = ninf;
	for(int i = 0 ; i < n ; i++)
	{
		l = min( l , a[i]);
		r = max( r , a[i]);
	}

	int value ;
	while( l <= r)
	{
		int mid = ( l+ r)/2;

		bool ans = ok( mid , n, a , b , c);
		if(ans)
		{
			value = mid ;
			l = mid + 1;
		}
		else
		{
			r = mid -1;
		}
	}

	//2. find the cost for this value
	set<pii>vals;
	for(int i =0 ; i < n ; i++)
	{	
		int last = max( value , b[i]);
		int cnt = a[i] - last ;
		if( cnt > 0 )
		{
			vals.insert({c[i] , cnt});
		}
	}

	//taking greedily 
	int cost = 0;
	int toincrease = 0;
	for(int i =0 ; i < n ; i++)
	{
		if(a[i] < value)toincrease++;
	}

	while(toincrease > 0 )
	{
		pii front = *vals.begin(); 
		int cantake = front.second ;
		cantake = min( toincrease , cantake);
		cost += ( cantake * front.first);
		toincrease -= cantake;
		if(front.second == cantake ){
			vals.erase(front);
		}
	}

	vector<int> ans = {value , cost};
	return ans ;

}

int main()
{
// #ifndef ONLINE_JUDGE
//     freopen("C:\\Users\\b2114\\OneDrive\\Desktop\\input.txt" , "r" , stdin);
//     freopen("C:\\Users\\b2114\\OneDrive\\Desktop\\output.txt", "w" , stdout);
// #endif
	int n ; cin>>n ;
	int a[n] , b[n] , c[n];
	for(int & i : a)cin>>i;
	for(int & i : b)cin>>i; 
	for(int & i : c)cin>>i;

	vector<int> ans = solve( n , a , b , c);
	cout<<ans[0] <<' '<<ans[1]<<endl;
	return 0 ;
}