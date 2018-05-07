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


router.get('/:user_id', function(req, res, next) {               // 상세정보 가져오기
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{
      var today = new Date();
      var today_date = parseInt((today.getTime()+9*60*60*1000)/(1000*60*60*24));
      connection.query('select start_date,end_date from recommend where user_id_fk=?',[req.params.user_id] ,function(error, rows){
        if (error){
          console.log("Connection Error" + error);
          res.sendStatus(500);
        }
        else {
          var length = rows.length;
          if (length>0){
            var startDate = new Date(rows[0].start_date);
            var endDate = new Date(rows[0].end_date);
            var startDate_date = parseInt(startDate.getTime()/(1000*60*60*24));
            var endDate_date = parseInt(endDate.getTime()/(1000*60*60*24));
            if (startDate_date<=today_date && today_date<=endDate_date){
              var day = today_date - startDate_date + 1;
              res.status(200).send({day : day});
            }
            else {
                res.status(200).send({day : 0});
            }
          }
          else {
              res.status(200).send({day : 0});
          }
            connection.release();
          }
        });

      }
  });
});

router.get('/weather/:user_id', function(req, res, next) {               // 여행 당일 메인페이지 날씨정보 클라이언트에 전송하기.
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{
      connection.query('select city_eng,city_latitude,city_longitude from city_info,recommend,user where user_id=? && user_id=user_id_fk && city_info_id=recommend.city_info_id_fk',[req.params.user_id] ,function(error, rows){
        if (error){
          console.log("Connection Error" + error);
          res.sendStatus(500);
          connection.release();
        }
        else {
          res.status(200).send(rows);
                          //rows에 데이터가 오는데 이것을 result에 저장해서 보낸다.
          connection.release();
        }
      });
    }
  });
});


router.post('/route', function(req, res, next) {               // 여행 당일 메인페이지 루트 클라이언트에 전송하기.
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{
      console.log(req.body.user_id);
      console.log(req.body.day);
      connection.query('select recommend_spot,latitude,longitude from user,recommend,recommend_onenight,recommend_onenight_route,city_sight where user_id =? && user_id=user_id_fk && recommend_id=recommend_id_fk && day=? && onenight_id=onenight_id_fk && recommend_spot=spot order by sequence',[req.body.user_id,req.body.day] ,function(error, rows){
        if (error){
          console.log("Connection Error" + error);
          res.sendStatus(500);
          connection.release();
        }
        else {
          console.log(rows);
          res.status(200).send(rows);
                          //rows에 데이터가 오는데 이것을 result에 저장해서 보낸다.
          connection.release();
        }
      });
    }
  });
});

module.exports = router;
