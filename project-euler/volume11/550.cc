#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 10000000 + 1, M = 987654321, S = 64;
vector<int> dv[MAXN];
int sg[MAXN], cnt[S];

void sieve(int n) {
  for (int i = 0; i <= n; ++i) dv[i].clear();
  for (int i = 2; i <= n; ++i) {
    for (int j = i + i; j <= n; j += i) {
      dv[j].push_back(i);
    }
  }
}

void add(int &x, int y) {
  x += y; if (x >= M) x -= M;
}

typedef int Matrix[S][S];
void mul(Matrix A, Matrix B) {
  static Matrix C;
  for (int i = 0; i < S; ++i) {
    for (int j = 0; j < S; ++j) {
      C[i][j] = 0;
      for (int k = 0; k < S; ++k) {
        add(C[i][j], 1ll * A[i][k] * B[k][j] % M);
      }
    }
  }
  for (int i = 0; i < S; ++i) {
    for (int j = 0; j < S; ++j) {
      A[i][j] = C[i][j];
    }
  }
}

int run(int n, LL k) {
  sieve(n); sg[1] = 0;
  for (int i = 0; i < S; ++i) cnt[i] = 0;
  for (int i = 2; i <= n; ++i) {
    static bool mark[S]; sg[i] = -1;
    memset(mark, 0, sizeof(mark));
    vector<int> &v = dv[i];
    for (size_t a = 0; a < v.size(); ++a) {
      for (size_t b = 0; b <= a; ++b) {
        mark[sg[v[a]] ^ sg[v[b]]] = 1;
      }
    }
    for (int s = 0; sg[i] == -1; ++s) {
      if (!mark[s]) sg[i] = s;
    }
    cnt[sg[i]]++;
  }
  Matrix A;
  for (int i = 0; i < S; ++i) {
    for (int j = 0; j < S; ++j) {
      A[i][j] = cnt[i ^ j];
    }
  }
  int R[S]; memset(R, 0, sizeof(R)); R[0] = 1;
  for (; k; k >>= 1) {
    if (k & 1) {
      static int tmp[S];
      for (int i = 0; i < S; ++i) {
        tmp[i] = 0;
        for (int j = 0; j < S; ++j) {
          add(tmp[i], 1ll * A[i][j] * R[j] % M);
        }
      }
      memcpy(R, tmp, sizeof(tmp));
    }
    mul(A, A);
  }
  int ret = 0;
  for (int i = 1; i < S; ++i) add(ret, R[i]);
  return ret;
}

int main() {
  cout << run(10, 5) << endl;
  cout << run(32, 4) << endl;
  cout << run(1e7, 1e12) << endl;
  return 0;
}
