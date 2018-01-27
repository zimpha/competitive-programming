#include<bits/stdc++.h>
#define st first
#define nd second

using namespace std;

const double pi = acos(-1.0);

typedef long long ll;
typedef pair<int, int> PII;

const int MM = 1e9 + 7;
const double eps = 1e-8;
const int N = 1e7 + 10;

int n, m;

int v[N],l[N],r[N],R[N],L[N],size[N],tot[N],root[N],d[N];  
int merge(int x,int y)  
{  
    if (!x) return y;  
    if (!y) return x;  
    if (v[x]<v[y]) swap(x,y);  
    R[x]=merge(R[x],y);  
    size[x]=size[L[x]]+size[R[x]]+1;  
    if (d[L[x]]<=d[R[x]])  swap(L[x],R[x]);  
    d[x]=d[R[x]]+1;  
    return x;  
}  

int main(){
	vector<int> a;
  const double eps = 1e-8;
	for (int i = -1000000; i <= 1000000; i++){
		long double tmp = sqrt(abs(i)) * sinl(fmod(i, pi * 2)) + abs(i);
    if (i == 0) a.push_back(0);
    else if (tmp >= 0) a.push_back(floor(tmp+eps));
		else a.push_back(floor(tmp+eps) - 1);
	}
	for (int i = -100000; i <= 100000; i++){
		long double tmp = sqrt(abs(i)) * sinl(fmod(i, pi * 2)) - abs(i);
    if (i == 0) a.push_back(0);
    else if (tmp >= 0) a.push_back(floor(tmp+eps));
		else a.push_back(floor(tmp+eps) - 1);
	}
  std::reverse(a.begin(), a.end());
	int n = a.size();
	for (int i = 1; i <= n; i++){
		v[i] = a[i - 1] - i;
	}
    int now=0;  
    for (int i=1;i<=n;i++)  
     {  
        now++;  
        root[now]=i;   
        l[now]=r[now]=i; //所控制区间的左右端点  
        tot[now]=1;//当前堆维护的中位数控制的数的个数  
        size[root[now]]=1;//堆中元素的个数  
        while (now>1&&v[root[now-1]]>v[root[now]])  
         {  
            now--;  
            r[now]=r[now+1]; tot[now]+=tot[now+1];  
            root[now]=merge(root[now],root[now+1]);  
            while (size[root[now]]*2>tot[now]+1)//保证堆顶元素是当前区间的中位数  
             root[now]=merge(L[root[now]],R[root[now]]);  
         }  
     }  
    long long ans=0;  
    for (int i=1;i<=now;i++)  
     for (int j=l[i];j<=r[i];j++)   
      ans+=(long long)abs(v[j]-v[root[i]]);  
    printf("%lld\n",ans);  
	return 0;
}
