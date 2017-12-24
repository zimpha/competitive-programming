#include <cstdio>
#include <cstring>

const int SIZE=10000;
const int MAXN=105;

bool C[SIZE];
int F[MAXN];
int N, M;

int main()
{
	memset(C, 0, sizeof(C));
	scanf("%d", &N);
	for (int i=1; i<=N; i++)
	{
		scanf("%d%d", &F[i], &M);
		for (int x, j=1; j<=M; j++)
		{
			scanf("%d", &x);
			C[x]=true;
		}
	}
	for (int i=1; i<=N; i++) C[F[i]]=false;
	int ret=0;
	for (int i=0; i<SIZE; i++) ret+=C[i];
	printf("%d\n", ret);
}
