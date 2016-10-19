#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10000000, M = 1e9 + 7, iv = 500000004;
int sg[MAXN], mp[MAXN], pl[MAXN];
int cnt[MAXN];

void fwt(int *a, int n) {
  for (int d = 1; d < n; d <<= 1) {
    for (int m = d << 1, i = 0; i < n; i += m) {
      for (int j = 0; j < d; ++j) {
        int x = a[i + j], y = a[i + j + d];
        a[i + j] = (x + y) % M;
        a[i + j + d] = (x + M - y) % M;
      }
    }
  }
}
void lfwt(int *a, int n) {
  for (int d = 1; d < n; d <<= 1) {
    for (int m = d << 1, i = 0; i < n; i += m) {
      for (int j = 0; j < d; ++j) {
        int x = a[i + j], y = a[i + j + d];
        a[i + j] = 1ll * (x + y) % M * iv % M;
        a[i + j + d] = 1ll * (x + M - y) % M * iv % M;
      }
    }
  }
}


int run(int n, int k) {
  for (int i = 0; i < n; ++i) mp[i] = 0;
  int m = 0; mp[1] = 1;
  for (int i = 2; i < n; ++i) {
    if (!mp[i]) mp[i] = i, pl[m++] = i;
    for (int j = 0; j < m && pl[j] * i < n; ++j) {
      mp[pl[j] * i] = pl[j];
      if (i % pl[j] == 0) break;
    }
  }
  m = 1;
  for (int i = 0; i < n; ++i) cnt[i] = 0;
  for (int i = 1; i < n; ++i) {
    if (i % 2 == 0) sg[i] = 0;
    else {
      if (mp[i] == i) sg[i] = m++;
      else sg[i] = sg[mp[i]];
    }
    cnt[sg[i]]++;
  }
  int s = 1;
  while (s < m) s <<= 1;
  fwt(cnt, s);
  static int ret[MAXN];
  for (int i = 0; i < s; ++i) ret[i] = 1;
  for (n = k; n; n >>= 1) {
    if (n & 1) {
      for (int i = 0; i < s; ++i) {
        ret[i] = 1ll * ret[i] * cnt[i] % M;
      }
    }
    for (int i = 0; i < s; ++i) {
      cnt[i] = 1ll * cnt[i] * cnt[i] % M;
    }
  }
  lfwt(ret, s);
  return ret[0];
}

int main() {
  cout << run(10, 5) << endl;
  cout << run(10, 10) << endl;
  cout << run(1000, 1000) << endl;
  cout << run(10000000, 10000000) << endl;
}
