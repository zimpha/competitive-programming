#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

std::vector<int> manacher(char *s, int n) {
  std::vector<int> u(n <<= 1, 0);
  for (int i = 0, j = 0, k; i < n; i += k, j = std::max(j - k, 0)) {
    while (i >= j && i + j + 1 < n && s[(i - j) >> 1] == s[(i + j + 1) >> 1]) ++j;
    for (u[i] = j, k = 1; i >= k && u[i] >= k && u[i - k] != u[i] - k; ++k) {
      u[i + k] = std::min(u[i - k], u[i] - k);
    }
  }
  return u;
}

const int N = 100 + 10;

char s[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s", s);
    int n = strlen(s);
    auto u = manacher(s, n);
    std::string res = "";
    for (int i = 0; i < n; ++i) {
      if (u[i] == i + 1) {
        std::string x;
        for (int j = 0; j < n - 1 - i; ++j) {
          x.push_back(s[n - 1 - j]);
        }
        x += s;
        if (res == "" || x.size() < res.size() || (x.size() == res.size() && x < res)) {
          res = x;
        }
      }
      if (u[i + n - 1] == n - i) {
        std::string x;
        x += s;
        for (int j = 0; j < i; ++j) {
          x.push_back(s[i - 1 - j]);
        }
        if (res == "" || x.size() < res.size() || (x.size() == res.size() && x < res)) {
          res = x;
        }
      }
    }
    printf("Case %d: %d %s\n", cas, int(res.size() - n), res.c_str());
  }
  return 0;
}
