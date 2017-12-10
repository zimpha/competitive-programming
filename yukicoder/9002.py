n = int(raw_input())
a = ord('p') - ord('a')
b = ord('d') - ord('a')
c = ord('f') - ord('a')
d = ord('b') - ord('a')
for i in xrange(d, n + d):
    if not (i % a):
        print 'FizzBuzz'
    elif not (i % b):
        print 'Fizz'
    elif not (i % c):
        print 'Buzz'
    else:
        print i
