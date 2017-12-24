#include <set>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

multiset<int> box;
int N, K;

int main()
{
	scanf("%d", &N);
	long long ret=0;
	box.clear();
	while (N--)
	{
		scanf("%d", &K);
		for (int x, i=0; i<K; i++)
		{
			scanf("%d", &x);
			box.insert(x);
		}
		multiset<int>::iterator it;
		it=box.begin(); ret-=(long long)*it; box.erase(it);
		it=--box.end(); ret+=(long long)*it; box.erase(it);
	}
	printf("%lld\n", ret);
	return 0;
}
