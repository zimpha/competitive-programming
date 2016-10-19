#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2000 + 10;
int s[MAXN * MAXN];

int main() {
  for (int k = 1; k <= 4000000; ++k) {
    if (k <= 55) s[k] = (100003 - 200003 * k % 1000000 + 300007 * k * k % 1000000 * k % 1000000 + 1000000000) % 1000000 - 500000;
    else s[k] = (s[k - 24] + s[k - 55] + 1000000) % 1000000 - 500000;
  }
  int ret = 0;
  for (int i = 1; i <= 2000; ++i) {
    int sum = 0;
    for (int j = 1; j <= 2000; ++j) {
      sum = max(0, sum + s[(i - 1) * 2000 + j]);
      ret = max(ret, sum);
    }
  }
  for (int j = 1; j <= 2000; ++j) {
    int sum = 0;
    for (int i = 1; i <= 2000; ++i) {
      sum = max(0, sum + s[(i - 1) * 2000 + j]);
      ret = max(ret, sum);
    }
  }
  for (int s = 2; s <= 4000; ++s) {
    int sum = 0;
    for (int i = max(1, s - 2000); i < s && i <= 2000; ++i) {
      int j = s - i;
      sum = max(0, sum + ::s[(i - 1) * 2000 + j]);
      ret = max(ret, sum);
    }
  }
  for (int s = -1999; s <= 1999; ++s) {
    int sum = 0;
    for (int i = max(1, s + 1); i <= 2000 && i <= s + 2000; ++i) {
      int j = i - s;
      sum = max(0, sum + ::s[(i - 1) * 2000 + j]);
      ret = max(ret, sum);
    }
  }
  cout << ret << endl;
  return 0;
}
