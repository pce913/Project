var express = require('express');
var mysql = require('mysql');
var aws = require('aws-sdk');
//var multer = require('multer');
//var multerS3 = require('multer-s3');
var db_config = require('../config/db_config.json');
//var datedate=require('date-utils');
var router = express.Router();

aws.config.loadFromPath('./config/aws_config.json');


var pool = mysql.createPool({
  host : db_config.host,
  port : db_config.port,
  user : db_config.user,
  password : db_config.password,
  database : db_config.database,
  connectionLimit : db_config.connectionLimit
});


router.post('/in_email', function(req, res, next) {               // 그냥 로그인
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{
     var crypto = require('crypto');
     var secret_key = 'butlerproject';
     var data = req.body.password;
     var encryption = crypto.createCipher('seed', secret_key);
     encryption.update(data, 'utf8', 'base64');
     var encryptionData = encryption.final('base64');
      connection.query('select * from user where user_email=? && user_password= ?',[req.body.email,encryptionData] ,function(error, rows){
        if (error){
          console.log("Connection Error" + error);
          res.sendStatus(500);
          connection.release();
        }
        else {

          var rlength=rows.length;
          console.log(rlength);
          console.log(req.body.email);
          console.log(req.body.password);
          if(rlength>0)
          res.status(201).send({result : true,
                                user_id: rows[0].user_id});
          else
          res.status(201).send({result : false,
                                user_id: null});


                          //rows에 데이터가 오는데 이것을 result에 저장해서 보낸다.
          connection.release();
        }
      });
    }
  });
});

router.post('/in_facebook', function(req, res, next) {               //  페이스북 로그인
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{
      connection.query('select * from user where user_facebook_id=?',[req.body.facebookid] ,function(error, rows){
        if (error){
          console.log("Connection Error" + error);
          res.sendStatus(500);
          connection.release();
        }
        else {

          var rlength=rows.length;
          console.log(rlength);
        //  var bool;
            if(rlength>0)
            res.status(201).send({result : true,
                                  user_id: rows[0].user_id});
            else
            res.status(201).send({result : false,
                                  user_id: null});

                        //rows에 데이터가 오는데 이것을 result에 저장해서 보낸다.
          connection.release();
        }
      });
    }
  });
});


router.post('/up_email', function(req, res, next) {               // 이메일 회원가입
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{
      connection.query('select * from user where user_email=?', [req.body.email], function(error, rows){
        if (error){
          console.log("Connection Error" + error);
          res.sendStatus(500);
          connection.release();
        }
        else {
          var rlength = rows.length;
          if (rlength > 0) {
            res.status(200).send({result : false});
          }
          else {
            var crypto = require('crypto');
            var secret_key = 'butlerproject';
            var data = req.body.password;
            // console.log("email:"+req.body.email);
            // console.log("name:"+req.body.name);
            // console.log("password: "+req.body.password);
            var encryption = crypto.createCipher('seed', secret_key);
            encryption.update(data, 'utf8', 'base64');
            var encryptionData = encryption.final('base64');
              connection.query('insert into user (user_email, user_password,user_name) value(?,?,?)', [req.body.email, encryptionData,req.body.name], function(error, rows){
                if (error){
                  console.log("Connection Error" + error);
                  res.sendStatus(500);
                  connection.release();
                }
                else {
                    res.status(200).send({result : true});
                  }
                  connection.release();
              });
          }
        }
      });
    }
  });
});

router.get('/info/:user_id', function(req, res, next) {               // 회원정보 보내기.
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{
      connection.query('select user_email,user_name,user_image_url from user where user_id=?',[req.params.user_id] ,function(error, rows){
        if (error){
          console.log("Connection Error" + error);
          res.sendStatus(500);
          connection.release();
        }
        else {

          var rlength=rows.length;
          if(rlength>0)
          res.status(201).send(rows[0]);
          else
          res.status(204).send({result : false});


                          //rows에 데이터가 오는데 이것을 result에 저장해서 보낸다.
          connection.release();
        }
      });
    }
  });
});


module.exports = router;
