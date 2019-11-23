#include <iostream>
#include <string>
#include <vector>
#include <map>

std::map<std::vector<int>, int> cache;

int query(const std::vector<int>& q) {
  if (cache.count(q)) return cache[q];
  std::cout << "?";
  for (size_t i = 0; i < q.size(); ++i) {
    if (q[i]) std::cout << " " << i + 1;
  }
  std::cout << std::endl;
  std::string res;
  std::cin >> res;
  return cache[q] = (res[0] == 'R');
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> q(n * 2);
  std::string s(n * 2, '?');
  for (int i = 0; i < n; ++i) q[i] = 1;
  auto first = query(q);
  int left = 1, right = n;
  while (left < right) {
    int mid = (left + right - 1) >> 1;
    q.assign(n * 2, 0);
    for (int i = 0; i < n; ++i) q[mid + i] = 1;
    auto res = query(q);
    if (res == first) left = mid + 1;
    else right = mid;
  }
  q.assign(n * 2, 0);
  for (int i = 0; i < n; ++i) q[left + i] = 1;
  int l = left - 1, r = l + n, last = first ^ 1;
  s[l] = "BR"[first];
  s[r] = "BR"[first ^ 1];
  for (int i = 0; i < n * 2; ++i) {
    if (i >= l && i <= r) continue;
    q[r] = 0; q[i] = 1;
    auto now = query(q);
    if (now == last) s[i] = s[r];
    else s[i] = 'B' + 'R' - s[r];
    q[r] = 1; q[i] = 0;
  }
  last ^= 1;
  for (int i = 0; i < n * 2; ++i) q[i] ^= 1;
  for (int i = l + 1; i < r; ++i) {
    q[i] = 1; q[l] = 0;
    auto now = query(q);
    if (now == last) s[i] = s[l];
    else s[i] = 'B' + 'R' - s[l];
    q[i] = 0; q[l] = 1;
  }
  std::cout << "! " << s << std::endl;
  return 0;
}
