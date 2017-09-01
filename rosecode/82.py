import requests

def S(n, m):
    rad = [1] * (m + 1)
    for i in xrange(2, m + 1):
        if rad[i] != 1: continue
        for j in xrange(i, m + 1, i):
            rad[j] *= i
    rad = rad[1:]
    rad = [(x, i + 1) for i, x in enumerate(rad)]
    rad.sort()
    return rad[n - 1][1]

print S(3, 10)
print S(7, 10)

login_url = 'http://www.javaist.com/rosecode/authenticate.php'

s = requests.session()
s.post(login_url, {'player': 'zimpha', 'password': 'linxiqwer', 'submit':'submit'}, headers = {})
r = s.get('http://www.javaist.com/rosecode/p82.php')
m, n = r.text.split()
m, n = int(m[2:]), int(n[2:])

payload = {'ans': S(n, m), 'submit82':'true'}
s.post('http://www.javaist.com/rosecode/p82.php', payload)
