#include <cstdio>
#include <cstring>

int main()
{
	int w;
	scanf("%d", &w);
	if ((w&1)||w<=2) puts("NO");
	else puts("YES");
	return 0;
}
