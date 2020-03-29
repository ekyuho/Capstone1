import requests
from random import *
import time

url = "https://api.thingspeak.com/update?api_key=U2MVHNEQWUGDEWRF&field1="
#r = requests.get(url)
#r.encoding = 'utf8'

for i in range(10) :
        value = randint(1,100)
        requests.get(url+str(value))
        time.sleep(20)
