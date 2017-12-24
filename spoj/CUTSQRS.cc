#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

struct node {
	int num, win;
};

node solve(int a, int b) {
	if (a<b) swap(a, b);
	if (b==0) return (node){0, 0};
	node ret=solve(b, a%b);
	ret.num+=a/b-1;
	if (ret.win==0 || a/b>1) ret.win=1;
	else ret.win=0;
	return ret;
}

int cal(int x) {
	return (x<=0)?1:(int)floor(x*log10(2))+1;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int a, b; scanf("%d%d", &a, &b);
		node ret=solve(a, b);
		int ans=(ret.win?5:6)+cal(ret.num)+cal(ret.num-1);
		printf("%d\n", ans);
	}
	return 0;
}
