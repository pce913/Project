var express = require('express');
var mysql = require('mysql');
var aws = require('aws-sdk');
var db_config = require('../config/db_config.json');
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


router.get('/:what_city', function(req, res, next) {               // 메인페이지 what_city에 따라서 뉴욕또는 LA 추천정보 보내기.
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{
      connection.query('select city_image_url,city from city_info_image,city_info where city_info_id=? && city_info_id=city_info_image.city_info_id_fk ',req.params.what_city,
        function(error, rows){
        if (error){
          console.log("Connection Error" + error);
          res.sendStatus(500);
          connection.release();
        }
        else {
          var array=[];
          //var onenightArray=["3","5","6","7","8","3"];
            var onenightArray=[3,5,6,7,8,3];
          for(var i=0;i<rows.length;i++){
            array.push({
              city_image_url:rows[i].city_image_url,
              city:rows[i].city,
              onenight:onenightArray[i]
            });
          }

          res.status(200).send(array);

          connection.release();
        }
      });

    }
  });
});




router.post('/send_essentials', function(req, res, next) {               // 필수 여행지 받기.
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{
      var essentials_id=req.body.essentials_city_sight_id;
      var elength=essentials_id.length;
      var ok=true;

      connection.query('delete from select_city_sight where user_id_fk=?',[req.body.user_id],                  //뒤로가기 버튼 눌러서 선택한 것을 새로 고칠때를 대비함.
        function(error, rows){
        if (error){
          console.log("Connection Error" + error);
          res.sendStatus(500);
        }
        else {
          for(var i=0;i<elength;i++){
            connection.query("insert into select_city_sight(user_id_fk,city_sight_id_fk,type) values(?,?,?)",[req.body.user_id,essentials_id[i],1],
              function(error, rows){
              if (error){
                ok=false;
              }
            });
          }
          if(!ok){
            console.log("Connection Error" + error);
            res.sendStatus(500);
          }
          else{                                     //사용자가 선택한 필수 여행지에 대한 표식을 완료했다면.
              res.status(200).send({result : true});
          }
          connection.release();
        }
      });

    }
  });
});

router.post('/send_alternatives', function(req, res, next) {               // 선택 여행지 받기.
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{
      var alternatives_id=req.body.alternatives_city_sight_id;
      var alength=alternatives_id.length;
      var ok=true;
      console.log(req.body.user_id);
      console.log(req.body.alternatives_city_sight_id);
      connection.query('delete from select_city_sight where user_id_fk=? && type=2',[req.body.user_id],                   //뒤로가기 버튼 눌러서 선택한 것을 새로 고칠때를 대비함.
        function(error, rows){
        if (error){
          console.log("Connection Error" + error);
          res.sendStatus(500);
        }
        else {
          for(var i=0;i<alength;i++){
            connection.query("insert into select_city_sight(user_id_fk,city_sight_id_fk,type) values(?,?,?)",[req.body.user_id,alternatives_id[i],2],
              function(error, rows){
              if (error){
                ok=false;
              }
            });
          }
          if(!ok){
            console.log("Connection Error" + error);
            res.sendStatus(500);
          }
          else{                                     //사용자가 선택한 필수 여행지에 대한 표식을 완료했다면.
              res.status(200).send({result : true});
          }
          connection.release();
        }
      });


    }
  });
});


// router.post('/init_type', function(req, res, next) {               // 필수 선택 관광지를 선택한 것을 초기화 시킨다.
//   pool.getConnection(function(error, connection){
//     if (error){
//       console.log("getConnection Error" + error);
//       res.sendStatus(500);
//     }
//     else{
//       connection.query('update city_sight set type=3',
//         function(error, rows){
//         if (error){
//           console.log("Connection Error" + error);
//           res.sendStatus(500);
//           connection.release();
//         }
//         else {
//           res.status(200).send({result:true});
//           connection.release();
//         }
//       });
//     }
//   });
// });
//


