#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

bool isPal(int n) {
  int r = 0;
  for (int x = n; x; x /= 10) {
    r = r * 10 + x % 10;
  }
  return r == n;
}

LL run(int upp) {
  vector<LL> square;
  square.push_back(0);
  for (int i = 1; i * i <= upp; ++i) {
    square.push_back(i * i);
    square[i] += square[i - 1];
  }
  LL ret = 0;
  set<int> s;
  for (size_t i = 0; i < square.size(); ++i) {
    for (size_t j = i + 2; j < square.size(); ++j) {
      LL now = square[j] - square[i];
      if (now < upp && isPal(now)) {
        s.insert(now);
      }
    }
  }
  for (auto &x: s) ret += x;
  return ret;
}

int main() {
  cout << run(1000) << endl;
  cout << run(100000000) << endl;
  return 0;
}
