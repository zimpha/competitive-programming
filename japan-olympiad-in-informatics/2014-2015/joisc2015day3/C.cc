#include "navigation_lib.h"

#include <vector>
#include <functional>

/*int mark[1000];

void Flag(int u, int v) {
  printf("m[%d]=%d\n", u, v);
  mark[u] = v;
}

void Answer(int x) {
  printf("ans=%d\n", x);
}*/

void Anna(int K, int N, int T, int A[], int B[]) {
  std::vector<std::vector<int>> edges(N);
  std::vector<int> mark(N);

  std::function<void(int, int)> dfs = [&](int u, int p = -1) {
    for (auto &v: edges[u]) if (v != p) {
      if (v > u) mark[v] = mark[u] ^ 1;
      else mark[v] = mark[u];
      dfs(v, u);
    }
  };

  for (int i = 0; i < N - 1; ++i) {
    --A[i], --B[i];
    edges[A[i]].push_back(B[i]);
    edges[B[i]].push_back(A[i]);
  }

  dfs(T - 1, -1);
  for (int i = 0; i < N; ++i) {
    Flag(i + 1, mark[i]);
  }
}

void Bruno(int K, int S, int F, int L, int P[], int Q[]) {
  for (int i = 0; i < L; ++i) {
    if ((S <= P[i]) ^ F ^ Q[i]) {
      Answer(P[i]);
      return;
    }
  }
  Answer(S);
}
/*
int main() {
  int N, S, T, K;
  scanf("%d%d%d%d", &N, &S, &T, &K);
  std::vector<int> A(N - 1), B(N - 1);
  for (int i = 0; i < N - 1; ++i) scanf("%d%d", &A[i], &B[i]);
  Anna(K, N, T, &A[0], &B[0]);
  std::vector<int> P, Q;
  for (int i = 0; i < N - 1; ++i) {
    if (A[i] == S) P.push_back(B[i]);
    if (B[i] == S) P.push_back(A[i]);
  }
  for (auto &x: P) Q.push_back(mark[x]);
  Bruno(K, S, mark[S], P.size(), &P[0], &Q[0]);
  return 0;
}*/
