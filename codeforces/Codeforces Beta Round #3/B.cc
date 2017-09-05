#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN=100000+10;

struct node
{
	int idx, p, s;
	node(){}
	node(int _i, int _p):idx(_i),p(_p){}
	node(int _i, int _p, int _s):idx(_i),p(_p),s(_s){}
	bool operator<(const node &t) const {
		return this->p>t.p;
	}
};

node ve[2][MAXN];
int cnt[2];
int n, v, n1, n2;

int main()
{
	scanf("%d%d", &n, &v);
	cnt[0]=cnt[1]=0;
	ve[0][0]=node(0, 0, 0);
	ve[1][0]=node(0, 0, 0);
	for (int t, p, i=0; i<n; i++)
	{
		scanf("%d%d", &t, &p);
		cnt[t-1]++;
		ve[t-1][cnt[t-1]]=node(i+1, p);
	}
	sort(ve[0]+1, ve[0]+1+cnt[0]);
	sort(ve[1]+1, ve[1]+1+cnt[1]);
	for (int t=0; t<2; t++)
		for (int i=1; i<=cnt[t]; i++)
			ve[t][i].s=ve[t][i-1].s+ve[t][i].p;
	int ret=0, ans1, ans2;
	for (int i=0; i<=cnt[0]; i++)
	{
		if (i>v) break;
		int s2=min((v-i)/2, cnt[1]);
		int tmp=ve[0][i].s+ve[1][s2].s;
		if (tmp>ret) ret=tmp, ans1=i, ans2=s2;
	}
	printf("%d\n", ret);
	vector<int> S; S.clear();
	for (int i=1; i<=ans1; i++) S.push_back(ve[0][i].idx);
	for (int i=1; i<=ans2; i++) S.push_back(ve[1][i].idx);
	for (int i=0; i<S.size(); i++)
		printf("%d%c", S[i], (i==S.size()-1)?'\n':' ');
	return 0;
}
