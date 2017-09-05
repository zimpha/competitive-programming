#include <set>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int dx[]={0, 0, 1, -1};
const int dy[]={1, -1, 0, 0};
const int MAXN=105;

set<char> S;
char map[MAXN][MAXN];
char boss;
int n, m;

int main()
{
	S.clear();
	scanf("%d%d %c", &n, &m, &boss);
	for (int i=0; i<n; i++) scanf("%s", map[i]);
	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++)
		{
			if (map[i][j]!=boss) continue;
			for (int k=0; k<4; k++)
			{
				int x=i+dx[k], y=j+dy[k];
				if (x<0||y<0||x>=n||y>=m) continue;
				if (map[x][y]==boss||map[x][y]=='.') continue;
				if (S.count(map[x][y])) continue;
				S.insert(map[x][y]);
			}
		}
	printf("%d\n", (int)S.size());
	return 0;
}
