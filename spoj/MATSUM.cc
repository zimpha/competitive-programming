#include <cstdio>
#include <cstring>

const int MAXN=1050;

int C[MAXN][MAXN];
int A[MAXN][MAXN];
int N;

inline int lowbit(int x)
{
	return (x&-x);
}

void add(int x0, int y0, int d)
{
	for (int x=x0; x<=N; x+=lowbit(x))
		for (int y=y0; y<=N; y+=lowbit(y))
			C[x][y]+=d;
}

int getsum(int x0, int y0)
{
	int ret=0;
	for (int x=x0; x>0; x-=lowbit(x))
		for (int y=y0; y>0; y-=lowbit(y))
			ret+=C[x][y];
	return ret;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);
		memset(C, 0, sizeof(C));
		memset(A, 0, sizeof(A));
		char str[10];
		while (scanf("%s", str)==1&&str[0]!='E')
		{
			int x1, y1, x2, y2, v;
			scanf("%d%d", &x1, &y1);
			if (str[1]=='E')
			{
				x1++, y1++;
				scanf("%d", &v);
				int a=A[x1][y1];
				A[x1][y1]=v; v-=a;
				add(x1, y1, v);
			}
			else
			{
				scanf("%d%d", &x2, &y2);
				x2++, y2++;
				printf("%d\n", getsum(x2, y2)-getsum(x2, y1)-getsum(x1, y2)+getsum(x1, y1));
			}
		}
		puts("");
	}
	return 0;
}
