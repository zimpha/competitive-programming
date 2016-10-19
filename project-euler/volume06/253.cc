#include <bits/stdc++.h>

std::map<std::vector<int>, double> dp[40];

double solve(std::vector<int> state, size_t m) {
  std::sort(state.begin() + 1, state.end() - 1);
  if (dp[m].count(state)) return dp[m][state];
  int total = 0;
  for (auto &&x: state) total += x;
  if (state.size() == 2 && !total) return dp[m][state] = m;
  double res = 0;
  std::vector<int> tmp;
  for (size_t i = 0; i < state.size(); ++i) {
    int len = state[i], sz = tmp.size();
    for (int j = 1; j <= len; ++j) {
      if (j - 1 || i == 0) tmp.push_back(j - 1);
      if (len - j || i + 1 == state.size()) tmp.push_back(len - j);
      for (size_t k = i + 1; k < state.size(); ++k) tmp.push_back(state[k]);
      res += solve(tmp, std::max(m, tmp.size() - 1));
      while (tmp.size() > sz) tmp.pop_back();
    }
    tmp.push_back(state[i]);
  }
  return dp[m][state] = res / total;
}

double run(int n) {
  double ret = 0;
  for (int i = 1; i <= n / 2; ++i) {
    dp[i].clear();
  }
  for (int i = 1; i <= n; ++i) {
    ret += solve({i - 1, n - i}, 1) / n;
  }
  return ret;
}

int main() {
  std::cout.precision(10);
  std::cout << run(10) << std::endl;
  std::cout << run(40) << std::endl;
  return 0;
}
