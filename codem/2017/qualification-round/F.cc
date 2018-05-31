#include <cstdio>
#include <string>
#include <queue>
#include <unordered_set>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::unordered_set<std::string> marked;

    auto resolve = [&] (std::string g, int x, int y, char c) {
      if (g[x * 19 + y] != '.') {
        puts("miss 1");
        return "";
      }
      g[x * 19 + y] = c;
      std::vector<std::vector<int>> me, other;
      std::vector<bool> visited(19 * 19);
      const int dx[] = {0, 0, 1, -1};
      const int dy[] = {1, -1, 0, 0};
      for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 19; ++j) {
          if (!visited[i * 19 + j] && g[i * 19 + j] != '.') {
            if (g[i * 19 + j] == c) me.push_back({});
            else other.push_back({});
            char now = g[i * 19 + j];
            static int queue[19 * 19];
            int head = 0, tail = 0;
            queue[tail++] = i * 19 + j;
            visited[i * 19 + j] = 1;
            for (; head < tail; ++head) {
              int x = queue[head] / 19, y = queue[head] % 19;
              if (now == c) me.back().emplace_back(queue[head]);
              else other.back().emplace_back(queue[head]);
              for (int k = 0; k < 4; ++k) {
                int xx = x + dx[k], yy = y + dy[k];
                if (xx < 0 || xx >= 19 || yy < 0 || yy >= 19) continue;
                if (g[xx * 19 + yy] != now || visited[xx * 19 + yy]) continue;
                queue[tail++] = xx * 19 + yy;
                visited[xx * 19 + yy] = 1;
              }
            }
          }
        }
      }
      for (auto &&group : other) {
        int cnt = 0;
        for (auto &&e : group) {
          for (int i = 0; i < 4; ++i) {
            int x = e / 19 + dx[i], y = e % 19 + dy[i];
            if (x >= 0 && x < 19 && y >= 0 && y < 19 && g[x * 19 + y] == '.') ++cnt;
          }
        }
        if (cnt == 0) {
          for (auto &&e : group) g[e] = '.';
        }
      }
      for (auto &&group : me) {
        int cnt = 0;
        for (auto &&e : group) {
          for (int i = 0; i < 4; ++i) {
            int x = e / 19 + dx[i], y = e % 19 + dy[i];
            if (x >= 0 && x < 19 && y >= 0 && y < 19 && g[x * 19 + y] == '.') ++cnt;
          }
        }
        if (cnt == 0) {
          puts("miss 2");
          return "";
        }
      }
      if (marked.count(g)) {
        puts("miss 3");
        return "";
      }
      return g.c_str();
    };

    std::string board(19 * 19, '.');
    for (int i = 0; i < n; ++i) {
      char col[10];
      int x, y;
      scanf("%s%d%d", col, &x, &y);
      std::string output = resolve(board, x - 1, y - 1, col[0]);
      if (output.empty()) continue;
      marked.insert(output);
      board = output;
    }
    for (int i = 0; i < 19; ++i) {
      for (int j = 0; j < 19; ++j) {
        putchar(board[i * 19 + j]);
      }
      puts("");
    }
  }
  return 0;
}
