#include <iostream>
#include <vector>

using int64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, k, q;
  std::cin >> n >> k >> q;
  std::vector<char> A(q);
  std::vector<int> B(q);
  std::vector<int> C(q);
  for (int i = 0; i < q; ++i) {
    std::cin >> A[i] >> B[i] >> C[i];
    --B[i], --C[i];
  }
  std::vector<bool> mark_row(n), mark_col(n);
  std::vector<int64> ret(k);
  int cnt_row = 0, cnt_col = 0;
  for (int i = q - 1; i >= 0; --i) {
    if (A[i] == 'R') {
      if (mark_row[B[i]]) continue;
      mark_row[B[i]] = true;
      ++cnt_row;
      ret[C[i]] += n - cnt_col;
    } else {
      if (mark_col[B[i]]) continue;
      mark_col[B[i]] = true;
      ++cnt_col;
      ret[C[i]] += n - cnt_row;
    }
  }
  ret[0] = (int64)n * n;
  for (int i = 1; i < k; ++i) {
    ret[0] -= ret[i];
  }
  for (int i = 0; i < k; ++i) {
    printf("%lld\n", ret[i]);
  }
  return 0;
}
