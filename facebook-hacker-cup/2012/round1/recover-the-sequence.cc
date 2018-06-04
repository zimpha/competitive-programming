#include <cstdio>
#include <vector>

const int N = 1e4 + 10;

char s[N * 100];
int a[N], idx, n;

void merge_sort(int a[], int l, int r) {
  int n = r - l;
  if (n <= 1) return;
  int m = n / 2;
  merge_sort(a, l, l + m);
  merge_sort(a, l + m, r);
  std::vector<int> t;
  int i, j;
  for (i = l, j = l + m; i < l + m && j < r; ) {
    if (s[idx++] == '1') t.emplace_back(a[i++]);
    else t.emplace_back(a[j++]);
  }
  while (i < l + m) t.emplace_back(a[i++]);
  while (j < r) t.emplace_back(a[j++]);
  for (int i = l; i < r; ++i) a[i] = t[i - l];
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%s", &n, s);
    for (int i = 0; i < n; ++i) a[i] = i;
    idx = 0;
    merge_sort(a, 0, n);
    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) p[a[i]] = i;
    int ret = 1, mod = 1000003;
    for (int i = 0; i < n; ++i) {
      ret = ret * 31 + p[i] + 1;
      ret %= mod;
    }
    printf("Case #%d: %d\n", cas, ret);
  }
  return 0;
}
