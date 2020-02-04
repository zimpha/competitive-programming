#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 2e5 + 10;

bool exclude[26];
int prefix[N][26], suffix[N][26];
char s[N], t[N], buf[N * 2];
int fail[N * 2];
int64 dp[2][N];

void update(int64 &x, int64 y) {
  if (x < y) x = y;
}

int main() {
  scanf("%s%s", s + 1, t + 1);
  int n = strlen(s + 1);
  int m = strlen(t + 1);
  std::vector<int> w(n);
  for (int i = 0; i < n; ++i) scanf("%d", &w[i]);
  for (int i = 1; i <= m; ++i) {
    memcpy(prefix[i], prefix[i - 1], sizeof(prefix[i]));
    prefix[i][t[i] - 'a']++;
  }
  for (int i = m; i >= 0; --i) {
    memcpy(suffix[i], suffix[i + 1], sizeof(suffix[i]));
    suffix[i][t[i] - 'a']++;
  }

  std::vector<int> segs;
  for (int i = 1; i <= m; ++i) {
    if (prefix[i - 1][t[i] - 'a'] == 0 || suffix[i + 1][t[i] - 'a'] == 0) {
      segs.push_back(i);
    }
  }
  memset(dp[0], -1, sizeof(dp[0]));
  dp[0][0] = 0;
  int cur = 0, next = 1;
  for (size_t x = 0; x < segs.size(); ++x) for (int it = 0; it < 2; ++it) {
    if (x == segs.size() - 1 && it == 1) break;
    int l = -1, r = -1;
    if (it == 0) l = r = segs[x];
    else l = segs[x] + 1, r = segs[x + 1] - 1;
    if (l > r) continue;
    memset(dp[next], -1, sizeof(*dp[next]) * (n + 1));
    for (int i = 0; i < 26; ++i) {
      exclude[i] = prefix[l - 1][i] == 0 || suffix[l][i] == 0;
    }
    for (int i = 1; i <= n; ++i) {
      if (exclude[s[i] - 'a'] && dp[cur][i - 1] != -1) {
        update(dp[cur][i], dp[cur][i - 1]);
      }
    }
    if (it == 0) {
      for (int i = 1; i <= n; ++i) if (s[i] == t[l] && dp[cur][i - 1] != -1) {
        update(dp[next][i], dp[cur][i - 1] + w[i - 1]);
      }
    } else {
      std::vector<int> inc;
      int m = 0;
      for (int i = l; i <= r; ++i) buf[m++] = t[i];
      buf[m++] = '#';
      for (int i = 1; i <= n; ++i) if (!exclude[s[i] - 'a']) {
        buf[m++] = s[i];
        inc.push_back(i);
      }
      std::vector<bool> match(inc.size(), 0);
      std::vector<int64> sum(inc.size() + 1, 0);
      for (int i = inc.size() - 1; i >= 0; --i) {
        sum[i] = sum[i + 1] + w[inc[i] - 1];
      }
      fail[0] = -1;
      for (int i = 1, j = -1; i < m; ++i) {
        while (j >= 0 && buf[j + 1] != buf[i]) j = fail[j];
        fail[i] = buf[j + 1] == buf[i] ? ++j : j;
        if (fail[i] >= r - l) {
          match[i - (r - l + 1) - fail[i] - 1] = true;
        }
      }
      for (size_t i = 0; i < inc.size(); ++i) if (match[i]) {
        auto w = sum[i] - sum[i + (r - l + 1)];
        if (dp[cur][inc[i] - 1] != -1) {
          update(dp[next][inc[i + r - l]], dp[cur][inc[i] - 1] + w);
        }
      }
    }
    //for (int i = 0; i <= n; ++i) printf("%lld ", dp[next][i]);
    //puts("");
    std::swap(cur, next);
  }
  int64 ret = -1;
  for (int i = 1; i <= n; ++i) {
    update(ret, dp[cur][i]);
  }
  if (ret == -1) {
    puts("You better start from scratch man...");
  } else {
    for (auto &x: w) ret -= x;
    printf("%lld\n", -ret);
  }
  return 0;
}

