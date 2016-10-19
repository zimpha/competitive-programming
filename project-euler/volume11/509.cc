#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int M = 1234567890;

LL run(LL n) {
  LL p = 1;
  vector<LL> v;
  for (int i = 0; p <= n; p *= 2) {
    v.push_back(n / p - n / p / 2);
  }
  assert(n == accumulate(v.begin(), v.end(), 0ll));
  LL ret = 0;
  for (size_t i = 0; i < v.size(); ++i) v[i] %= M;
  for (size_t a = 0; a < v.size(); ++a) {
    for (size_t b = 0; b < v.size(); ++b) {
      for (size_t c = 0; c < v.size(); ++c) {
        if (a ^ b ^ c) {
          ret += v[a] * v[b] % M * v[c] % M;
          ret %= M;
        }
      }
    }
  }
  return ret;
}

int main() {
  cout << run(10) << endl;
  cout << run(100) << endl;
  cout << run(123456787654321ll) << endl;
  return 0;
}
