#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include "grader.h"

void getProgram() {
  int n;
  scanf("%d", &n);
  std::vector<int> stk;
  stk.push_back(1);
  std::string s(n, '(');
  for (int i = 2; i <= n; ++i) {
    if (stk.empty()) stk.push_back(i);
    else {
      printf("? %d %d\n", stk.back(), i);
      fflush(stdout);
      char res[10];
      scanf("%s", res);
      if (res[0] == 'Y') s[i - 1] = ')', stk.pop_back();
      else stk.push_back(i);
    }
  }
  printf("! %s\n", s.c_str());
  fflush(stdout);
}
