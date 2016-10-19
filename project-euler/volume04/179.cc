#include <bits/stdc++.h>
using namespace std;
const int N = 10000001;
int d[N];

int main() {
  for (int i = 1; i < N; ++i) {
    for (int j = i; j < N; j += i) d[j]++;
  }
  int ret = 0;
  for (int i = 2; i + 1 < N; ++i) {
    ret += (d[i] == d[i + 1]);
  }
  cout << ret << endl;
  return 0;
}
