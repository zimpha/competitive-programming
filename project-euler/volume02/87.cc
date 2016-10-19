#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int sol(int n) {
  int N = sqrt(n) + 1;
  vector<int> vs(N, 1), pl;
  for (int i = 2; i < N; ++ i) if (vs[i]) {
    pl.push_back(i);
    for (int j = i; j < N; j += i) vs[j] = 0;
  }
  set<int> S;
  for (size_t i = 0; i < pl.size(); ++ i) {
    LL a = pl[i], sa = (LL)a * a * a * a;
    if (sa >= n) break;
    for (size_t j = 0; j < pl.size(); ++ j) {
      LL b = pl[j], sb = (LL)b * b * b;
      if (sa + sb >= n) break;
      for (size_t k = 0; k < pl.size(); ++ k) {
        int c = pl[k], sc = c * c;
        if (sa + sb + sc > n) break;
        S.insert(sa + sb + sc);
      }
    }
  }
  return S.size();
}

int main() {
  cout << sol(50) << endl;
  cout << sol(50000000) << endl;
  return 0;
}
