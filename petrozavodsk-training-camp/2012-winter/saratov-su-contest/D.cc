#include <bits/stdc++.h>
 
const int N = 100;
const int M = 1001;
const int S = 2 * N * M;
 
int n, length[N], dp[S];
bool infinity, visiting[S];
char words[2][N][M], s[(N + 1) * M];
short _[M], ext[2][N][N * M];
 
int state(int t, int i, int j) { return t * N * M + i * M + j; }
 
// t = 1 suffix of length j
// t = 0 prefix of length j
int dfs(int t, int i, int j) {
  if (infinity) {
    return 0;
  }
  int s = state(t, i, j);
  int &ref = dp[s];
  if (ref == -1) {
    ref = 0;
    visiting[s] = true;
    for (int k = 0; k < n; ++k) {
      int z = ext[t][k][i * M + length[i] - j];
      ref = std::max(ref, z * 2);
#define GO(V, T, I, J)                                                         \
  if (z >= V) {                                                                \
    if (visiting[state(T, I, J)]) {                                            \
      infinity = true;                                                         \
      return 0;                                                                \
    }                                                                          \
    ref = std::max(ref, V * 2 + dfs(T, I, J));                                     \
  }
      if (j < length[k]) {
        GO(j, t ^ 1, k, length[k] - j);
      } else {
        GO(length[k], t, i, j - length[k]);
      }
    }
    visiting[s] = false;
  }
  return ref;
}
 
int main() {
#ifndef LOCAL_JUDGE
  //freopen("palindrome.in", "r", stdin);
  //freopen("palindrome.out", "w", stdout);
#endif
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%s", words[0][i]);
    length[i] = strlen(words[0][i]);
    for (int j = 0; j < length[i]; ++j) {
      words[1][i][j] = words[0][i][length[i] - 1 - j];
    }
  }
  int tlength = (n + 1) * M;
  for (int t = 1; t >= 0; --t) {
    for (int i = 0; i < tlength; ++i) s[i] = 0;
    for (int i = 0; i < n; ++i) {
      strcpy(s + (i + 1) * M, words[t ^ 1][i]);
    }
    for (int k = n - 1; k >= 0; --k) {
      short *e = ext[t][k] - M;
      for (int i = 0; i < M; ++i) s[i] = 0;
      strcpy(s, words[t][k]);
      s[length[k]] = '#';
      for (int i = 1, j = 0; i < tlength; ++i) {
        e[i] = i <= j + e[j] - 1
                   ? std::min(e[j - i], static_cast<short>(j + e[j] - i))
                   : 0;
        while (i + e[i] < tlength && s[e[i]] == s[i + e[i]]) {
          e[i]++;
        }
        if (j + e[j] < i + e[i]) {
          j = i;
        }
      }
    }
  }
  int result = 0;
  memset(dp, -1, sizeof(dp));
  // t = 0 prefix of length j
  // t = 1 suffix of length j
  // ... add manacher
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= length[i]; ++j) {
      if (ext[0][i][i * M + length[i] - j] >= j >> 1) {
        result = std::max(result, j + dfs(1, i, length[i] - j));
      }
      if (ext[1][i][i * M + length[i] - j] >= j >> 1) {
        result = std::max(result, j + dfs(0, i, length[i] - j));
      }
    }
  }
  printf("%d\n", infinity ? -1 : result);
}
