#include <bits/stdc++.h>

const int N = 1 << 20, M = 100000007;
int dis[N], checksum[N], cnt[N];

const char dir[] = "URDL";
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, -1, 0, 1};

int run(int src, int tar) {
  for (int i = 0; i < N; ++i) dis[i] = -1;
  dis[src] = 0, checksum[src] = 0, cnt[src] = 1;
  std::queue<int> queue;
  queue.push(src);
  for (; !queue.empty(); queue.pop()) {
    int now = queue.front();
    int x = now >> 2 & 3, y = now & 3;
    int decode[16];
    for (int i = 0; i < 16; ++i) decode[i] = now >> 4 >> i & 1;
    if (now == tar) return checksum[now];
    for (int k = 0; k < 4; ++k) {
      int xx = x + dx[k], yy = y + dy[k];
      if (xx < 0 || xx > 3 || yy < 0 || yy > 3) continue;
      std::swap(decode[x * 4 + y], decode[xx * 4 + yy]);
      int tmp = 0;
      for (int i = 0; i < 16; ++i) tmp |= decode[i] << i;
      tmp = (tmp << 4) | (xx << 2) | yy;
      if (dis[tmp] == -1) {
        dis[tmp] = dis[now] + 1;
        cnt[tmp] = cnt[now];
        checksum[tmp] = (checksum[now] * 243ll + 1ll * dir[k] * cnt[now]) % M;
        queue.push(tmp);
      } else if (dis[tmp] == dis[now] + 1) {
        checksum[tmp] += (checksum[now] * 243ll + 1ll * dir[k] * cnt[now]) % M;
        cnt[tmp] += cnt[now];
        checksum[tmp] %= M;
        cnt[tmp] %= M;
      }
      std::swap(decode[x * 4 + y], decode[xx * 4 + yy]);
    }
  }
  return -1;
}

int main() {
  std::cout << run(0b00110011001100100000, 0b10100101101001000000) << std::endl;
  return 0;
}
