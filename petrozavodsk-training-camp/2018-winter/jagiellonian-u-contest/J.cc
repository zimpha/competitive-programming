#include <cmath>
#include <ctime>
#include <cstdio>
#include <vector>
#include <algorithm>

using i64 = long long;

const int N = 150000 + 10;
const i64 mod = 1945555039024054273ll;

std::vector<int> factors[N];
i64 rd[N], hash[N];
long double ln[N];

int main() {
  srand(time(NULL));
  ln[0] = 0;
  for (int i = 1; i < N; ++i) {
    ln[i] = ln[i - 1] + log(i);
    rd[i] = (i64)rand() * rand() % mod;
  }
  hash[0] = hash[1] = 0;
  for (int i = 2; i < N; ++i) {
    hash[i] = hash[i - 1];
    if (factors[i].empty()) {
      for (int j = i; j < N; j += i) {
        factors[j].push_back(i);
      }
    }
    int w = i;
    for (auto &p: factors[i]) {
      while (w % p == 0) {
        w /= p;
        hash[i] += rd[p];
        if (hash[i] >= mod) hash[i] -= mod;
      }
    }
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int t, m;
    scanf("%d%d", &t, &m);
    long double lnx = 0;
    i64 hashx = 0;
    for (int i = 0, p; i < t; ++i) {
      scanf("%d", &p);
      hashx = (hashx + rd[p]) % mod;
      lnx += log(p);
    }
    int ret_n = -1, ret_k = -1;
    for (int n = 0; n <= m && ret_n == -1; ++n) {
      int left = 0, right = (n + 1) / 2;
      while (left < right) {
        int mid = (left + right + 1) / 2;
        long double v = ln[n] - ln[mid] - ln[n - mid];
        if (v <= lnx) left = mid;
        else right = mid - 1;
      }
      for (int k = std::max(0, left - 10); k <= left + 10 && k <= (n + 1) / 2; ++k) {
        i64 h = (hash[n] - hash[k] - hash[n - k] + mod * 2) % mod;
        if (h == hashx) ret_n = n, ret_k = k;
      }
    }
    if (ret_n == -1) puts("NO");
    else printf("YES\n%d %d\n", ret_n, ret_k);
  }
  return 0;
}
