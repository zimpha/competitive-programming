fs = open('network.txt', 'r')
g = []
total = 0
for l in fs:
    s = l.strip().split(',')
    nl = [1e9] * 40
    for i in xrange(40):
        if s[i] != '-':
            nl[i] = int(s[i])
            total += int(s[i])
    g.append(nl)
for i in xrange(40):
    g[i][i] = 0
vis = [0] * 40
dis = g[0]
vis[0] = 1
remain = 0
for i in xrange(1, 40):
    mx = -1
    for j in xrange(40):
        if vis[j] == 0 and (mx == -1 or dis[j] < dis[mx]):
            mx = j
    vis[mx] = 1
    remain += dis[mx]
    for j in xrange(40):
        if vis[j] == 0 and g[mx][j] < dis[j]:
            dis[j] = g[mx][j]
print total / 2 - remain
