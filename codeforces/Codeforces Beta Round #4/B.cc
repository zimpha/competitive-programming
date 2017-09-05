#include <cstdio>
#include <cstring>
#include <cstdlib>

int main()
{
	int d, sum;
	int mint[40], maxt[40];
	int days[40];
	scanf("%d%d", &d, &sum);
	for (int i=0; i<d; i++)
	{
		scanf("%d%d", mint+i, maxt+i);
		days[i]=mint[i]; sum-=mint[i];
	}
	if (sum<0) puts("NO");
	else
	{
		for (int i=0; i<d; i++)
		{
			while (sum>0&&days[i]<maxt[i])
			{
				sum--; days[i]++;
			}
		}
		if (sum>0) puts("NO");
		else
		{
			puts("YES");
			for (int i=0; i<d; i++)
				printf("%d%c", days[i], (i==d-1)?'\n':' ');
		}
	}
	return 0;
}
