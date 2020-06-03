#include <cstdio>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  int l = 0;
  while (l + 1 < n && a[l] <= a[l + 1]) ++l;
  int r = l + 1;
  while (r + 1 < n && a[r] <= a[r + 1]) ++r;
  if (r >= n || (r == n - 1 && a[n - 1] <= a[0])) {
    puts("TAK");
    return 0;
  }
  l = 0;
  while (l + 1 < n && a[l] >= a[l + 1]) ++l;
  r = l + 1;
  while (r + 1 < n && a[r] >= a[r + 1]) ++r;
  if (r >= n || (r == n - 1 && a[n - 1] >= a[0])) {
    puts("TAK");
    return 0;
  }
  puts("NIE");
  return 0;
}
