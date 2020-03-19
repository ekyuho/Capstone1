import requests

url = "https://api.thingspeak.com/update?api_key=U2MVHNEQWUGDEWRF&field1=77" #77을 데이터를 보내는 api

requests.get(url)
