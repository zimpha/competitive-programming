x, y = map(int, input().split())
ret = 0
if x == 1: ret += 300000
if x == 2: ret += 200000
if x == 3: ret += 100000
if y == 1: ret += 300000
if y == 2: ret += 200000
if y == 3: ret += 100000
if x == 1 and y == 1: ret += 400000
print(ret)
