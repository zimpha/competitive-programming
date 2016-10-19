#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL run(int n) {
  vector<int> a; --n;
  do {
    a.push_back(n % 7); n /= 7;
  } while (n);
  reverse(a.begin(), a.end());
  LL mul = 1, ret = 0;
  for (size_t i = 0; i < a.size(); ++i) {
    LL tmp = mul * (1 + a[i]) * a[i] / 2; mul *= (a[i] + 1);
    for (size_t j = i + 1; j < a.size(); ++j) tmp *= 28;
    ret += tmp;
  }
  return ret + mul;
}

int main() {
  cout << run(7) << endl;
  cout << run(100) << endl;
  cout << run(1000000000) << endl;
  return 0;
}
