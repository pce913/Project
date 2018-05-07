var express = require('express');
var mysql = require('mysql');
var aws = require('aws-sdk');
// var multer = require('multer');
// var multerS3 = require('multer-s3');
var db_config = require('../config/db_config.json');

var router = express.Router();
var crypto = require('crypto');
var secret_key = 'bulter';
aws.config.loadFromPath('./config/aws_config.json');



var pool = mysql.createPool({
  host : db_config.host,
  port : db_config.port,
  user : db_config.user,
  password : db_config.password,
  database : db_config.database,
  connectionLimit : db_config.connectionLimit
});


router.get('/spot/:city_sight_id', function(req, res, next) {               // 상세정보 가져오기
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{

      connection.query('select sight_image_url from city_sight,city_sight_image where city_sight_id=? && city_sight_id=city_sight_id_fk && represent!=1',[req.params.city_sight_id] ,function(error, rows){
        if (error){
          console.log("Connection Error" + error);
          res.sendStatus(500);
        }
        else {
          var image_url_array=[];

          for(var i=0;i<rows.length;i++){
            image_url_array.push(rows[i].sight_image_url);              //image 포맷 맞추기
          }

          connection.query('select spot,spot_eng,address,information from city_sight where city_sight_id=?',[req.params.city_sight_id] ,function(error, rows){
            if (error){
              console.log("Connection Error" + error);
              res.sendStatus(500);
            }
            else {
              res.status(200).send({
                  image_url:image_url_array,
                  spot:rows[0].spot,
                  spot_eng:rows[0].spot_eng,
                  address:rows[0].address,
                  information:rows[0].information
                });
              connection.release();
            }
          });

        }
      });
    }
  });
});



router.post('/oneday', function(req, res, next) {               // 상세정보 가져오기
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{
      var query3='select spot, latitude, longitude from city_sight where';
      var arr=[];
      arr=req.body.spot;
      var arr2=[];
      for (var i=0;i<arr.length;i++) {
        query3+=' spot='+"'"+arr[i]+"'";
        if (i<arr.length-1) {
          query3+='||';
        }
      }
      connection.query(query3,function(error, rows){
        if (error){
          console.log("Connection Error" + error);
          res.sendStatus(500);
        }
        else {
          for (var j=0;j<arr.length;j++){
            for (var a=0;a<rows.length;a++){
              var input = arr[j];
              var output = rows[a].spot;
              if (input==output){
                arr2[j] = rows[a];
              }
            }
          }
          res.status(200).send(arr2);
          connection.release();
        }
      });
    }
  });
});

module.exports = router;
