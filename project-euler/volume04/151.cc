#include <bits/stdc++.h>
using namespace std;

map<vector<int>, double> dp;

double dfs(vector<int> a) {
  if (*max_element(a.begin(), a.end()) == 0) return dp[a] = 0;
  if (dp.count(a)) return dp[a];
  double ret = 0;
  int sum = 0;
  for (int i = 0; i < 5; ++i) sum += a[i];
  if (sum == 1) ++ret;
  for (size_t i = 0; i < a.size(); ++i) if (a[i]) {
    vector<int> b = a; b[i]--;
    for (int j = i + 1; j < a.size(); ++j) b[j]++;
    ret += dfs(b) * a[i] / sum;
  }
  return dp[a] = ret;
}

int main() {
  printf("%.6f\n", dfs({1, 0, 0, 0, 0}) - 2);
  return 0;
}
