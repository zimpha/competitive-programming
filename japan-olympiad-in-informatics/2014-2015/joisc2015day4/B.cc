#include "Memory_lib.h"
/*
#include <cstdio>
#include <cstring>

char s[1000];

char Get(int i) {
  return s[i - 1];
}
*/

int Memory(int N, int M) {
  if (N % 2 == 1) return -2;
  int call = M % (1 << 13);
  int d = call / N + 1, i = call % N;
  if (d > N / 2) return -1;
  int cnt = (M >> 13) % (1 << 7);
  int rec = (M >> 20);
  if (cnt > N / 2) return -2;
  char c = Get(i + 1);
  if (c == '<' || c == '[') {
    ++cnt;
    if (cnt == d) rec = (c == '<');
  } else {
    if (cnt == d) {
      if (rec && c != '>') return -2;
      if (!rec && c != ']') return -2;
    }
    cnt--;
  }
  if (cnt < 0) return -2;
  if (i == N - 1 && cnt != 0) return -2;
  call++;
  return call + (cnt << 13) + (rec << 20);
}
/*
int main() {
  scanf("%s", s);
  int n = strlen(s);
  int m = 0;
  int cnt = 0;
  for (; cnt < 15000; ++cnt) {
    m = Memory(n, m);
    if (m < 0) break;
  }
  printf("%d\n", m);
  return 0;
}*/
