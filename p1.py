import requests
url = 'http://www.sogang.ac.kr'
r = requests.get(url)
r.encoding= 'utf8'
print(r.text)
