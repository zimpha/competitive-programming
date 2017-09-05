#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

int sx, sy, ex, ey;

int main()
{
	char ss[10];
	scanf("%s", ss); sx=ss[0]-'a'; sy=ss[1]-'0';
	scanf("%s", ss); ex=ss[0]-'a'; ey=ss[1]-'0';
	int n1=min(abs(sx-ex), abs(sy-ey));
	int n2=max(abs(sx-ex), abs(sy-ey));
	printf("%d\n", n2);
	for (int i=0; i<n1; i++)
	{
		if (sx<ex) sx++, putchar('R');
		else sx--, putchar('L');
		if (sy<ey) sy++, putchar('U');
		else sy--, putchar('D');
		puts("");
	}
	for (int i=0; i<n2-n1; i++)
	{
		if (sx<ex) sx++, putchar('R');
		else if (sx>ex) sx--, putchar('L');
		if (sy<ey) sy++, putchar('U');
		else if (sy>ey) sy--, putchar('D');
		puts("");
	}
	return 0;
}
