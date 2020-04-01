const express = require('express');
const app = express();

const port =3000;

function getClientIP(req){
	return (req.headers['x-forwarded-for']||'').split(',')[0]||req.connection.remoteAddress;
}


app.get('/get',function(req,res){
//	var user_id = req.param('xx');


	const date = require('date-utils');
	var newDate = new Date();
	var time = newDate.toFormat('YYYY-MM-DD HH24:MI:SS');
	
	var myip= getClientIP(req);
	myip  = myip.substr(7);

	var status_code = '{  "email":"inseok9876@gmail.com", "stuno":"20121586", "time": "t",  "ip":"ii"  }';//static
	status_code.time = time;
	var obj = JSON.parse(status_code);//static becomes dynamic
	obj.time = time;
	obj.ip = myip;
	
	var status_query = status_code;

	var query = req.query;


//	res.send(query);
	var t_flag=false;
	for (var key in query){
		if(key in obj){
			if(query[key]==obj[key]){
				//console.log(`insek success`);//check
				//res.send(query);//check
				t_flag=true;	
			}
			else{
				t_flag=false;
			}
		}
		else{
			t_flag = false;
		}
	}
	if(t_flag){
		res.send(obj);
	}
	else{
		res.send("NOthing");
	}
	//check
	obj.time = time;//check
	console.log(`${obj.time}`);//check

	//console.log(` function(req,res)`);//check
	
});

//?
app.use(express.json())

app.post('',function(req,res){
	var myip = getClientIP(req)
	myip = myip.substr(7)

	req.body.stuno = "20121586"
	req.body.ip = myip
	req.body.time = currentDate
	req.body.email = "inseok9876@gmail.com"

	req.json(req.body)


});



//app.get('/',(req,res) =>{res.send(obj.time);});
app.listen(port,() =>console.log(`Example app listening on port ${port}!`));

