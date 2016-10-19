#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

const int M = 21, N = 75, S = 6;
const int p[M] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73};
double lim = 0;
int cnt[M];

typedef int256_t vll;

std::vector<std::pair<double, vll>> ok;

void dfs1(int d, double now, vll val) {
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

vll ret;
double mx;

void dfs2(int d, double now, vll val) {
  if (d == S) {
    auto it = std::upper_bound(ok.begin(), ok.end(), std::make_pair(lim - now, (vll)0)) - 1;
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
  int1024_t tot = 1;
  lim = 0;
  for (int i = 0; i < N; ++i) {
    lim += log(i + 1);
    tot *= i + 1;
  }
  lim /= 2;
  ok.clear();
  dfs1(S, 0, 1);
  std::cout << ok.size() << std::endl;
  std::sort(ok.begin(), ok.end());
  mx = 0;
  dfs2(0, 0, 1);
  std::cout << tot / ret << "-" << ret << std::endl;
  return 0;
}
