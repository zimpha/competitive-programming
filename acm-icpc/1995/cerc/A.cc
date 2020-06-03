#include <cstdio>
#include <cstring>

struct cal {
  int d, m, y;
};

cal haab, tzol;
char *tzol_month[] = {"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"};

int haab_month(char *s) {
  if (strcmp(s,"pop") == 0) return 0;
  if (strcmp(s,"no") == 0) return 1;
  if (strcmp(s,"zip") == 0) return 2;
  if (strcmp(s,"zotz") == 0) return 3;
  if (strcmp(s,"tzec") == 0) return 4;
  if (strcmp(s,"xul") == 0) return 5;
  if (strcmp(s,"yoxkin") == 0) return 6;
  if (strcmp(s,"mol") == 0) return 7;
  if (strcmp(s,"chen") == 0) return 8;
  if (strcmp(s,"yax") == 0) return 9;
  if (strcmp(s,"zac") == 0) return 10;
  if (strcmp(s,"ceh") == 0) return 11;
  if (strcmp(s,"mac") == 0) return 12;
  if (strcmp(s,"kankin") == 0) return 13;
  if (strcmp(s,"muan") == 0) return 14;
  if (strcmp(s,"pax") == 0) return 15;
  if (strcmp(s,"koyab") == 0) return 16;
  if (strcmp(s,"cumhu") == 0) return 17;
  if (strcmp(s,"uayet") == 0) return 18;
}

int main() {
  int T;
  scanf("%d", &T);
  printf("%d\n", T);
  for (int cas = 1; cas <= T; ++cas) {
    char m[10];
    scanf("%d. %s%d", &haab.d, m, &haab.y);
    haab.m = haab_month(m);
    int day = haab.y * 365 + haab.m * 20 + haab.d;
    tzol.y = day / 260;
    tzol.d = day % 13 + 1;
    tzol.m = day % 20;
    printf("%d %s %d\n", tzol.d, tzol_month[tzol.m], tzol.y);
  }
  return 0;
}
