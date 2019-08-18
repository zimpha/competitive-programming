from cmath import complex

def solve(a1, b1, a2, b2):
    u = complex(1, 0)
    v = complex(0, 1)
    while not (a1 > b1 and a2 < b2):
        if a2 >= b2:
            k = a2 // b2
            v = k * u + v
            a1 -= k * b1
            a2 -= k * a2
        else:
            assert a1 <= b1
            k = b1 // a1
            u = u + k * v
            b1 -= k * a1
            b2 -= k * a2
    return u, v
