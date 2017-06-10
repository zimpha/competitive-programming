#include <cstdio>
#include <vector>

const int N = 10000001;

int nx[N];

int main() {
  for (int i = 0; i < N; ++i) {
    nx[i] = (i * 5402147ll + 54321) % 10000001;
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    std::vector<int> candidate;
    for (int i = 0; i < N; ++i) {
      if (i % 1000 == a[0]) candidate.push_back(i);
    }
    for (int i = 1; i < n; ++i) {
      std::vector<int> new_can;
      for (auto &&e: candidate) {
        if (nx[e] % 1000 == a[i]) new_can.push_back(nx[e]);
      }
      candidate.swap(new_can);
    }
    printf("Case #%d:", cas);
    if (candidate.empty()) puts(" Wrong machine");
    else if (candidate.size() > 1) puts(" Not enough observations");
    else {
      int u = candidate[0];
      for (int i = 0; i < 10; ++i) {
        u = nx[u];
        printf(" %d", u % 1000);
      }
      puts("");
    }
  }
  return 0;
}
