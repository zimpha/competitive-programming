#include <bits/stdc++.h>

using LL = long long;

const int A[3][3] = {{1, -2, 2}, {2, -1, 2}, {2, -2, 3}};
const int B[3][3] = {{1, 2, 2}, {2, 1, 2}, {2, 2, 3}};
const int C[3][3] = {{-1, 2, 2}, {-2, 1, 2}, {-2, 2, 3}};

std::set<std::tuple<int, int, int>> S;

void add(int a, int b, int c) {
  if (a > b) std::swap(a, b);
  if (a > c) std::swap(a, c);
  if (b > c) std::swap(b, c);
  S.insert({a, b, c});
}

void dfs(int a[], int upp) {
  int sum = a[0] + a[1] + a[2];
  if (sum > upp) return;
  add(a[0], a[1], a[2]);
  int b[3];
  for (int i=0;i<3;++i)b[i]=A[i][0]*a[0]+A[i][1]*a[1]+A[i][2]*a[2];
  dfs(b, upp);
  for (int i=0;i<3;++i)b[i]=B[i][0]*a[0]+B[i][1]*a[1]+B[i][2]*a[2];
  dfs(b, upp);
  for (int i=0;i<3;++i)b[i]=C[i][0]*a[0]+C[i][1]*a[1]+C[i][2]*a[2];
  dfs(b, upp);
}

int run(int upp) {
  int a[] = {2, 2, 3};
  S.clear();
  dfs(a, upp);
  return S.size();
}

int main() {
  std::cout << run(75000000) << std::endl;
  return 0;
}
