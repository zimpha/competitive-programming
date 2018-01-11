#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 10000 + 10;

namespace SA {
int sa[N], rk[N], ht[N], s[N<<1], t[N<<1], p[N], cnt[N], cur[N];
#define pushS(x) sa[cur[s[x]]--] = x
#define pushL(x) sa[cur[s[x]]++] = x
#define inducedSort(v) std::fill_n(sa, n, -1); std::fill_n(cnt, m, 0);      \
  for (int i = 0; i < n; i++) cnt[s[i]]++;                                  \
  for (int i = 1; i < m; i++) cnt[i] += cnt[i-1];                           \
  for (int i = 0; i < m; i++) cur[i] = cnt[i]-1;                            \
  for (int i = n1-1; ~i; i--) pushS(v[i]);                                  \
  for (int i = 1; i < m; i++) cur[i] = cnt[i-1];                            \
  for (int i = 0; i < n; i++) if (sa[i] > 0 &&  t[sa[i]-1]) pushL(sa[i]-1); \
  for (int i = 0; i < m; i++) cur[i] = cnt[i]-1;                            \
  for (int i = n-1;  ~i; i--) if (sa[i] > 0 && !t[sa[i]-1]) pushS(sa[i]-1)
void sais(int n, int m, int *s, int *t, int *p) {
  int n1 = t[n-1] = 0, ch = rk[0] = -1, *s1 = s+n;
  for (int i = n-2; ~i; i--) t[i] = s[i] == s[i+1] ? t[i+1] : s[i] > s[i+1];
  for (int i = 1; i < n; i++) rk[i] = t[i-1] && !t[i] ? (p[n1] = i, n1++) : -1;
  inducedSort(p);
  for (int i = 0, x, y; i < n; i++) if (~(x = rk[sa[i]])) {
    if (ch < 1 || p[x+1] - p[x] != p[y+1] - p[y]) ch++;
    else for (int j = p[x], k = p[y]; j <= p[x+1]; j++, k++)
      if ((s[j]<<1|t[j]) != (s[k]<<1|t[k])) {ch++; break;}
    s1[y = x] = ch;
  }
  if (ch+1 < n1) sais(n1, ch+1, s1, t+n, p+n1);
  else for (int i = 0; i < n1; i++) sa[s1[i]] = i;
  for (int i = 0; i < n1; i++) s1[i] = p[sa[i]];
  inducedSort(s1);
}
template<typename T>
int mapCharToInt(int n, const T *str) {
  int m = *std::max_element(str, str+n);
  std::fill_n(rk, m+1, 0);
  for (int i = 0; i < n; i++) rk[str[i]] = 1;
  for (int i = 0; i < m; i++) rk[i+1] += rk[i];
  for (int i = 0; i < n; i++) s[i] = rk[str[i]] - 1;
  return rk[m];
}
template<typename T>
void suffixArray(int n, const T *str) {
  int m = mapCharToInt(++n, str);
  sais(n, m, s, t, p);
  for (int i = 0; i < n; i++) rk[sa[i]] = i;
  for (int i = 0, h = ht[0] = 0; i < n-1; i++) {
    int j = sa[rk[i]-1];
    while (i+h < n && j+h < n && s[i+h] == s[j+h]) h++;
    if (ht[rk[i]] = h) h--;
  }
}
};

struct ST {
  int u[N][20], n;
  static int lg[N];
  static void init() {
    lg[0] = -1;
    for (int i = 1; i < N; ++i) {
      lg[i] = lg[i >> 1] + 1;
    }
  }
  void build(int a[], int n) {
    this->n = n;
    for (int i = 0; i < n; ++i) u[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; ++j) {
      for (int i = 0; i + (1 << j) <= n; ++i) {
        u[i][j] = std::min(u[i][j - 1], u[i + (1 << (j - 1))][j - 1]);
      }
    }
  }
  int ask(int a, int b) {
    if (a > b) std::swap(a, b);
    int k = lg[b - a + 1];
    return std::min(u[a][k], u[b - (1 << k) + 1][k]);
  }
} sa_min, ht_min;

int ST::lg[N];

char s[N];

int main() {
  ST::init();
  int q, n;
  scanf("%s%d", s, &q);
  n = strlen(s);
  SA::suffixArray(n, s);
  std::vector<int> delta(n + 1);
  for (int i = 1; i <= n; ++i) {
    int l = SA::ht[i];
    int r = n - SA::sa[i];
    delta[i] = delta[i - 1] + r - l;
  }
  sa_min.build(SA::sa, n + 1);
  ht_min.build(SA::ht, n + 1);
  for (int i = 0; i < q; ++i) {
    int k;
    scanf("%d", &k);
    if (k > delta.back()) {
      puts("-1");
      continue;
    }
    int p = std::lower_bound(delta.begin(), delta.end(), k) - delta.begin();
    int len = SA::ht[p] + k - delta[p - 1];
    int left = p, right = n;
    while (left < right) {
      int mid = (left + right + 1) >> 1;
      if (mid == p || ht_min.ask(p + 1, mid) >= len) left = mid;
      else right = mid - 1;
    }
    printf("%d %d\n", sa_min.ask(p, left) + 1, len);
  }
  return 0;
}
