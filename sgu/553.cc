#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200000 + 10;

int w[MAXN], c[MAXN];
int n, m, k;

void run() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", w + i, c + i);
    w[i] += w[i - 1]; c[i] += c[i - 1];
  }
  int ret = -1, h = 0, t = 0;
  for (int i = n; i >= 1; --i) {
    int ch = c[n] - c[i], wh = w[i] - w[i - m];
    if (1l * w[i - m] * k < wh) break;
    int l = 1, r = i - m;
    while (l < r) {
      int mid = (l + r + 1) >> 1;
      int wt = w[i - m] - w[mid - 1];
      if (1ll * wt * k >= wh) l = mid;
      else r = mid - 1;
    }
    int ct = c[l - 1];
    if (ret == -1 || ct + ch > ret) ret = ct + ch, t = l - 1, h = n - i;
  }
  if (ret == -1) puts("0 0");
  else {
    printf("%d %d\n", h + t, ret);
    while (h--) putchar('H');
    while (t--) putchar('T');
    puts("");
  }
}

int main() {
  run();
  return 0;
}
