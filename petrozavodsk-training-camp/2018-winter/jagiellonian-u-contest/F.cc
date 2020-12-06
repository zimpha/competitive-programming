#include <cstdio>
#include <cmath>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int r;
    scanf("%*d%*d%*d%d%*d%*d%*d%*d", &r);
    printf("%.20f\n", r * r * acos(-1.0));
  }
  return 0;
}
