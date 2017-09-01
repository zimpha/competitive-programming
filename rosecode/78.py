import requests
from PIL import Image
import StringIO

login_url = 'http://www.javaist.com/rosecode/authenticate.php'

s = requests.session()
s.post(login_url, {'player': 'zimpha', 'password': 'linxiqwer', 'submit':'submit'}, headers = {})
r = s.get('http://www.javaist.com/rosecode/p78.php')
image = Image.open(StringIO.StringIO(r.content))
w, h = image.size
R, G, B = 0., 0., 0.
for i in xrange(h):
    for j in xrange(w):
        r, g, b = image.getpixel((j, i))
        R += r
        G += g
        B += b
print R, G, B
R /= w * h
G /= w * h
B /= w * h

payload = {'rgb': '%.2f:%.2f:%.2f' % (R, G, B), 'submit':'true'}
s.post('http://www.javaist.com/rosecode/p78.php', payload)
