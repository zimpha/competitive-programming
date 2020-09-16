#include <cstdio>
#include <cstring>
#include <vector>

using i64 = long long;
const int N = 1e5 + 10;

char s[N];
int mate[N];

i64 parse(int l, int r) {
  if (l >= r) return 0;
  if (s[l] == 'L') return parse(l + 1, r) + 1;
  if (s[l] == 'R') return parse(l + 1, r) - 1;
  int w = 0;
  for (; s[l] != '('; l++) {
    w = w * 10 + s[l] - '0';
  }
  return w * parse(l + 1, mate[l]) + parse(mate[l] + 1, r);
}

int main() {
  freopen("xoring.in", "r", stdin);
  freopen("xoring.out", "w", stdout);
  int n, m;
  scanf("%d", &n);
  std::vector<int> x(n), ret(n);
  for (int i = 0; i < n; ++i) scanf("%d", &x[i]);
  scanf("%s", s);
  m = strlen(s);
  std::vector<int> stk;
  for (int i = 0; i < m; ++i) {
    if (s[i] == '(') stk.push_back(i);
    else if (s[i] == ')') {
      mate[stk.back()] = i;
      mate[i] = stk.back();
      stk.pop_back();
    }
  }
  m = parse(0, m);
  if (m > 0) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      if (cnt == 0) for (int j = i; j < n; ++j) ret[j] ^= x[j - i];
      cnt += __builtin_ctzll(m + i) - __builtin_ctzll(i + 1);
    }
  } else if (m < 0) {
    m = -m;
    int cnt = 0;
    for (int i = 0; i < n && i <= m; ++i) {
      if (cnt == 0) for (int j = i; j < n; ++j) ret[j] ^= x[j - i];
      if (i < m) cnt += __builtin_ctzll(m - i) - __builtin_ctzll(i + 1);
    }
  } else {
    ret = x;
  }
  for (int i = 0; i < n; ++i) printf("%d ", ret[i]);
  puts("");
  return 0;
}