router.post('/search', function(req, res, next) {               //랜드마크 보여주기.
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{
      var keyword='%'+req.body.keyword+'%';
      var keyword2=keyword.toLowerCase();

      if(req.body.selecting_type==1){              //필수선택 여행지 일때
        var query3="select distinct info_sight_theme.city_info_id_fk,info_sight_theme.city_sight_id_fk,spot,city_sight_id,sight_image_url,sentence from city_info,info_sight_theme,city_sight,city_sight_image where city_info_id_fk=city_info_id &&city_sight_image.city_sight_id_fk=city_sight_id&&info_sight_theme.city_sight_id_fk=city_sight_id && represent=1 && (city like ? || city_eng like ?) && sub_city=0";

        if(req.body.theme=='전체'){                //테마를 정하지 않고 검색할때

          connection.query(query3,[keyword, keyword2],
            function(error, rows){
            if (error){
              console.log("Connection Error" + error);
              res.sendStatus(500);
              connection.release();
            }
            else {
              //rows=[{},{},{},{}];    spot,city_sight_id,sight_image_url,sentence
            var arr=[];
            for(var i=0;i<rows.length;i++){
              arr.push({spot:rows[i].spot,
                        city_sight_id:rows[i].city_sight_id,
                        sight_image_url:rows[i].sight_image_url,
                        sentence:rows[i].sentence
                      });
            }

              res.status(200).send(arr);
              connection.release();
            }
          });
        }
      else{                  //테마 정해서 검색할때
        connection.query(query3+"&& theme=?",[keyword,keyword2,req.body.theme],
          function(error, rows){
          if (error){
            console.log("Connection Error" + error);
            res.sendStatus(500);
            connection.release();
          }
          else {
          var arr=[];
          for(var i=0;i<rows.length;i++){
            arr.push({spot:rows[i].spot,
                      city_sight_id:rows[i].city_sight_id,
                      sight_image_url:rows[i].sight_image_url,
                      sentence:rows[i].sentence
                    });
          }

            res.status(200).send(arr);
            connection.release();
          }
        });
        }

      }

      else if (req.body.selecting_type==2){                //선택 여행지 일때
        var query2="select distinct info_sight_theme.city_info_id_fk,info_sight_theme.city_sight_id_fk,spot,city_sight_id,sight_image_url,sentence from city_info,info_sight_theme,city_sight,city_sight_image where city_info_id_fk=city_info_id && info_sight_theme.city_sight_id_fk=city_sight_id  && (city like ? || city_eng like ?)  && city_sight_id not in (select select_city_sight.city_sight_id_fk from user,select_city_sight where user_id=? && user_id=user_id_fk && type=1) && city_sight_image.city_sight_id_fk=city_sight_id && represent=1 && city_sight.sub_city=0";
        if(req.body.theme=='전체'){                //테마를 정하지 않고 검색할때
          connection.query(query2,[keyword,keyword2,req.body.user_id],
            function(error, rows){
            if (error){
              console.log("Connection Error" + error);
              res.sendStatus(500);
              connection.release();
            }
            else {
              var arr=[];
              for(var i=0;i<rows.length;i++){
                arr.push({spot:rows[i].spot,
                          city_sight_id:rows[i].city_sight_id,
                          sight_image_url:rows[i].sight_image_url,
                          sentence:rows[i].sentence
                        });
              }

                res.status(200).send(arr);
              connection.release();
            }
          });
        }
      else{                  //테마 정해서 검색할때
        connection.query(query2+'&& theme=?',[keyword,keyword2,req.body.user_id,req.body.theme],
          function(error, rows){
          if (error){
            console.log("Connection Error" + error);
            res.sendStatus(500);
            connection.release();
          }
          else {
            var arr=[];
            for(var i=0;i<rows.length;i++){
              arr.push({spot:rows[i].spot,
                        city_sight_id:rows[i].city_sight_id,
                        sight_image_url:rows[i].sight_image_url,
                        sentence:rows[i].sentence
                      });
            }
            res.status(200).send(arr);
            connection.release();
          }
        });
        }

      }

    }
  });
});




