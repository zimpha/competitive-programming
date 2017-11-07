for x in xrange(1, 100):
    for y in xrange(1, 100):
        for z in xrange(y + 1, 100):
            if -x * (-x + y) * (-x + z) + y * (-x + y) * (y + z) + z * (-x + z) * (y + z) == 4 * (-x + y) * (-x + z) * (y + z):
                print -x, y, z
