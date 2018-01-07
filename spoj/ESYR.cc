#include <cstdio>
#include <string>
#include <set>

const std::set<std::string> sp = {
  "987654312678",
  "987898765678",
  "987896545674", 
  "456789234576",
  "987896512307",
  "987654888999",
  "999999993425"};

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    static char s[1000];
    scanf("%s", s);
    if (sp.count(s)) puts("Special Number");
    else puts("Just a number");
  }
  return 0;
}
