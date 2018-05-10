package com.brave.blank.erm.Network;

import com.brave.blank.erm.Network.Request.ItemId;
import com.brave.blank.erm.Network.Request.Login;
import com.brave.blank.erm.Network.Request.Signup;
import com.brave.blank.erm.Network.Request.SubmitSpeaking;
import com.brave.blank.erm.Network.Request.SubmitWriting;
import com.brave.blank.erm.Network.Response.Homework;
import com.brave.blank.erm.Network.Response.Identify;
import com.brave.blank.erm.Network.Response.Letter;
import com.brave.blank.erm.Network.Response.Result;
import com.brave.blank.erm.Network.Response.SignupResult;
import com.brave.blank.erm.Network.Response.Speaking;
import com.brave.blank.erm.Network.Response.Speakingdetail;
import com.brave.blank.erm.Network.Response.StudyInfo;
import com.brave.blank.erm.Network.Response.Topic;
import com.brave.blank.erm.Network.Response.Writing;
import com.brave.blank.erm.Network.Response.Writingdetail;

import java.util.List;

import retrofit2.Call;
import retrofit2.http.Body;
import retrofit2.http.DELETE;
import retrofit2.http.GET;
import retrofit2.http.Header;
import retrofit2.http.POST;
import retrofit2.http.Path;
import retrofit2.http.Query;

/**
 * Created by chanung on 2016-08-04.
 */
public interface NetworkService {
    @POST("sign/in")                                      //로그인 요청
    Call<Identify> getIdentify(@Body Login login);

    @POST("sign/up")                                   //회원가입
    Call<SignupResult> getSigninResult(@Body Signup signup);

    @GET("sign/duplication")                                //중복체크
    Call<Result> getDuplication(@Query("user") String user);

    @GET("sign/teacherCheck")                          //선생님 id 존재하는지 체크
    Call<Result> getTeacherExist(@Query("teacher") String teacher);

    @GET("study/topics")                                //단어 및 문장들의 주제를 가져온다.
    Call<List<Topic>> getTopic(@Query("type") String type);

    @GET("study/items")                                // 자음, 단어, 문장 등의 정보를 불러온다.
    Call<List<Letter>> getLetter(@Query("type") String type);                //복수개의 정보를 받아야 하므로 리턴타입이 List

//    @GET("user/homeworks")                            //과제 목록을 불러온다.             <--------------수정되었음
//    Call<List<Homework>> getHomework(@Header("token") String token);            //복수개의 정보를 받아야 하므로 리턴타입이 List

    @GET("user/homeworks")                            //과제 목록을 불러온다.             <--------------수정되었음
    Call<List<Homework>> getHomework(@Header("token") String token,@Query("type") int type);            //복수개의 정보를 받아야 하므로 리턴타입이 List

    @GET("user/homework/detail")                                 //받아쓰기 과제 내역을 보여준다.
    Call<List<Writingdetail>> getdetailWriting(@Header("token") String token, @Query("homework_id") int homework_id, @Query("type") boolean type);

    @GET("user/homework/detail")                           // 말해보기 과제 내역을 보여준다.
    Call<List<Speakingdetail>> getdetailSpeaking(@Header("token") String token, @Query("homework_id") int homework_id, @Query("type") boolean type);

    @POST("user/homework/submit")                              //받아쓰기 과제 제출
    Call<Void> submitWriting(@Header("token") String token,@Body SubmitWriting submitWriting);

    @POST("user/homework/submit")                         //말하기 과제 제출
    Call<Void> submitSpeaking(@Header("token") String token,@Body SubmitSpeaking submitSpeaking);

    @GET("user/learned")                 //학습한 것들의 목록을 불러온다.
    Call<List<StudyInfo>> getLearnedInfo(@Header("token") String token);          //복수개의 정보를 받아야 하므로 리턴타입이 List

    @GET("user/saved")                  //저장한 것들의 목록을 불러온다.
    Call<List<StudyInfo>> getSavedInfo(@Header("token") String token);           //복수개의 정보를 받아야 하므로 리턴타입이 List

    @POST("user/learn")                                        //학습내용저장
    Call<Void> saveLearn(@Header("token") String token,@Body ItemId itemId);

    @POST("user/save")                              //저장한 내용 저장
    Call<Void> saveSave(@Header("token") String token,@Body ItemId itemId);
    ////////////////////추가

    @GET("user/homework/submitted")                                           //제출한 받아쓰기과제 목록을 불러온다
    Call<List<Writing>> getWriting(@Header("token") String token, @Query("type") boolean type);

    @GET("user/homework/submitted")                                       //제출한 말하기과제 목록을 불러온다
    Call<List<Speaking>> getSpeaking(@Header("token") String token, @Query("type") boolean type);

    @DELETE("user/learned/{item_id}")                     //학습완료를 '취소'하기
    Call<Void> deleteLearn(@Header("token") String token,@Path("item_id") int item_id);

    @DELETE("user/saved/{item_id}")                     //저장완료를 '취소'하기
    Call<Void> deleteSave(@Header("token") String token,@Path("item_id") int item_id);

//    @GET("study/item/image")                    //이미지 부분 물어볼것 있음.
//    Call<Void> getImage();

}