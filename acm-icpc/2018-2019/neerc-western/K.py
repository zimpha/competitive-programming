def check(ops, x):
    r = x
    for (op, v) in ops:
        if v == "?":
            v = x
        else:
            v = int(v)
        if op == "add": r += v
        elif op == 'subtract': r -= v
        else: r *= v
    return r

n = int(input())
ops = []
for i in range(n):
    s = list(input().split())
    ops.append((s[0], s[-1]))

ret = set()
for x in range(-3000, 3000):
    ret.add(check(ops, x))
if len(ret) == 1:
    print(list(ret)[0])
else:
    print("Epic fail")
