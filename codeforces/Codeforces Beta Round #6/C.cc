#include <cstdio>
#include <cstring>

const int MAXN=100000+10;

int t[MAXN];
int n;

int main()
{
	scanf("%d", &n);
	int a=0, b=n-1, ta=0, tb=0;
	for (int i=0; i<n; i++) scanf("%d", &t[i]);
	while (a<=b)
	{
		if (a==b)
		{
			if (ta<=tb) ta+=t[a], a++;
			else if (ta>tb) tb+=t[b], b--;
			break;
		}
		while (a<b&&ta<=tb) ta+=t[a], a++;
		while (a<b&&tb<=ta) tb+=t[b], b--;
	}
	printf("%d %d\n", a, n-a);
	return 0;
}
