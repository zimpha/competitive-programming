for _ in xrange(int(raw_input())):
  n, k = map(int, raw_input().split())
  if (n - 1) % (k + 1) == 0: print 'Lose'
  else: print 'Win'
