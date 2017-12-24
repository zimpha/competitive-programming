#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
using namespace std;
#define REP(i, n) for(int i=0; i<int(n); i++)
#define pb(x) push_back(x)
#define mp(a, b) make_pair(a, b)
typedef long long LL;
typedef vector<int> vi;
#define MAXN 100
#define MOD 1000000007
#define eps 1e-8
int sgn(double x){
	if(fabs(x)<eps)return 0;
	else return x>0?1:-1;
}
int main()
{
	int n;
	double p, q;
	int tt=0;
	while(scanf("%d%lf", &n, &p)==2){
		double ans=0;
		q=1-p;
		if(sgn(p)==0||sgn(q)==0){
			ans=n;
			printf("Case %d: %.6lf\n",++tt, 0.0);
			continue;
		}
		double C=1;
		int cnt=n;
		for(int i=n; i<2*n; i++){
			double t=(2*n-i)*C;
			while(t>1e10){
				t*=p;
				C*=p;
				ans*=p;
				cnt--;
			}
			if(t<1e-14)break;
			ans+=t;
			C*=q;
			C*=i+1;
			C/=i-n+1;
		}
		for(int i=0; i<=cnt; i++)
			ans*=p;
		swap(p, q);
		double ans2=0;
		C=1;
		cnt=n;
		for(int i=n; i<2*n; i++){
			double t=(2*n-i)*C;
			while(t>1e10){
				t*=p;
				C*=p;
				ans2*=p;
				cnt--;
			}
			if(t<1e-14)break;
			ans2+=t;
			C*=q;
			C*=i+1;
			C/=i-n+1;
		}
		for(int i=0; i<=cnt; i++)
			ans2*=p;
		printf("Case %d: %.6lf\n", ++tt, ans+ans2);
	}

}
