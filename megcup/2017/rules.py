import numpy as np
import math

player = {}
final = {}
score = [0]
pid = [0] * 8
valid = 1
last = 0
sz = 0

his = []
for tot in xrange(430):
    x = raw_input()
    t, s, id = x.split(' ')
    t = float(t)
    id = int(id)

    for x in player:
        e = player[x]
        if not (x in final):
            final[x] = 0
        final[x] += (t - last) * score[e + valid]

    if not (s in player):
        player[s] = sz
        sz += 1

    his.append((t, s, id))
    cnt = [0] * 8
    for x in his:
        cnt[x[2]] += 1
    valid = 1
    for i in xrange(8):
        if cnt[i] > 0:
            pid[i] = valid
            valid += 1
    n = valid + len(player)
    A = np.zeros((n, n))
    A[0][0] = 1
    for i in xrange(8):
        if cnt[i] > 0:
            s = 0
            for j in xrange(cnt[i]):
                s += 1.0 / (j + 1)
            A[0][pid[i]] = cnt[i]
            A[pid[i]][0] = s
    for x in his:
        u = pid[x[2]]
        v = player[x[1]] + valid
        A[v][u] = 1
        A[u][v] = 1.0 / cnt[x[2]]
    for i in xrange(n):
        s = np.sum(A[i])
        for j in xrange(n):
            A[i][j] /= s
    P = A.copy()
    for i in xrange(n):
        for j in xrange(n):
            P[i][j] = -P[i][j]
        P[i][i] = 1 - P[i][i]
    P = np.linalg.inv(P)
    score = [0] * n
    for i in xrange(n):
        for j in xrange(n):
            score[i] += P[0][j] * A[j][i]
    s = np.sum(score)
    for i in xrange(n):
        score[i] /= s
        score[i] *= (tot + 1)
    last = t
t = 22 * 60 * 60
for x in player:
    e = player[x]
    if not (x in final):
        final[x] = 0
    final[x] += (t - last) * score[e + valid]
print final
h = []
for x in final:
    h.append([final[x], x, 0])
h.sort()
h.reverse()
m = min(32, len(player))
avg = 0
for i in xrange(m):
    avg += h[i][0]
avg /= m
s = 0
for i in xrange(m):
    s += (h[i][0] - avg) ** 2
s = np.sqrt(s / m)
sss = 0
for i in xrange(m):
    h[i][2] = math.exp(h[i][0] / s)
    sss += h[i][2]
for i in xrange(m):
    h[i][2] = 88888 * h[i][2] / sss
for i in xrange(len(h)):
    print (i + 1), h[i][1], h[i][0], h[i][2]
