#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN=5000+10;

struct node
{
	int w, h, idx;
	bool operator < (const node &t) const
	{
		if (this->w==t.w) return (this->h<t.h);
		else return (this->w<t.w);
	}
};

node blk[MAXN];
int pre[MAXN];
int dp[MAXN];

int main()
{
	int n;
	scanf("%d", &n);
	for (int i=0; i<=n; i++)
	{
		scanf("%d%d", &blk[i].w, &blk[i].h);
		blk[i].idx=i;
	}
	sort(blk, blk+1+n);
	memset(pre, -1, sizeof(pre));
	for (int i=n; i>=0; i--)
	{
		dp[i]=1;
		for (int j=i+1; j<=n; j++)
			if (blk[i].w<blk[j].w&&blk[i].h<blk[j].h)
			{
				if (dp[i]<dp[j]+1) dp[i]=dp[j]+1, pre[i]=j;
			}
	}
	int pos;
	for (int i=0; i<=n; i++)
		if (blk[i].idx==0) pos=i;
	printf("%d\n", dp[pos]-1);
	if (dp[pos]>1)
	{
		bool first=true;
		while (pre[pos]!=-1)
		{
			if (!first) putchar(' ');
			printf("%d", blk[pre[pos]].idx);
			pos=pre[pos]; first=false;
		}
		puts("");
	}
	return 0;
}
