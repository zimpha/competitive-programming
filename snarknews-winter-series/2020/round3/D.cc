#include <cstdio>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a;
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    while (!a.empty() && x >= a.back()) a.pop_back();
    a.push_back(x);
    printf("%d\n", (int)a.size());
  }
  return 0;
}
