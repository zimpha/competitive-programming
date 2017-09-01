import requests

login_url = 'http://www.javaist.com/rosecode/authenticate.php'

s = requests.session()
s.post(login_url, {'player': 'zimpha', 'password': 'linxiqwer', 'submit':'submit'}, headers = {})
r = s.get('http://www.javaist.com/rosecode/p83.php')
ret = ''
for x in r.text.split():
    print x, int(x, 2)
    for i in xrange(0, len(x), 8):
        v = chr(int(x[i: i + 8][::-1], 2))
        if (v >= 'a' and v <= 'z') or (v >= 'A' and v <= 'Z'):
            ret += v

print ret
payload = {'ans': ret, 'submit83':'true'}
r = s.post('http://www.javaist.com/rosecode/p83.php', payload)
print r.text
