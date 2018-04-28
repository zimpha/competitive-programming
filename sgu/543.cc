#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2000 + 10;
int a[MAXN], n, m;

bool check(int num1) {
  static int b[MAXN];
  int sz1 = m, sz2 = 0, num2 = 0;
  int cnt3 = 0, cnt2 = 0;
  for (int i = 0; i < n; ++i) {
    b[i] = a[i];
    if (b[i] & 1) ++cnt3, b[i] -= 3;
  }
  if (sz1 & 1) {
    sz2 = sz1 - 3;
    num2 = min(num1, cnt3);
    num1 -= num2, cnt3 -= num2;
    if (num1 > 1) {
      for (int i = 0; i < n && num1 > 1; ++i) if (b[i] >= 6) {
        int has = b[i] / 6, need = num1 / 2;
        int mx = min(has, need);
        b[i] -= mx * 6;
        num1 -= mx * 2;
        num2 += mx * 2;
      }
    }
  }
  for (int i = 0; i < n; ++i) cnt2 += b[i] / 2;
  if (m % 2 == 0) swap(num1, num2), swap(sz1, sz2);
  if (cnt3) {
    assert(num1 == 0);
    for (int i = 0; i < num2; ++i) {
      int mx = min(cnt3, sz2 / 3 - (sz2 / 3 % 2));
      int now = sz2 - mx * 3; cnt3 -= mx; 
      mx = min(cnt2, now / 2);
      cnt2 -= mx; now -= mx * 2;
      mx = min(cnt3, now / 3);
      cnt3 -= mx; now -= 3 * mx;
      if (!cnt2 && !cnt3) return true;
    }
    return false;
  } else return sz1 / 2 * num1 + sz2 / 2 * num2 >= cnt2;
}

void run() {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> a[i];
  int left = 0, right = 2e6;
  check(1);
  while (left < right) {
    int mid = (left + right - 1) >> 1;
    if (check(mid)) right = mid;
    else left = mid + 1;
  }
  cout << left << endl;
}

int main() {
  run();
  return 0;
}
