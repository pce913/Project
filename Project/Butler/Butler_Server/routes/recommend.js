function next_permutation(a,n){
  var i=n-1;
  while(i>0 && a[i-1] >= a[i])
    i-=1;

  if(i<=0)
    return false;

  var j=n-1;
  while(a[j]<=a[i-1])
    j-=1;

  //[a[i-1],a[j]]=[a[j],a[i-1]];                 //swap -> [x,y]=[y,x]
  var tmp=a[i-1];
  a[i-1]=a[j];
  a[j]=tmp;
  j=n-1;
  while(i<j){
    //[a[i],a[j]]=[a[j],a[i]];
    tmp=a[i];
    a[i]=a[j];
    a[j]=tmp;
    i+=1;
    j-=1;
  }
  return true;
}


function tsp(a){         // a ->  A지점에서 B지점으로의 weight가 저장되어 있는 2차원 배열.
//  console.log(a);
   var ansRoute=new Array(a.length);      //a.length-1
  var n=a.length;                       //숙소를 포함해서 방문해야하는 장소의 갯수. 받아오는 코드 추가하기.
  var d=[];                     //next_permutation을 적용할 배열 선언
  for(var i=1;i<n;i++){                     //0번을 숙소라고 했을때, 0번을 제외한 나머지 부분에대해 next_permutation 적용.
    d.push(i);
    console.log("d: "+i);
  }
  var ans=2147483647;
  do{
  //  var ok=true;                    //못가는 길은 없다.
    var sum=0;
    for(var i=0;i<n-2;i++){
      sum+=a[d[i]][d[i+1]];
    }
  //  console.log("in tsp 88888888888888");
    sum+=a[0][d[0]] + a[d[n-2]][0];
  //  console.log("in tsp 999999999999999");
    if(ans>sum){                       //마지막에 가는곳은 숙소라고 가정하고 숙소에서 첫번째 장소와 마지막 까지 더해주는 코드 추가한다.
      ans=sum;
      var i=0;
      for(;i<d.length;i++){
        ansRoute[i]=d[i];
      }
    }

  }while(next_permutation(d,d.length));

  //console.log(ans);
  //console.log(ansRoute);
  return ansRoute;
}
//
// var myArray=new Array(4);
// myArray[0]=new Array(4);
// myArray[1]=new Array(4);
// myArray[2]=new Array(4);
// myArray[3]=new Array(4);
// myArray[0][0]=0;
// myArray[0][1]=10;
// myArray[0][2]=15;
// myArray[0][3]=20;
// myArray[1][0]=5;
// myArray[1][1]=0;
// myArray[1][2]=9;
// myArray[1][3]=10;
// myArray[2][0]=6;
// myArray[2][1]=13;
// myArray[2][2]=0;
// myArray[2][3]=12;
// myArray[3][0]=8;
// myArray[3][1]=8;
// myArray[3][2]=9;
// myArray[3][3]=0;
 //var ansRoute=new Array(3);      //숙소를 제외한 방문해야하는 장소의 갯수. 정답이 되는 경로를 받기 위함.  동적으로 생성해줘야 한다.







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


router.get('/:user_id', function(req, res, next) {               // 계산된 추천경로를 보여준다.
  pool.getConnection(function(error, connection){
    if (error){
      console.log("getConnection Error" + error);
      res.sendStatus(500);
    }
    else{
      console.log("111111111111111111");
      var temp_spot_array=[];
      var temp_city_sight_id_array=[];
    //  var temp_city_id_pair_array=new Array();
      connection.query('select spot,city_sight_id from city_sight,select_city_sight,user where user_id=? && user_id=user_id_fk && city_sight_id_fk=city_sight_id && type =1' ,[req.params.user_id],function(error, rows){
        if (error){
          console.log("Connection Error" + error);
          res.sendStatus(500);
          connection.release();
        }
        else {
          //essentials=rows1;
                console.log("22222222222222222");
          temp_spot_array.push("숙소");                       //첫번째 push는 숙소로 한다.
          temp_city_sight_id_array.push(1000);

          for(var i=0;i<rows.length;i++){
            temp_spot_array.push(rows[i].spot);
            temp_city_sight_id_array.push(rows[i].city_sight_id);
          }
          connection.query('select spot,city_sight_id from city_sight,select_city_sight,user where user_id=? && user_id=user_id_fk && city_sight_id_fk=city_sight_id && type =2' ,[req.params.user_id],function(error, rows){           //type=2 인 선택관광지 애들중에서 적당히 몇개를 추려야 한다. ->아직 안함.
            if (error){
              console.log("Connection Error" + error);
              res.sendStatus(500);
              connection.release();
            }
            else {
              //alternatives=rows;
              console.log("33333333333333");
              for(var i=0;i<rows.length;i++){
                  temp_spot_array.push(rows[i].spot);                       //첫번째 push는 숙소로 한다.
                  temp_city_sight_id_array.push(rows[i].city_sight_id);      // 첫번째 push는 id=1000 즉, 숙소로 한다.
              }

              var city_num=temp_city_sight_id_array.length;            //여행지 갯수.
              var city_pair_array=new Array(city_num*(city_num-1)/2);      //  여행지간의 pair의 갯수. 순서없이 2개를 뽑는 조합. (무방향 그래프이기 때문이다)
              for(var i=0;i<city_pair_array.length;i++){                  //각 여행지 간의 pair를 이루는 2차원 배열을 만든다.
                city_pair_array[i]=new Array(2);
              }
              /////////////////////////////////////
              var k=0;
              for(var i=0;i<city_num-1;i++){                      //각 여행지 간의 pair를 이루는 2차원 배열을 만든다.
                for(var j=i+1;j<city_num;j++){
                  city_pair_array[k][0]=temp_city_sight_id_array[i];
                  city_pair_array[k][1]=temp_city_sight_id_array[j];
                  console.log([city_pair_array[k][0],city_pair_array[k][1]]);     //잘나옴.
                  k++;
                }
              }

              //////////////////////////////////////
              var weightArray=new Array(city_num);                        //각 여행지 간의 weight를 담는 2차원 배열을 만든다.
              for(var i=0;i<city_num;i++){
                weightArray[i]=new Array(city_num);
                for(var j=0;j<city_num;j++){
                  weightArray[i][j]=0;
                }
              }

              //////////////////////
              console.log("44444444444444");
              makeWeightArray(connection,temp_spot_array,city_pair_array,weightArray,req,res);                     // 각 여행지 간에 걸리는 시간을 담는 배열을 생성한다.

              //res.status(200).send({result : true});
              connection.release();

            }
          });

        }
      });
    }
  });
});

