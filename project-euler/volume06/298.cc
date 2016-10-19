#include <bits/stdc++.h>

typedef std::pair<std::vector<int>, std::vector<int>> state;

std::map<state, double> dp[51][101];

double solve(int d, int s, std::vector<int> L, std::vector<int> R) {
  state st = {L, R};
  if (d == 0) return abs(s - 50);
  if (dp[d][s].count(st)) return dp[d][s][st];
  double ret = 0;
  for (int x = 0; x < 10; ++x) {
    std::vector<int> LL, RR;
    int now = s;
    bool find = false;
    for (auto &&v: L) find |= v == x;
    if (find) {
      for (auto &&v: L) {
        if (v != x) LL.push_back(v);
      }
    } else {
      for (size_t i = 0; i < L.size(); ++i) {
        if (i || L.size() != 5) LL.push_back(L[i]);
      }
    }
    LL.push_back(x);
    now += find;
    find = false;
    for (auto &&v: R) find |= v == x;
    if (find) RR = R;
    else {
      for (size_t i = 0; i < R.size(); ++i) {
        if (i || R.size() != 5) RR.push_back(R[i]);
      }
      RR.push_back(x);
    }
    now -= find;
    int num[10], t = 0;
    memset(num, -1, sizeof(num));
    for (auto &&v: RR) {
      num[v] = t++;
      v = num[v];
    }
    for (auto &&v: LL) {
      if (num[v] == -1) num[v] = t++;
      v = num[v];
    }
    ret += 0.1 * solve(d - 1, now, LL, RR);
  }
  return dp[d][s][st] = ret;
}

double run() {
  std::vector<int> v;
  return solve(50, 50, v, v);
}

int main() {
  std::cout.precision(20);
  std::cout << run() << std::endl;
  return 0;
}
