var express = require('express');
var mysql = require('mysql');
var aws = require('aws-sdk');
//var multer = require('multer');
//var multerS3 = require('multer-s3');
var db_config = require('../config/db_config.json');
//var datedate=require('date-utils');
var router = express.Router();
var async=require('async');

aws.config.loadFromPath('./config/aws_config.json');


var pool = mysql.createPool({
  host : db_config.host,
  port : db_config.port,
  user : db_config.user,
  password : db_config.password,
  database : db_config.database,
  connectionLimit : db_config.connectionLimit
});

var ri;
router.post('/save_schedule', function(req, res, next) {              // 사용자가 만든 스케쥴을 서버에 저장하기.       새롭게 저장할때 recommend 삭제후에 다시 생성한다.
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{
      // var sdate=new Date(req.body.start_date);                         //클라이언트에서 format을 "2017/1/4" 이런식으로 맞춰서 보내달라고 하기.
      // var edate=new Date(req.body.end_date);
      // var onenight=edate.getTime()/(1000*60*60*24)-sdate.getTime()/(1000*60*60*24)+1;
      // var schedule=req.body.schedule;
    //  console.log(schedule);
    console.log(req.body.user_id);
    console.log(req.body.start_date);
    console.log(req.body.end_date);
    console.log(req.body.schedule);
      async.series([
        function(callback){
          deleteRecommend(connection,req,res,callback);
          callback(null,null);
        },
        function(callback){
          insertRecommend(connection,req,res,callback);
          callback(null,null);
        },
        function(callback){
          insertRecommendOnenight(connection,req,res,callback);
          callback(null,null);
        },
        function(callback){
          insertRecommendOnenightRoute(connection,req,res,callback);
          callback(null,null);
        }
      ]);

    }
  });
});

router.get('/show_schedule/:user_id', function(req, res, next) {               // 사용자의 스케쥴을 사용자에게 보내준다.
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{

      connection.query('select recommend_spot,day,count(*) from user,recommend,recommend_onenight,recommend_onenight_route where user_id=? && user_id=user_id_fk && recommend_id=recommend_id_fk && onenight_id=onenight_id_fk group by day', [req.params.user_id], function(error, rows){  // group by day order by sequence
        if (error){
          console.log("Connection Error" + error);
          res.sendStatus(500);
          connection.release();
        }
        else {
            var count=[];
            for(var i=0;i<rows.length;i++){
              console.log(rows[i]["count(*)"]);
              count.push(rows[i]["count(*)"]);
            }
            connection.query('select recommend_spot,day,count(onenight_id_fk) from user,recommend,recommend_onenight,recommend_onenight_route where user_id=? && user_id=user_id_fk && recommend_id=recommend_id_fk && onenight_id=onenight_id_fk group by onenight_id_fk,sequence order by day,sequence', [req.params.user_id], function(error, rows){  // group by day order by sequence
              if (error){
                console.log("Connection Error" + error);
                res.sendStatus(500);
                connection.release();
              }
              else {
                console.log(rows.length);
                for(var i=0;i<rows.length;i++){
                  console.log(rows[i].recommend_spot);
                }

                  var realSchedules=[];
                  var k=0;
                  for(var i=0;i<count.length;i++){
                    var tempSpotArray=[];
                  //  console.log(rows[k].recommend_spot);
                    for(var j=0;j<count[i];j++){
                      tempSpotArray.push(rows[k].recommend_spot);
                      k++;
                    }
                    realSchedules.push(tempSpotArray);

                  }

                //  console.log({schedules:realSchedules});

                  res.status(200).send({schedules:realSchedules});
              }
            });
        }
      });

    }
  });
});



function insertRecommend(connection,req,res,callback){
  var sdate=new Date(req.body.start_date);                         //클라이언트에서 format을 "2017/1/4" 이런식으로 맞춰서 보내달라고 하기.
  var edate=new Date(req.body.end_date);
  var onenight=edate.getTime()/(1000*60*60*24)-sdate.getTime()/(1000*60*60*24)+1;
  connection.query('insert into recommend(user_id_fk,onenight,start_date,end_date) values(?,?,?,?)',[req.body.user_id,onenight,req.body.start_date,req.body.end_date],function(error, rows){
    if (error){
      console.log("Connection Error3" + error);
      res.sendStatus(500);
      connection.release();
    }
    else {

    }
  });
}

