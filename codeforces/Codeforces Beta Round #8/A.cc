#include <bits/stdc++.h>
using namespace std;

char s[100010], a[110], b[110];

int main() {
    scanf("%s%s%s", s, a, b);
    char *x = strstr(s, a);
    if (x) x = strstr(x + strlen(a), b);
    reverse(a, a + strlen(a));
    reverse(b, b + strlen(b));
    char *y = strstr(s, b);
    if (y) y = strstr(y + strlen(b), a);
    if (x && y) puts("both");
    else if (x) puts("forward");
    else if (y) puts("backward");
    else puts("fantasy");

    return 0;
}
