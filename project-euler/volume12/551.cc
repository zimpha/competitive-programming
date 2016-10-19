#include <bits/stdc++.h>

typedef __int128 ll;

std::map<std::tuple<int, int, ll>, std::pair<ll, ll>> dp;

std::pair<ll, ll> dfs(int len, int pre, ll init) {
  auto state = std::make_tuple(len, pre, init);
  if (dp.count(state)) return dp[state];
  if (len == 0) {
    if (init == 1) return {1, pre};
    else return {0, init - 1};
  }
  ll step = 0;
  for (int x = 0; x < 10; ++x) {
    auto res = dfs(len - 1, pre + x, init);
    step += res.first;
    init = res.second;
  }
  return dp[state] = {step, init};
}

ll solve(int len, int pre, ll init, ll n, ll val) {
  if (len == 0) return val + init - 1;
  for (int x = 0; x < 10; ++x) {
    auto res = dfs(len - 1, pre + x, init);
    ll step = res.first;
    if (step >= n) {
      return solve(len - 1, pre + x, init, n, val * 10 + x);
    }
    init = res.second;
    n -= step;
  }
  return -1;
}

void run(long n) {
  ll res = solve(19, 0, 2, n, 0);
  const long M = 1000000000000000000ll;
  printf("%ld%018ld\n", (long)(res / M), (long)(res % M));
}

int main() {
  run(100000);
  run(1000000);
  run(1000000000000000ll);
  run(100000000000000000ll);
  return 0;
}
