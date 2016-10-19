#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 1e8 + 10;

int mp[MAXN], pl[MAXN];

void sieve(int n) {
  for (int i = 1; i <= n; ++i) mp[i] = 0;
  for (int i = 2, m = 0; i <= n; ++i) {
    if (!mp[i]) mp[i] = i, pl[m++] = i;
    for (int j = 0; j < m && pl[j] * i <= n; ++j) {
      mp[pl[j] * i] = pl[j];
      if (i % pl[j] == 0) break;
    }
  }
}

int s(int n) {
  static int p[20], cnt[20], m; m = 0;
  for (int x = n; x > 1; x /= mp[x]) {
    int v = mp[x];
    if (m == 0 || p[m - 1] != v) p[m] = v, cnt[m++] = 1;
    else cnt[m - 1]++;
  }
  int r = 0;
  for (int i = 0; i < m; ++i) {
    int left = p[i], right = p[i] * cnt[i];
    while (left < right) {
      int mid = (left + right - 1) >> 1;
      int sum = 0;
      for (LL x = p[i]; x <= mid; x *= p[i]) sum += mid / x;
      if (sum >= cnt[i]) right = mid;
      else left = mid + 1;
    }
    r = max(r, left);
  }
  return r;
}

LL run(int n) {
  sieve(n);
  LL ret = 0;
  for (int i = 2; i <= n; ++i) {
    ret += s(i);
  }
  return ret;
}

int main() {
  cout << run(100) << endl;
  cout << run(1e8) << endl;
  return 0;
}
