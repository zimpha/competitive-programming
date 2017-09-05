#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN=1005;

int dp2[MAXN][MAXN], dp5[MAXN][MAXN];
int nu2[MAXN][MAXN], nu5[MAXN][MAXN];
int n, tx, ty;

inline int cost(int n, int p)
{
	int ret;
	if (n==0) return 1;
	for (ret=0; n%p==0; n/=p, ret++);
	return ret;
}

void solve(int dp[][MAXN], int num[][MAXN])
{
	dp[0][0]=num[0][0];
	for (int i=1; i<n; i++) dp[0][i]=dp[0][i-1]+num[0][i];
	for (int i=1; i<n; i++)
		for (int j=0; j<n; j++)
		{
			if (j==0) dp[i][j]=dp[i-1][j]+num[i][j];
			else dp[i][j]=min(dp[i-1][j], dp[i][j-1])+num[i][j];
		}
}

int print(int dp[][MAXN], int num[][MAXN], int x, int y)
{
	if (x>0&&dp[x][y]==dp[x-1][y]+num[x][y])
	{
		print(dp, num, x-1, y);
		putchar('D');
	}
	else if (y>0&&dp[x][y]==dp[x][y-1]+num[x][y])
	{
		print(dp, num, x, y-1);
		putchar('R');
	}
	return 0;
}

int main()
{
	scanf("%d", &n); 
	tx=-1; ty=-1;
	for (int i=0; i<n; i++)
		for (int x, j=0; j<n; j++)
		{
			scanf("%d", &x);
			nu2[i][j]=cost(x, 2); nu5[i][j]=cost(x, 5);
			if (x==0) tx=i, ty=j;
		}
	solve(dp2, nu2);
	solve(dp5, nu5);
	if (tx==-1)
	{
		printf("%d\n", min(dp2[n-1][n-1], dp5[n-1][n-1]));
		if (dp2[n-1][n-1]>dp5[n-1][n-1]) print(dp5, nu5, n-1, n-1);
		else print(dp2, nu2, n-1, n-1);
	}
	else
	{
		if (dp2[n-1][n-1]==0) puts("0"), print(dp2, nu2, n-1, n-1);
		else if (dp5[n-1][n-1]==0) puts("0"), print(dp5, nu5, n-1, n-1);
		else
		{
			puts("1");
			for (int i=0; i<tx; i++) putchar('D');
			for (int i=0; i<n-1; i++) putchar('R');
			for (int i=tx; i<n-1; i++) putchar('D');
		}
	}
	puts("");
	return 0;
}
