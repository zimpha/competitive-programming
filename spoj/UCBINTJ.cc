#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 10;
const char *s = "ACGT";
char dna[MAXN];

int main() {
  int cnt[4], n; scanf("%d%s", &n, dna);
  memset(cnt, 0, sizeof(cnt));
  for (int i = 0; i < n; ++ i) {
    if (dna[i] == 'A') cnt[0] ++;
    else if (dna[i] == 'C') cnt[1] ++;
    else if (dna[i] == 'G') cnt[2] ++;
    else cnt[3] ++;
  }
  int mx = 0;
  for (int i = 0; i < 4; ++ i) {
    if (cnt[i] < cnt[mx]) mx = i;
  }
  for (int i = 0; i < n; ++ i) dna[i] = s[mx];
  printf("%d\n%s\n", cnt[mx], dna);
  return 0;
}