function makeWeightArray(connection,temp_spot_array,city_pair_array,weightArray,req,res){      // 각 여행지 간의 pair를 이루는 배열을 매개변수로 넘겨줘야 한다.
  var i=0;
  var j=1;
    console.log("5555555555555");
    console.log(city_pair_array.length);
    //  console.log(city_pair_array[0][0]+" "+city_pair_array[0][1]);
    for(var k=0;k<city_pair_array.length;k++){
                                                     //pool.getConnection 해줘야 할 수도 있다.
    connection.query('select duration from lead_time where a_city_sight_id_fk=? && b_city_sight_id_fk=?' ,[city_pair_array[k][0],city_pair_array[k][1]],function(error, rows){             //1. 일단 숙소를 제외한 각각의 여행지들에 대해서 weight를 가져온다.
      if (error){
        console.log("Connection Error" + error);
        res.sendStatus(500);
        connection.release();
      }
      else {
        console.log(rows.length);
            weightArray[i][j]=rows[0].duration;
            weightArray[j][i]=rows[0].duration;
            j++;
            if(j==weightArray[i].length){
                if(i==weightArray[i].length-2){                                                 //이 안에서 tsp 호출.
                  console.log("666666666666");
                  console.log(weightArray);
                  var ansRoute=tsp(weightArray);
                  console.log("7777777777777");
                  showRecommend(connection,temp_spot_array,req,res,ansRoute);
                }

              i++;
              j=i+1;
            }

          //  console.log("weightArray[i].length: "+weightArray[i].length);

      }
    });
  }



}

// 추천경로를 보여줌과 동시에 기존에 선택했던 애들은 전부다 지워지는 코드를 넣어줘야 한다.
function showRecommend(connection,temp_spot_array,req,res,ansRoute){
        // 3일씩 나눠서 담는 코드를 짜준다.
  var one;
  var two;
  var three;
  var rlength=ansRoute.length;           //숙소까지 포함된 길이.
  console.log(rlength);
  if(rlength==0){
  one=[];
  two=[];
  three=[];
  }
  else if(rlength==1){
  one=[];
  two=new Array(1);
  three=[];
  }
  else if(rlength==2){
  one=[];
  two=new Array(1);
  three=new Array(1);
  }
  else if(rlength==3){
  one=new Array(1);
  two=new Array(1);
  three=new Array(1);
  }
  else if(rlength==4){
  one=new Array(1);
  two=new Array(2);
  three=new Array(1);
  }
  else{
                                     // 가운데다가 다 떼려박지 말고 적절하게 분배해서 넣어주자.
  var div=parseInt(rlength/3);
  var firstLength;
  var secondLength;
  var thirdLength;
  if(rlength%3==0){
    firstLength=div-1;
    secondLength=div;
    thirdLength=div;
  }
  else if(rlength%3==1){
    firstLength=div;
    secondLength=div;
    thirdLength=div;
  }
  else{
    firstLength=div;
    secondLength=div+1;
    thirdLength=div;
  }
console.log("div: "+div);
console.log("firstLength: "+firstLength);
console.log("secondLength: "+secondLength);
console.log("thirdLength: "+thirdLength);
  one=new Array(firstLength);                  //합쳐서 rlenth-1개 --> 숙소는 제외시켜서 보여준다.
  two=new Array(secondLength);
  three=new Array(thirdLength);
  }

  //////////////////////////
  var x=0;
  while(x<one.length){
    one[x]=temp_spot_array[ansRoute[x]];
    console.log(one);
    x++;
  }
  var twoi=0;
  while(x<one.length+two.length){
    two[twoi]=temp_spot_array[ansRoute[x]];
  //  console.log(two);
    x++;
    twoi++;
  }
  console.log("cccccccccccccccccccccc");
  var threei=0;
  while(x<one.length+two.length+three.length){
    three[threei]=temp_spot_array[ansRoute[x]];
  //  console.log(three);
    x++;
    threei++;
  }
  console.log([one,two,three]);
res.status(200).send([one,two,three]);
connection.query('delete from select_city_sight where user_id_fk=?',req.params.user_id,function(error, rows){
  if (error){
    console.log("Connection Error" + error);
    res.sendStatus(500);
    connection.release();
  }                              // ArrayList<ArrayList<Landmark>> 형태로 보낸다.
  else {

      //  console.log("weightArray[i].length: "+weightArray[i].length);

  }
});

}





module.exports = router;
