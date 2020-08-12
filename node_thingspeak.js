request = require("request")

function doit() {
	v = Math.random() * 100
	
	url = "https://api.thingspeak.com/update?api_key=UGO0NIS0OJ75CVR0&field1="
	request(url + v, function(err, res, body) {
		console.log(body)
	})
	
	setTimeout(doit, 20000)
}

doit();

