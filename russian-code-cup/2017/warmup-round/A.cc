#include <cstdio>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  long long sum = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    sum += a[i];
  }
  for (int i = 0; i < n; ++i) {
    if (sum - a[i] == a[i]) {
      for (int j = 0; j < n; ++j) {
        if (i != j) printf("%d ", a[j]);
      }
      printf("%d\n", a[i]);
      break;
    }
  }
  return 0;
}
