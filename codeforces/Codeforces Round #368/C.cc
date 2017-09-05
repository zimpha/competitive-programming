#include <bits/stdc++.h>
using LL = long long;
using PII = std::pair<int, int>;

std::vector<PII> pl;
int n;

bool dfs1(int d, LL now) {
  LL X = now, Y = 1ll * n * n / now;
  if ((X + Y) % 2 == 0) {
    LL b = (X + Y) / 2, a = (Y - X) / 2;
    if (1 <= b && a >= 1) {
      std::cout << a << " " << b << std::endl;
      return true;
    }
  }
  if (d == pl.size()) return false;
  for (int i = 0; i <= pl[d].second; ++i) {
    if (dfs1(d + 1, now)) return true;
    now *= pl[d].first;
  }
  return false;
}

bool solve(int n) {
  for (int i = 2; i * i <= n; ++i) if (n % i == 0) {
    int c = 0;
    while (n % i == 0) n /= i, ++c;
    pl.push_back(PII(i, c * 2));
  }
  if (n > 1) pl.push_back(PII(n, 2));
  return dfs1(0, 1);
}

const int A[3][3] = {{1,-2,2},{2,-1,2},{2,-2,3}};
const int B[3][3] = {{1,2,2},{2,1,2},{2,2,3}};
const int C[3][3] = {{-1,2,2},{-2,1,2},{-2,2,3}};
bool dfs(LL a[3]) {
  LL b[3];
  if (a[2] > n) return false;
  if (n % a[2] == 0) {
    int k = n / a[2];
    std::cout << a[0] * k << " " << a[1] * k << std::endl;
    return true;
  }
  for (int i=0;i<3;++i)b[i]=A[i][0]*a[0]+A[i][1]*a[1]+A[i][2]*a[2];
  if (dfs(b)) return true;
  for (int i=0;i<3;++i)b[i]=B[i][0]*a[0]+B[i][1]*a[1]+B[i][2]*a[2];
  if (dfs(b)) return true;
  for (int i=0;i<3;++i)b[i]=C[i][0]*a[0]+C[i][1]*a[1]+C[i][2]*a[2];
  if (dfs(b)) return true;
  return false;
}

void run() {
  std::cin >> n;
  LL a[3] = {3, 4, 5};
  if (!solve(n) && !dfs(a)) puts("-1");
}

int main() {
  run();
  return 0;
}
