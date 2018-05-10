var mongoose = require("mongoose");
var multer = require("multer")
var fs = require("fs");
var bodyParser = require('body-parser');
var PythonShell = require("python-shell");
var ps = new PythonShell("public/init.py");

mongoose.Promise = require("bluebird");
/* mongodb connection */
/*
var db = mongoose.connection;
db.on('error', console.error);
db.once('open', () => { console.log('Connected to mongodb server'); });
*/
// mongoose.connect('mongodb://username:password@host:port/database=');

module.exports = function(app)
{
    app.get('/',function(req,res){
        res.render('index',{
            title : "Classification Prototype",
            isUp :false,
            imgs : "./imgs/ml_icons.jpg"
        })
    })

    app.post('/upload',multer({dest:'public/myfiletmp/upload/'}).single('upfile'),function(req,res){
	var options = {
	    mode : 'text',
	    pythonPath : '',
	    pythonOptions: ['-u'],
	    scriptPath :'',
	    args:['value1','value2','value3']
	};
	console.log("we running python...");
	ps.
	/*
        PythonShell.run("public/sum.py",options,function(err,results){
		if(err) console.log(err);
		console.log("results %j",results)
        })
	*/
        
        res.render('index',{
            title : "UPLOADED",
            isUp : true,
            imgs : "myfiletmp/upload/"+req.file.filename
        })
    })
}
