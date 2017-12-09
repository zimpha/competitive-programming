from heapq import *

n = int(input())
a = list(map(int, input().split()))
b = list(map(int, input().split()))

ret = n
for i in range(n):
    pq = [(x, 0) for x in a]
    heapify(pq)
    mx = 0
    for j in range(n):
        e = b[(i + j) % n]
        u = heappop(pq)
        u = (u[0] + e // 2, u[1] + 1)
        heappush(pq, u)
    mx = max([e[1] for e in pq])
    ret = min(ret, mx)
print(ret)
