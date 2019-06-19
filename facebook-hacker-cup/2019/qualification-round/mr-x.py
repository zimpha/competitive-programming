def valid(e):
  return eval(e.replace('x', '0').replace('X', '1')) == eval(e.replace('x', '1').replace('X', '0'))

T = int(raw_input())
for cas in xrange(1, T + 1):
  e = raw_input()
  ret = not valid(e)
  print 'Case #{}: {}'.format(cas, int(ret))
