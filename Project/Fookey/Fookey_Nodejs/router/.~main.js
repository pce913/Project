var mongoose = require("mongoose");
var multer = require("multer")
var fs = require("fs");
var bodyParser = require('body-parser');
var cmd = require('node-cmd');

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
	console.log("we running python...");
	var pyProcess = cmd.get("python public/fookey1/singlecl3.py ../myfiletmp/upload/"+req.file.filename,function(data,err,stderr){
   	    if(!err){
		console.log("data from python script" +data)
		res.render('index',{
			title : data,
			isUp : true,
			imgs : "myfiletmp/upload/"+req.file.filename
		})
	    }
	    else{
		console.log("python script cmd error : " +err)
		res.render('index',{
			title : err,
			isUp : true,
			imgs : "myfiletmp/upload/"+req.file.filename
		})
	    }
	});
    })
}
