#include <bits/stdc++.h>
using namespace std;

int run(int n, int k) {
  vector<bool> vs(n + 1, 0);
  vector<int> rad(n + 1, 1);
  vector<int> id(n);
  for (int i = 2; i <= n; ++i) if (!vs[i]) {
    for (int j = i; j <= n; j += i) {
      rad[j] *= i; vs[j] = 1;
    }
  }
  for (int i = 0; i < n; ++i) id[i] = i + 1;
  sort(id.begin(), id.end(), [&](int a, int b) {
      return rad[a] < rad[b] || (rad[a] == rad[b] && a < b);
  });
  return id[k - 1];
}

int main() {
  cout << run(10, 4) << endl;
  cout << run(10, 6) << endl;
  cout << run(100000, 10000) << endl;
  return 0;
}