router.post('/show_selected_spot', function(req, res, next) {      //선택된 필수&선택여행지 목록을 출력한다.
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{
     var essentialsArray=[];
     var alternativesArray=[];
     var ok=true;
     console.log(req.body.user_id);
      connection.query('select city_sight_id,spot from city_sight,select_city_sight where type=1 && user_id_fk=? && city_sight_id=city_sight_id_fk',[req.body.user_id],
        function(error, rows){
        if (error){
          console.log("Connection Error" + error);
          res.sendStatus(500);
          ok=false;
        }
        else {
          //essentialsArray=rows;
          for(var i=0;i<rows.length;i++){
            essentialsArray.push({city_sight_id:rows[i].city_sight_id,
                                    spot:rows[i].spot});
          }
          //console.log(essentialsArray);
                                                                              // 동기화를 위해서 query를 처리 후 그다음에 또 다른 query를 처리한다.
          connection.query('select city_sight_id,spot from city_sight,select_city_sight where type=2 && user_id_fk=? && city_sight_id=city_sight_id_fk',[req.body.user_id],
            function(error, rows){
            if (error){
              console.log("Connection Error" + error);
              res.sendStatus(500);
              ok=false;

            }
            else {
            //  alternativesArray=rows;
            for(var i=0;i<rows.length;i++){
              alternativesArray.push({city_sight_id:rows[i].city_sight_id,
                                      spot:rows[i].spot});

            }
                console.log(alternativesArray);
                if(!ok){
                  console.log("Connection Error" + error);
                  res.sendStatus(500);
                  connection.release();
                }
                else{                                     //사용자가 선택한 필수 여행지에 대한 표식을 완료했다면.
                // console.log({essentials:essentialsArray,
                //                       alternatives:alternativesArray});
                    res.status(200).send({essentials:essentialsArray,
                                          alternatives:alternativesArray});
                    connection.release();
                }
            }
          });

        }
      });

   }
  });
});

router.post('/sub_spot', function(req, res, next) {               // 여행일정 추천페이지에서 추가로 보여지는 여행지 정보 클라이언트에 전송하기.
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{
      connection.query('select spot,sight_image_url from city_sight,city_sight_image,info_sight_theme,city_info where sub_city=1 && city_sight_id=city_sight_image.city_sight_id_fk && info_sight_theme.city_sight_id_fk=city_sight_id && city_info_id=city_info_id_fk && city=?',[req.body.city] ,function(error, rows){
        if (error){
          console.log("Connection Error" + error);
          res.sendStatus(500);
          connection.release();
        }
        else {
          res.status(200).send(rows);
          connection.release();
        }
      });
    }
  });
});


// router.post('/send_final_spot', function(req, res, next) {               // 최종 선택된 여행지들을 보낸다.
//   pool.getConnection(function(error, connection){
//     if (error){
//       console.log("getConnection Error" + error);
//       res.sendStatus(500);
//     }
//     else{
//
//       connection.query('update city_sight set type=3',              // 최종 선택된 여행지를 보내는것은 결국 앞에서 무엇을 선택했는지가 의미가 없어지므로 일단 type=3으로 다 초기화 시킨다.
//         function(error, rows){
//         if (error){
//           console.log("Connection Error" + error);
//           res.sendStatus(500);
//         }
//         else {
//           var essentials_id=req.body.essentials_city_sight_id;
//           var alternatives_id=req.body.alternatives_city_sight_id;
//           var ok=true;
//           var isEndEssentials=false;
//           var isEndAlternatives=false;
//           var elength=essentials_id.length;
//           var alength=alternatives_id.length;
//         //  console.log("elength-1: "+(elength-1));
//           var i=0;
//           for(i=0;i<elength;i++){
//             //  console.log("i1: "+i);
//             console.log("essentials_id: "+essentials_id[i]);
//             connection.query("update city_sight set type=1 where city_sight_id = ?",[essentials_id[i]],
//               function(error, rows){
//               if (error){
//                 ok=false;
//               }
//             });
//           }
//           if(i==elength)
//             isEndEssentials=true;
//
//           var j=0;
//           for(j=0;j<alength;j++){
//             console.log("alternatives_id: "+alternatives_id[i]);
//             connection.query("update city_sight set type=2 where city_sight_id = ?",[alternatives_id[i]],
//               function(error, rows){
//               if (error){
//                 ok=false;
//               }
//             });
//           }
//           if(j==alength)
//             isEndAlternatives=true;
//
//           while(true){
//             if(isEndEssentials && isEndAlternatives){           // 두개의 반복문이 끝났을때 result:true를 보내라.
//               if(!ok){
//                 console.log("Connection Error" + error);
//                 res.sendStatus(500);
//               }
//               else{
//                   res.status(200).send({result : true});
//               }
//               connection.release();
//             }
//           }
//
//         }
//       });
//
//     }
//   });
// });




module.exports = router;
