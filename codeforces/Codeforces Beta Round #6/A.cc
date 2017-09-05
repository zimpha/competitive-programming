#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

int len[4], a[4];
int flag;

void dfs(int dep, int cur)
{
	if (dep==3)
	{
		if (a[0]+a[1]>a[2]) flag=1;
		else if (a[0]+a[1]==a[2]&&flag==-1) flag=0;
		return;
	}
	for (int i=cur; i<4; i++)
	{
		a[dep]=len[i];
		dfs(dep+1, i+1);
	}
}

int main()
{
	for (int i=0; i<4; i++) scanf("%d", len+i);
	sort(len, len+4);
	flag=-1;
	dfs(0, 0);
	if (flag==1) puts("TRIANGLE");
	else if (flag==0) puts("SEGMENT");
	else puts("IMPOSSIBLE");
	return 0;
}
