#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4000 + 10;
int m[MAXN], c[MAXN], n, k;

int cost;
bool check(int s) {
  cost = 0;
  map<int, vector<int>> mp;
  for (int i = 0; i < n; ++i) {
    mp[m[i]].push_back(c[i]);
  }
  vector<int> pt;
  for (auto &x: mp) if (x.second.size() >= s) {
    sort(x.second.begin(), x.second.end(), greater<int>());
    int tmp = 0;
    for (int i = 0; i < s; ++i) tmp += x.second[i];
    pt.push_back(tmp);
  }
  sort(pt.begin(), pt.end(), greater<int>());
  for (int i = 0; i < k && i < pt.size(); ++i) cost += pt[i];
  return pt.size() >= k;
}

void run() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) scanf("%d%d", m + i, c + i);
  int left = 0, right = n / k;
  while (left < right) {
    int mid = (left + right + 1) >> 1;
    if (check(mid)) left = mid;
    else right = mid - 1;
  }
  check(left);
  printf("%d %d\n", left, cost);
}

int main() {
  run();
  return 0;
}
