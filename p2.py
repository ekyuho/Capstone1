import requests
url = '127.0.0.1'
r = requests.get(url)
r.encoding= 'utf8'
print(r.text)
