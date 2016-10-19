#include <bits/stdc++.h>

using LL = long long;

const int N = 203, M = 1000000000;

void mul(LL A[N][N], LL B[N][N]) {
  static LL C[N][N];
  memset(C, 0, sizeof(C));
  for (int i = 0; i < N; ++i) {
    for (int k = 0; k < N; ++k) {
      for (int j = 0; j < N; ++j) {
        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % M;
      }
    }
  }
  memcpy(A, C, sizeof(C));
}

std::map<std::vector<int>, int> cache;
int f[6];

void get_all_state(int d, int m) {
  if (d == 6) {
    int id = cache.size();
    cache[std::vector<int>(f, f + 6)] = id;
    return;
  }
  for (int i = 0; i <= m; ++i) {
    f[d] = i;
    get_all_state(d + 1, m + (m == i));
  }
}

std::vector<int> get_id(std::vector<int> v) {
  std::vector<int> res(6);
  std::map<int, int> mp;
  if (v.size() == 7) v.erase(v.begin());
  for (int i = 0; i < 6; ++i) {
    if (!mp.count(v[i])) {
      int id = mp.size();
      mp[v[i]] = id;
    }
    res[i] = mp[v[i]];
  }
  return res;
}

void get_trans_matrix(LL A[N][N]) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      A[i][j] = 0;
    }
  }
  for (auto &&x: cache) {
    std::vector<int> v = x.first;
    for (int i = 0; i < 7; ++i) {
      v.push_back(i);
      std::set<int> all(v.begin(), v.end());
      if (all.size() < 7) {
        auto u = get_id(v);
        A[cache[u]][x.second] += 1;
      }
      v.pop_back();
    }
  }
}

void generate_values(LL R[N]) {
  for (int i = 0; i < N; ++i) R[i] = 0;
  for (int msk = 0; msk < 262144; ++msk) {
    std::vector<int> u(6);
    for (int i = 0; i < 6; ++i) {
      u[i] = msk >> (i * 3) & 7;
    }
    if (*std::max_element(u.begin(), u.end()) == 7) continue;
    ++R[cache[get_id(u)]];
  }
}

LL run(LL n) {
  cache.clear();
  get_all_state(0, 0);
  static LL A[N][N], X[N], Y[N];
  get_trans_matrix(A);
  generate_values(X);
  for (n -= 6; n; n >>= 1) {
    if (n & 1) {
      memset(Y, 0, sizeof(Y));
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          Y[i] = (Y[i] + A[i][j] * X[j]) % M;
        }
      }
      memcpy(X, Y, sizeof(Y));
    }
    mul(A, A);
  }
  LL ret = 0;
  for (int i = 0; i < N; ++i) ret += X[i];
  return ret % M;
}

int main() {
  std::cout << run(7) << std::endl;
  std::cout << run(1000000000000ll) << std::endl;
  return 0;
}
