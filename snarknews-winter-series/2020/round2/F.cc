#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 2e6 + 10;

int prev[N], next[N];
bool is_prime[N];

int main() {
  for (int i = 2; i < N; ++i) is_prime[i] = 1;
  for (int i = 2; i < N; ++i) if (is_prime[i]) {
    for (int j = i + i; j < N; j += i) is_prime[j] = 0;
  }
  for (int i = 0; i < N; ++i) next[i] = prev[i] = -1;
  for (int i = 2; i < N; ++i) {
    if (is_prime[i]) prev[i] = i;
    else prev[i] = prev[i - 1];
  }
  for (int i = N - 2; i >= 0; --i) {
    if (is_prime[i]) next[i] = i;
    else next[i] = next[i + 1];
  }
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> a(n), odd(n, 2e9), even(n, 2e9);
  std::vector<int> A(n), S(n);
  int64 ret = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    std::vector<int> primes = {2};
    for (int it = 0, x = next[a[i]]; it < 2 && x != -1; ++it, x = next[x + 1]) {
      primes.push_back(x);
    }
    for (int it = 0, x = prev[a[i]]; it < 2 && x != -1; ++it, x = prev[x - 1]) {
      primes.push_back(x);
    }
    for (auto &p: primes) {
      int step = std::abs(p - a[i]);
      if (step & 1) {
        if (std::abs(odd[i]) > step) odd[i] = p - a[i];
      } else {
        if (std::abs(even[i]) > step) even[i] = p - a[i];
      }
    }
    if (std::abs(even[i]) < std::abs(odd[i])) {
      if (even[i] > 0) A[i] = even[i];
      else S[i] = -even[i];
    } else {
      if (odd[i] > 0) A[i] = odd[i];
      else S[i] = -odd[i];
    }
    ret += A[i] + S[i];
  }
  if (ret <= m && ret % 2 != m % 2) {
    int best = -1, p = -1;
    for (int i = 0; i < n; ++i) if (even[i] <= m && odd[i] <= m) {
      int delta = std::abs(std::abs(odd[i]) - std::abs(even[i]));
      if (best == -1 || delta < best) best = delta, p = i;
    }
    if (best == -1) ret = m + 1;
    else {
      ret -= A[p] + S[p];
      A[p] = S[p] = 0;
      if (std::abs(even[p]) > std::abs(odd[p])) {
        if (even[p] > 0) A[p] = even[p];
        else S[p] = -even[p];
      } else {
        if (odd[p] > 0) A[p] = odd[p];
        else S[p] = -odd[p];
      }
      ret += A[p] + S[p];
    }
  }
  if (ret <= m) {
    puts("YES");
    S[0] += (m - ret) / 2;
    A[0] += (m - ret) / 2;
    for (int i = 0; i < n; ++i) {
      printf("%d %d\n", S[i], A[i]);
    }
  } else {
    puts("NO");
  }
  return 0;
}
