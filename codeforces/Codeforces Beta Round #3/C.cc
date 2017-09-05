#include <cstdio>
#include <cstring>
#include <cstdlib>

char map[10][10];
int nx, no, fx, fo, turn;

bool check(char c)
{
	for (int i=0; i<3; i++)
	{
		if (map[i][0]==c&&map[i][1]==c&&map[i][2]==c) return true;
		if (map[0][i]==c&&map[1][i]==c&&map[2][i]==c) return true;
	}
	if (map[0][0]==c&&map[1][1]==c&&map[2][2]==c) return true;
	if (map[2][0]==c&&map[1][1]==c&&map[0][2]==c) return true;
	return false;
}

int main()
{
	nx=no=0;
	for (int i=0; i<3; i++)
	{
		scanf("%s", map[i]);
		for (int j=0; j<3; j++)
		{
			if (map[i][j]=='X') nx++;
			else if (map[i][j]=='0') no++;
		}
	}
	fx=check('X'); fo=check('0');
	if (nx==no||nx==(no+1))
	{
		if (fx&&fo) puts("illegal");
		else if (fx&&!fo)
			if (nx==no+1) puts("the first player won");
			else puts("illegal");
		else if (!fx&&fo)
			if (nx==no) puts("the second player won");
			else puts("illegal");
		else
		{
			if (nx+no==9) puts("draw");
			else if (nx==no) puts("first");
			else if (nx==no+1) puts("second");
		}
	}
	else puts("illegal");
	return 0;
}
