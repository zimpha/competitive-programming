#include "mon.h"
#include <algorithm>

void solve1(char a, char b, char c, char d, char e) {
  // a > c > d > e
  if (lzejsza(b, d)) {
    if (lzejsza(b, e)) wynik(b, e, d, c, a);
    else wynik(e, b, d, c, a);
  } else {
    if (lzejsza(b, c)) wynik(e, d, b, c, a);
    else wynik(e, d, c, b, a);
  }
}

void solve2(char a, char b, char c, char d, char e) {
  // e > a > c > d
  if (lzejsza(b, c)) {
    if (lzejsza(b, d)) wynik(b, d, c, a, e);
    else wynik(d, b, c, a, e);
  } else {
    wynik(d, c, b, a, e);
  }
}

void sortujMonety() {
  char a = 'A', b = 'B', c = 'C', d = 'D', e = 'E';
  if (lzejsza(a, b)) std::swap(a, b);
  if (lzejsza(c, d)) std::swap(c, d);
  if (lzejsza(a, c)) {
    std::swap(a, c);
    std::swap(b, d);
  }
  if (lzejsza(e, c)) {
    if (lzejsza(d, e)) {
      std::swap(e, d);
    }
    solve1(a, b, c, d, e);
  } else {
    if (lzejsza(e, a)) {
      std::swap(c, e);
      std::swap(e, d);
      solve1(a, b, c, d, e);
    } else {
      solve2(a, b, c, d, e);
    }
  }
}
