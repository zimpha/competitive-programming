import sys

def run(x1, y1, x2, y2, L):
    u, v = x1 * y2 + x2 * y1, y1 * y2 * 2
    if x1 * 100 >= y1 or v > L or (x1 == 0 and y2 * y2 * 2 >= L):
        return 0
    ret = 0
    if x1 != 0 and v > u * 100:
        ret = 1
    u, v = x1 + x2, y1 + y2
    ret += run(x1, y1, u, v, L)
    ret += run(u, v, x2, y2, L)
    return ret

sys.setrecursionlimit(100000)
print run(0, 1, 1, 1, 10 ** 8) + 10 ** 8 / 2 - 50
