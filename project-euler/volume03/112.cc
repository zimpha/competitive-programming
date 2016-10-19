#include <bits/stdc++.h>
using namespace std;

bool inc(int n) {
  int y = 100;
  while (n) {
    int x = n % 10;
    if (x > y) return false;
    y = x; n /= 10;
  }
  return true;
}
bool dec(int n) {
  int y = -1;
  while (n) {
    int x = n % 10;
    if (x < y) return false;
    y = x; n /= 10;
  }
  return true;
}

int calc(int a, int b) {
  for (int n = 1, cnt = 0; ; ++n) {
    if (inc(n) || dec(n)) ++cnt;
    if ((n - cnt) * b == a * n) return n;
  }
  return -1;
}

int main() {
  printf("%d\n", calc(1, 2));
  printf("%d\n", calc(90, 100));
  printf("%d\n", calc(99, 100));
}
