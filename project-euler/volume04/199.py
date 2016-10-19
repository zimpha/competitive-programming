# Descartes' theorem
import math

def circle_type0(r1, r2, r3):
    k1, k2, k3 = 1 / r1, 1 / r2, 1 / r3
    k4 = k1 + k2 + k3 + math.sqrt(k1 * k2 + k2 * k3 + k3 * k1) * 2
    return 1 / k4

def circle_type1(r4, r1, r2):
    k1, k2, k4 = 1 / r1, 1 / r2, -1 / r4
    k31 = k1 + k2 + k4 + 2 * math.sqrt(k1 * k2 + k2 * k4 + k4 * k1)
    k32 = k1 + k2 + k4 - 2 * math.sqrt(k1 * k2 + k2 * k4 + k4 * k1)
    return 1 / max(k31, k32)

def sort3(a, b, c):
    if a > b:
        a, b = b, a
    if a > c:
        a, c = c, a
    if b > c:
        b, c = c, b
    return a, b, c

def run(circles, it):
    if it == 0:
        return 0
    new = []
    ret = 0
    for e in circles:
        r1, r2, r3 = e[0], e[1], e[2]
        if e[3] == 0:
            r1, r2, r3 = sort3(r1, r2, r3)
            r4 = circle_type0(r1, r2, r3)
            ret += r4 * r4 * e[4]
            if r1 == r3:
                new.append((r1, r1, r4, 0, 3 * e[4]))
            elif r1 == r2:
                new.append((r1, r3, r4, 0, 2 * e[4]))
                new.append((r1, r2, r4, 0, e[4]))
            elif r2 == r3:
                new.append((r1, r3, r4, 0, 2 * e[4]))
                new.append((r2, r3, r4, 0, e[4]))
            else:
                new.append((r1, r2, r4, 0, e[4]))
                new.append((r2, r3, r4, 0, e[4]))
                new.append((r3, r1, r4, 0, e[4]))
        else:
            r4 = circle_type1(r1, r2, r3)
            ret += r4 * r4 * e[4]
            if r2 == r3:
                new.append((r4, r2, r3, 0, e[4]))
                new.append((r1, r2, r4, 1, e[4] * 2))
            else:
                new.append((r4, r2, r3, 0, e[4]))
                new.append((r1, r2, r4, 1, e[4]))
                new.append((r1, r3, r4, 1, e[4]))
    return ret + run(new, it - 1)



r = math.sqrt(3) / (2 + math.sqrt(3))
print 1 - r * r * 3 - run([(r, r, r, 0, 1), (1, r, r, 1, 3)], 3)
print 1 - r * r * 3 - run([(r, r, r, 0, 1), (1, r, r, 1, 3)], 10)
