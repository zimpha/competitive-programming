import sys

q = int(raw_input())
for i in xrange(q):
    x1, x2, y1, y2 = map(int, raw_input().split(' '))
    print 'SELECT count(*) FROM point WHERE x >= %d and x <= %d and y >= %d and y <= %d;' % (x1, x2, y1, y2)
    sys.stdout.flush()

