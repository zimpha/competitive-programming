#include <bits/stdc++.h>
using namespace std;
typedef double flt;
typedef long long LL;
typedef pair<int, int> PII;
const int MAXN = 30;
bool dp[2][2][MAXN][MAXN][MAXN][MAXN];

void run() {
  int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
  for (int s = 0; s < 2; ++s) {
    for (int e = 0; e < 2; ++e) {
      if (!dp[s][e][a][b][c][d]) continue;
      putchar('0' + s);
      int n = a + b + c + d + 1;
      for (int i = 1; i < n; ++i) {
        for (int t = 0; t < 2; ++t) {
          if (a >= 1 && s == 0 && t == 0 && dp[t][e][a - 1][b][c][d]) {
            s = t; putchar('0' + s); --a; break;
          }
          if (b >= 1 && s == 0 && t == 1 && dp[t][e][a][b - 1][c][d]) {
            s = t; putchar('0' + s); --b; break;
          }
          if (c >= 1 && s == 1 && t == 0 && dp[t][e][a][b][c - 1][d]) {
            s = t; putchar('0' + s); --c; break;
          }
          if (d >= 1 && s == 1 && t == 1 && dp[t][e][a][b][c][d - 1]) {
            s = t; putchar('0' + s); --d; break;
          }
        }
      }
      puts("");
      return;
    }
  }
  puts("impossible");
}

int main() {
  dp[0][0][0][0][0][0] = 1;
  dp[1][1][0][0][0][0] = 1;
  for (int s = 0; s < 2; ++s) {
      for (int a = 0; a <= 20; ++a) {
        for (int b = 0; b <= 20; ++b) {
          for (int c = 0; c <= 20; ++c) {
            for (int d = 0; d <= 20; ++d) {

                for (int t = 0; t < 2; ++t) {
              if (!dp[s][t][a][b][c][d]) continue;
              for (int e = 0; e < 2; ++e) {
                if (t == 0 && e == 0) dp[s][e][a + 1][b][c][d] = 1;
                if (t == 0 && e == 1) dp[s][e][a][b + 1][c][d] = 1;
                if (t == 1 && e == 0) {
                  //if (s == 1) cerr << a << " " << b << " " << c + 1 << " " << d << endl;
                  dp[s][e][a][b][c + 1][d] = 1;
                }
                if (t == 1 && e == 1) dp[s][e][a][b][c][d + 1] = 1;
              }
            }
          }
        }
      }
    }
  }
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) run();
  return 0;
}
