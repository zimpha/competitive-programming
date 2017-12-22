def kill_the_remaining_chinese():
    X = 1
    for i in xrange(100):
        X *= i + 1
    Y = pow(X, 9449771607341027425, 9449771616229914661)
    return Y % 1000000008;

print kill_the_remaining_chinese()
