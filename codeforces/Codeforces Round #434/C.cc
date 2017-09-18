#include <cstdio>
#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

std::set<std::string> files[2];
std::vector<std::string> extra[2], empty[2];

int main() {
  int n;
  std::cin >> n;
  int sample = 0;
  for (int i = 0; i < n; ++i) {
    std::string name;
    int type;
    std::cin >> name >> type;
    files[type].insert(name);
    sample += type;
  }
  for (int i = 1; i <= n; ++i) {
    int type = i <= sample;
    std::string name = std::to_string(i);
    if (files[type].count(name)) {
      files[type].erase(name);
    } else if (files[type ^ 1].count(name)) {
      files[type ^ 1].erase(name);
      extra[type ^ 1].push_back(name);
    } else {
      empty[type].push_back(name);
    }
  }
  std::vector<std::pair<std::string, std::string>> ret;
  while (true) {
    bool update = false;
    for (int type = 0; type < 2; ++type) {
      while (!extra[type].empty() && !empty[type].empty()) {
        std::string x = extra[type].back();
        extra[type].pop_back();
        std::string y = empty[type].back();
        empty[type].pop_back();
        ret.emplace_back(x, y);
        empty[type ^ 1].push_back(x);
        update = true;
      }
    }
    if (!update) break;
  }
  for (int type = 0; type < 2; ++type) {
    while (!files[type].empty()) {
      std::string x = *files[type].begin();
      files[type].erase(files[type].begin());
      std::string y = empty[type].back();
      empty[type].pop_back();
      ret.emplace_back(x, y);
    }
  }
  if (!extra[0].empty()) {
    std::string tmp = "agfdzy";
    ret.emplace_back(extra[1].back(), tmp);
    for (int i = extra[0].size() - 2; i >= 0; --i) {
      ret.emplace_back(extra[0][i + 1], extra[1][i + 1]);
      ret.emplace_back(extra[1][i], extra[0][i + 1]);
    }
    ret.emplace_back(extra[0][0], extra[1][0]);
    ret.emplace_back(tmp, extra[0][0]);
  }
  printf("%d\n", (int)ret.size());
  for (auto &&e: ret) {
    printf("move %s %s\n", e.first.c_str(), e.second.c_str());
  }
  return 0;
}
