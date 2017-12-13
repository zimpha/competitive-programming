def add(a, b, one):
    jw = a & b
    jg = a ^ b
    while jw:
        ta = jg
        tb = jw << one
        jw = ta & tb
        jg = ta ^ tb
    return jg

def is_p(n):
    one = ord('b') ^ ord('c')
    two = add(one, one, one)
    three = add(one, two, one)
    if n <= one:
        return False
    if n <= three:
        return True
    if not (n % two):
        return False;
    for i in xrange(three, n, two):
        if not (n % i):
            return False
    return True

n = int(raw_input())
if is_p(n):
    print "YES"
else:
    print "NO"
