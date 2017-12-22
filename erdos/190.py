def semi_prime_sum(N):
  def f(n):
    return n * (n + 1) // 2 - 1

  v = int(N ** 0.5)
  ssum = [f(i) for i in range(v + 1)]
  lsum = [f(N // i) if i else 0 for i in range(v + 1)]

  ps = []
  for p in range(2, v + 1):
    if ssum[p] == ssum[p - 1]:
      continue
    ps.append(p)
    psum = ssum[p - 1]
    q = p * p
    end = min(v, N // q)
    for i in range(1, end + 1):
      d = i * p
      if d <= v:
        lsum[i] -= (lsum[d] - psum) * p
      else:
        t = N // d
        lsum[i] -= (ssum[t] - psum) * p
    for i in range(v, q - 1, -1):
      t = i // p
      ssum[i] -= (ssum[t] - psum) * p

  def get(u):
      return ssum[u] if u <= v else lsum[N / u]

  ret = 0
  s = 0
  for p in ps:
      ret += p * (get(N / p) - get(p - 1))
      s += p
      assert s == ssum[p]
  return ret

print semi_prime_sum(10 ** 7)
