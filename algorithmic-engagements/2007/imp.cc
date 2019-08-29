#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

const std::string flat_notes[] = {
  "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"
};

const std::string sharp_notes[] = {
  "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
};

const std::vector<std::set<int>> scale = {
  {0, 2, 4, 7, 9, 11},
  {0, 2, 3, 5, 7, 9, 10},
  {0, 2, 3, 5, 6, 8, 9, 11},
  {0, 2, 4, 7, 9, 10},
  {0, 1, 3, 4, 6, 7, 9, 10},
  {0, 1, 3, 4, 6, 8, 10}
};

int note_index(const std::string& s) {
  for (int i = 0; i < 12; ++i) {
    if (flat_notes[i] == s) return i;
    if (sharp_notes[i] == s) return i;
  }
  return -1;
}

bool is_flat(int i, const std::string& s) {
  return sharp_notes[i] != s;
}

int mode_index(const std::string& s) {
  if (s == "maj7") return 0;
  if (s == "min7") return 1;
  if (s == "dim") return 2;
  if (s == "7") return 3;
  if (s == "7b9") return 4;
  if (s == "7#9") return 5;
  return -1;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int m;
  std::cin >> m;
  std::vector<std::pair<std::string, int>> accords(m);
  for (int i = 0; i < m; ++i) {
    std::string s;
    std::cin >> s;
    size_t p;
    for (p = 0; p < s.size(); ++p) {
      if (s[p] == 'm' || s[p] == 'd' || s[p] == '7') break;
    }
    accords[i].first = s.substr(0, p);
    accords[i].second = mode_index(s.substr(p));
  }
  int n;
  std::cin >> n;
  for (int i = 0, j = 0; i < n; ++i) {
    if (i) std::cout << " ";
    std::string s;
    std::cin >> s;
    if (s == "_") {
      std::cout << s;
    } else {
      int a = note_index(s);
      int b = note_index(accords[j].first);
      int best = -1;
      for (int k = 0; ; ++k) {
        int c = (k + 1) / 2;
        if (k % 2 == 0) c = -c;
        c = (a + c + 12) % 12;
        int d = c - b;
        if (d < 0) d += 12;
        if (scale[accords[j].second].count(d)) {
          best = c;
          break;
        }
      }
      if (is_flat(b, accords[j].first)) std::cout << flat_notes[best];
      else std::cout << sharp_notes[best];
      if ((i + 1) % 4 == 0) j = (j + 1) % m;
    }
  }
  std::cout << std::endl;
  return 0;
}
