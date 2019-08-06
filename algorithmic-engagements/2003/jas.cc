#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>

int main() {
  std::vector<char> step;
  while (true) {
    char c;
    scanf(" %c", &c);
    if (c == 'P') continue;
    if (c == 'K') break;
    step.push_back(c);
  }
  if (step.empty()) {
    puts("0");
    return 0;
  }
  step.push_back(step[0]);
  int x = 0, y = 0;
  std::map<int, std::vector<int>> bound;
  for (size_t i = 1; i < step.size(); ++i) {
    if (step[i - 1] == 'E' && step[i] != 'S') bound[x].push_back(y);
    else if (step[i - 1] == 'W' && step[i] != 'N') bound[x].push_back(y);
    else if (step[i - 1] == 'S' && step[i] != 'S' && step[i] != 'W') bound[x].push_back(y);
    else if (step[i - 1] == 'N' && step[i] != 'N' && step[i] != 'E') bound[x].push_back(y);
    if (step[i - 1] == 'W' && step[i] == 'E') bound[x].push_back(y);
    if (step[i - 1] == 'E' && step[i] == 'W') bound[x].push_back(y);
    if (step[i] == 'N') ++y;
    else if (step[i] == 'S') --y;
    else if (step[i] == 'E') ++x;
    else --x;
  }
  int ret = 0;
  for (auto &e: bound) {
    auto &ys = e.second;
    std::sort(ys.begin(), ys.end());
    for (size_t i = 1; i < ys.size(); i += 2) {
      ret += ys[i] - ys[i - 1] + 1;
    }
  }
  printf("%d\n", ret);
  return 0;
}
