#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

const int mod = 998244353;

using int64 = long long;

int count[62][62];
int64 dp[62][62][62];

int idx(char c) {
  if (c >= 'a' && c <= 'z') return c - 'a' + 10;
  else if (c >= 'A' && c <= 'Z') return c - 'A' + 10 + 26;
  else return c - '0';
}

int solve(std::vector<std::string> &s) {
  memset(count, 0, sizeof(count));
  memset(dp, 0, sizeof(dp));
  std::sort(s.begin(), s.end());
  s.erase(std::unique(s.begin(), s.end()), s.end());
  for (auto &w: s) {
    count[idx(w[0])][idx(w.back())]++;
  }
  for (int d = 0; d < 62; ++d) {
    for (int a = 0; a < 62; ++a) {
      for (int b = a; b < 62; ++b) {
        for (int c = b; c < 62; ++c) {
          dp[a][b][c] += (int64)count[d][a] * count[d][b] % mod * count[d][c] % mod;
        }
      }
    }
  }
  for (int a = 0; a < 62; ++a) {
    for (int b = a; b < 62; ++b) {
      for (int c = b; c < 62; ++c) {
        dp[a][b][c] %= mod;
      }
    }
  }
  int64 ret = 0;
  for (int a = 0; a < 62; ++a) {
    for (int b = a; b < 62; ++b) {
      for (int c = b; c < 62; ++c) {
        for (int d = c; d < 62; ++d) {
          int m = 24;
          if (a == d) { // a = b = c = d
            m = 1;
          } else if (a == c) { // a = b = c < d
            m = 4;
          } else if (a == b) {
            if (c == d) { // a = b < c = d
              m = 6;
            } else { // a = b < c < d
              m = 12;
            }
          } else if (b == d) { // a < b = c = d
            m = 4;
          } else if (b == c || c == d) { // a < b = c < d or a < b < c = d
            m = 12;
          }
          ret += dp[a][b][c] * dp[a][b][d] % mod * dp[a][c][d] % mod * dp[b][c][d] % mod * m % mod;

        }
      }
    }
  }
  return ret % mod;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  std::vector<std::vector<std::string>> words(11);
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    words[s.size()].push_back(s);
    std::reverse(s.begin(), s.end());
    words[s.size()].push_back(s);
  }
  int ret = 0;
  for (int i = 3; i <= 10; ++i) {
    ret += solve(words[i]);
    ret %= mod;
  }
  std::cout << ret << std::endl;
  return 0;
}
