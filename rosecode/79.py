import requests

def area(a, b, c):
    return abs((c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]))

def solve(x):
    x = map(int, x.split(','))
    a, b, c = (x[0], x[1]), (x[2], x[3]), (x[4], x[5])
    o = (0, 0)
    return area(a, b, c) == area(o, a, b) + area(o, a, c) + area(o, b, c)

login_url = 'http://www.javaist.com/rosecode/authenticate.php'

s = requests.session()
s.post(login_url, {'player': 'zimpha', 'password': 'linxiqwer', 'submit':'submit'}, headers = {})
r = s.get('http://www.javaist.com/rosecode/p79.php')
tri = r.content.replace('<br>', '').replace('<html>', '').split()
ret = 0
for x in tri:
    ret += solve(x)

print ret
payload = {'amount': ret, 'submit79':'true'}
x = s.post('http://www.javaist.com/rosecode/p79.php', payload)
print x.content