function insertRecommendOnenight(connection,req,res,callback){
  var sdate=new Date(req.body.start_date);                         //클라이언트에서 format을 "2017/1/4" 이런식으로 맞춰서 보내달라고 하기.
  var edate=new Date(req.body.end_date);
  var onenight=edate.getTime()/(1000*60*60*24)-sdate.getTime()/(1000*60*60*24)+1;
  var scheduleArray=req.body.schedule;
  for(var i=0;i<scheduleArray.length;i++){       // recommend_onenight에 insert
    ri=i;
    console.log("aaaaaaaaaaaaaaaaaaaaaaaa "+i);
    connection.query("insert into recommend_onenight(recommend_id_fk,day) select recommend_id,'?' from user,recommend where user_id=? && user_id=user_id_fk",[(i+1),req.body.user_id],function(error, rows){
      if (error){
        console.log("Connection Error2" + error);
        res.sendStatus(500);
        connection.release();
      }
      else {

        //  res.status(200).send({result : true});
      }
    });
  }
}

function insertRecommendOnenightRoute(connection,req,res,callback){
  var schedule=req.body.schedule;
  console.log("user_id: "+req.body.user_id);
  connection.query("select distinct onenight_id from user,recommend,recommend_onenight where user_id=? && user_id=user_id_fk && recommend_id=recommend_id_fk",[req.body.user_id],function(error, rows){
    if (error){
      console.log("Connection Error3" + error);
      res.sendStatus(500);
      connection.release();
    }
    else {
      console.log("schedule"+schedule);
      console.log("schedule.length: "+schedule.length);
      console.log("rows.length: "+rows.length);
      for(var i=0;i<rows.length;i++){
        console.log("rows[i].onenight_id: "+rows[i].onenight_id);
      }
      for(var i=0;i<rows.length;i++){
        //var realnight=rows[i].onenight;
        for(var j=0;j<schedule[i].length;j++){
          // console.log("bbbbbbbbbbbbbbbbbbbbb "+j);
          // console.log(schedule[i][j]);
          // console.log("schedule[i].length , i :"+ schedule[i].length+" , "+i);
          // console.log("rows[j]: "+rows[j].onenight_id);
          // console.log("i :"+i);
          // console.log("rows[i].onenight_id "+rows[i].onenight_id);
          console.log(rows[i].onenight_id);
          connection.query("insert into recommend_onenight_route(onenight_id_fk,sequence,recommend_spot) values(?,?,?)",[rows[i].onenight_id,j,schedule[i][j]],function(error, rows){
            if (error){
              console.log("Connection Error3" + error);
              res.sendStatus(500);
              connection.release();
            }
            else {

            }
          });

        }
      }
    }
  });

  // connection.query("insert into recommend_onenight_route(onenight_id_fk,sequence,recommend_spot) select onenight_id,'?','?' from user,recommend,recommend_onenight where recommend_id=recommend_id_fk && user_id=? && user_id=user_id_fk && day = ?",[j,schedule[i][j],req.body.user_id,(i+1)],function(error, rows){
  //   if (error){
  //     console.log("Connection Error3" + error);
  //     res.sendStatus(500);
  //     connection.release();
  //   }
  //   else {
  //
  //   }
  // });
  res.status(200).send({result:true});
}

function deleteRecommend(connection,req,res,callback){
  console.log("ccccccccccccccccc");
  connection.query("delete from recommend where user_id_fk=?",req.body.user_id,function(error, rows){
    if (error){
      console.log("Connection Error3" + error);
      res.sendStatus(500);
      connection.release();
    }
    else {
      console.log("ddddddddddddddddddddd");
    }
  });
  //res.status(200).send({result:true});

}


module.exports = router;
