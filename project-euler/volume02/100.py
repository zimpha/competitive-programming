x, y = 1, 1
while True:
    x, y = 3 * x + 2 * y, 4 * x + 3 * y
    if x % 2 == 1 and y % 2 == 1:
        B = (x + 1) / 2
        T = (y + 1) / 2
        if T > 1e12:
            print B
            break
