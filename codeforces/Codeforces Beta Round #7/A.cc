#include <cstdio>
#include <cstring>

int main() {
	int x=0, y=0, num;
	for (int i=0; i<8; i++) {
		char st[10]; scanf("%s", st); num=0;
		for (int j=0; j<8; j++) {
			if (st[j]=='B') num++;
		}
		if (num==8) x++;
		else y=num;
	}
	printf("%d\n", x+y);
	return 0;
}
