#include <bits/stdc++.h>

const int M = 21, N = 75, S = 7;
const int p[M] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73};
const double lim = 30.0 * log(10);
int cnt[M];

std::vector<std::pair<double, __int128>> ok;

void dfs1(int d, double now, __int128 val) {
  if (d == M) {
    ok.push_back({now, val});
    return;
  }
  for (int i = 0; i <= cnt[d]; ++i) {
    dfs1(d + 1, now, val);
    now += log(p[d]);
    if (now >= lim) break;
    val *= p[d];
  }
}

__int128 ret;
double mx;

void dfs2(int d, double now, __int128 val) {
  if (d == S) {
    auto it = std::upper_bound(ok.begin(), ok.end(), std::make_pair(lim - now, (__int128)0)) - 1;
    if (it >= ok.begin() && it->first + now > mx) {
      mx = it->first + now;
      ret = val * it->second;
    }
    return;
  }
  for (int i = 0; i <= cnt[d]; ++i) {
    dfs2(d + 1, now, val);
    now += log(p[d]);
    if (now >= lim) break;
    val *= p[d];
  }
}

int main() {
  for (int i = 0; i < M; ++i) {
    cnt[i] = 0;
    for (int j = p[i]; j <= N; j *= p[i]) cnt[i] += N / j;
  }
  ok.clear();
  dfs1(S, 0, 1);
  std::cout << ok.size() << std::endl;
  std::sort(ok.begin(), ok.end());
  mx = 0;
  dfs2(0, 0, 1);
  const long U = 1000000000000000000ll;
  printf("%ld%018ld\n", (long)(ret / U), (long)(ret % U));
  return 0;
}
