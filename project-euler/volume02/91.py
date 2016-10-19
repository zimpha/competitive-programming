def sqr(x):
    return x * x

def check(x1, y1, x2, y2):
    a = sqr(x1) + sqr(y1)
    b = sqr(x2) + sqr(y2)
    c = sqr(x1 - x2) + sqr(y1 - y2)
    if a == 0 or b == 0 or c == 0:
        return 0
    if a + b == c or a + c == b or b + c == a:
        return 1
    else:
        return 0

def run(n):
    ret = 0
    for x1 in range(0, n + 1):
        for y1 in range(0, n + 1):
            for x2 in range(0, n + 1):
                for y2 in range(0, n + 1):
                    ret = ret + check(x1, y1, x2, y2)
    return ret

print run(2) / 2
print run(50) / 2
