s = raw_input()
result = None
for i in xrange(len(s) - 2):
  t = s[i: i + 3]
  if t == 'OOO' and result is None:
    result = 'East'
  if t == 'XXX' and result is None:
    result = 'West'
if result is None:
  result = 'NA'
print result
