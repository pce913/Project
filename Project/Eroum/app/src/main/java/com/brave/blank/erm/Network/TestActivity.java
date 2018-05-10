//package com.brave.blank.erm.Network;
//
//import android.os.Bundle;
//import android.support.v7.app.AppCompatActivity;
//import android.util.Log;
//import android.widget.Toast;
//
//import com.brave.blank.erm.Network.Request.ItemId;
//import com.brave.blank.erm.Network.Request.Login;
//import com.brave.blank.erm.Network.Request.Signup;
//import com.brave.blank.erm.Network.Request.SubmitSpeaking;
//import com.brave.blank.erm.Network.Request.SubmitWriting;
//import com.brave.blank.erm.Network.Response.Homework;
//import com.brave.blank.erm.Network.Response.Identify;
//import com.brave.blank.erm.Network.Response.Letter;
//import com.brave.blank.erm.Network.Response.Result;
//import com.brave.blank.erm.Network.Response.SignupResult;
//import com.brave.blank.erm.Network.Response.Speaking;
//import com.brave.blank.erm.Network.Response.StudyInfo;
//import com.brave.blank.erm.Network.Response.Topic;
//import com.brave.blank.erm.Network.Response.Writing;
//import com.brave.blank.erm.R;
//
//import java.util.List;
//
//import retrofit2.Call;
//import retrofit2.Callback;
//import retrofit2.Response;
//
///**
// * Created by chanung on 2016-08-09.
// */
//public class TestActivity extends AppCompatActivity {
//    private NetworkService networkService;
//    private void initNetworkService(){
//        // TODO: 13. ApplicationController 객체를 이용하여 NetworkService 가져오기
//        networkService = ApplicationController.getInstance().getNetworkService();
//    }
//
//    @Override
//    protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_join);
//
//        initNetworkService();
//    }
//    public void testLogin(){                        //로그인 테스트
//        Login login=new Login();
//        login.setUser("tester1");
//        login.setPassword("123123");
//        Call<Identify> identifyCall=networkService.getIdentify(login);
//        identifyCall.enqueue(new Callback<Identify>() {
//            @Override
//            public void onResponse(Call<Identify> call, Response<Identify> response) {
//                int statusCode = response.code();
//                if (response.isSuccessful()) {
//                    Identify identify = response.body();
//                    Token.setToken(identify.getToken());
//                    Log.d("MyTag", "성공! 응답코드 : : " + statusCode);
//                    //Log.d("token",identify.getToken());
//                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
//                } else {
//
//                    Log.d("MyTag", "응답코드 : " + statusCode);
//                }
//            }
//
//            @Override
//            public void onFailure(Call<Identify> call, Throwable t) {
//                Log.d("MyTag", "에러내용 : " + t.getMessage());
//            }
//        });
//    }
//
//    public void testSingup(){                         //회원가입 테스트
//        Signup signup=new Signup();
//        signup.setUser("iamthebest2");
//        signup.setPassword("123");
//        signup.setName("박찬웅2");
//        signup.setSchool(1);
//        signup.setGrade(3);
//        signup.setClass_num(5);
//        signup.setTeacher("tester1");
//        Call<SignupResult> signupResultCall=networkService.getSigninResult(signup);
//        signupResultCall.enqueue(new Callback<SignupResult>() {
//            @Override
//            public void onResponse(Call<SignupResult> call, Response<SignupResult> response) {
//                int statusCode = response.code();
//                if(response.isSuccessful()){
//                    SignupResult signupResult=response.body();
//                    Log.d("MyTag", "성공! 응답코드 : : " + statusCode);
//                }
//                else{
//
//                    Log.d("MyTag", "응답코드 : " + statusCode);
//                }
//            }
//
//            @Override
//            public void onFailure(Call<SignupResult> call, Throwable t) {
//                Toast.makeText(getApplicationContext(), "Failed to load", Toast.LENGTH_LONG).show();
//                Log.i("MyTag", "에러내용 : " + t.getMessage());
//                //finish();
//            }
//        });
//    }
//
//    public void testDuplication(){                         //아이디 중복확인 테스트
//        Call<Result> booleanCall=networkService.getDuplication("iamthebest");
//        booleanCall.enqueue(new Callback<Result>() {
//            @Override
//            public void onResponse(Call<Result> call, Response<Result> response) {
//                int statusCode = response.code();
//                if (response.isSuccessful()) {
//                    Result result=response.body();
//                    Log.d("MyTag", "성공! 응답코드 : : " + statusCode);
//
//                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
//                } else {
//
//                    Log.d("MyTag", "응답코드 : " + statusCode);
//                }
//            }
//
//            @Override
//            public void onFailure(Call<Result> call, Throwable t) {
//                Log.d("MyTag", "에러내용 : " + t.getMessage());
//            }
//        });
//    }
//
//    public void testTeacherExist(){              //선생님 존재유무 테스트
//        Call<Result> booleanCall=networkService.getTeacherExist("tester1");
//        booleanCall.enqueue(new Callback<Result>() {
//            @Override
//            public void onResponse(Call<Result> call, Response<Result> response) {
//                int statusCode = response.code();
//                if (response.isSuccessful()) {
//                    Result result=response.body();
//                    Log.d("MyTag", "성공! 응답코드 : : " + statusCode);
//
//                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
//                } else {
//
//                    Log.d("MyTag", "응답코드 : " + statusCode);
//                }
//            }
//
//            @Override
//            public void onFailure(Call<Result> call, Throwable t) {
//                Log.d("MyTag", "에러내용 : " + t.getMessage());
//            }
//        });
//    }
//
//    public void testTopic(){
//        Call<List<Topic>> topicCall=networkService.getTopic();
//        topicCall.enqueue(new Callback<List<Topic>>() {
//            @Override
//            public void onResponse(Call<List<Topic>> call, Response<List<Topic>> response) {
//                int statusCode = response.code();
//                if(response.isSuccessful()){
//                    Log.d("MyTag", "성공! Topic 응답코드  : "+ statusCode );
//
//                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
//                }
//                else{
//
//                    Log.d("MyTag", "Topic 응답코드 : " + statusCode);
//                }
//            }
//
//            @Override
//            public void onFailure(Call<List<Topic>> call, Throwable t) {
//                Log.d("MyTag","Topic 에러내용 : " + t.getMessage());
//            }
//        });
//    }
//
//    public void testLetter(){             //글자 정보 받아오기 테스트
//
//        Call<List<Letter>> letterCall=networkService.getLetter("1");
//        letterCall.enqueue(new Callback<List<Letter>>() {
//            @Override
//            public void onResponse(Call<List<Letter>> call, Response<List<Letter>> response) {
//                int statusCode = response.code();
//                if(response.isSuccessful()){
//                    List<Letter> letters=response.body();
//                    Log.d("MyTag", "성공! 응답코드 : : "+ statusCode );
//
//                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
//                }
//                else{
//
//                    Log.d("MyTag", "응답코드 : " + statusCode);
//                }
//            }
//
//            @Override
//            public void onFailure(Call<List<Letter>> call, Throwable t) {
//                Log.d("MyTag","에러내용 : " + t.getMessage());
//            }
//        });
//    }
//
//    public void testHomework(){                      //숙제 정보 받아오기 테스트
//        Call<List<Homework>> homeworkCall=networkService.getHomework(Token.getToken());
//        homeworkCall.enqueue(new Callback<List<Homework>>() {
//            @Override
//            public void onResponse(Call<List<Homework>> call, Response<List<Homework>> response) {
//                int statusCode = response.code();
//                if (response.isSuccessful()) {
//                    List<Homework> homeworks = response.body();
//                    Log.d("MyTag", "성공! 응답코드 : : " + statusCode);
//
//                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
//                } else {
//
//                    Log.d("MyTag", "응답코드 : " + statusCode);
//                }
//            }
//
//            @Override
//            public void onFailure(Call<List<Homework>> call, Throwable t) {
//                Log.d("MyTag", "에러내용 : " + t.getMessage());
//            }
//        });
//    }
//
//    public void testLearnedInfo(){                   //학습한내용 가져오기 테스트
//        Call<List<StudyInfo>> studyInfoCall=networkService.getLearnedInfo(Token.getToken());
//        studyInfoCall.enqueue(new Callback<List<StudyInfo>>() {
//            @Override
//            public void onResponse(Call<List<StudyInfo>> call, Response<List<StudyInfo>> response) {
//                int statusCode = response.code();
//                if(response.isSuccessful()){
//                    List<StudyInfo> studyInfos=response.body();
//                    Log.d("MyTag", "성공! 응답코드 : : "+ statusCode );
//
//                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
//                }
//                else{
//
//                    Log.d("MyTag", "응답코드 : " + statusCode);
//                }
//            }
//
//            @Override
//            public void onFailure(Call<List<StudyInfo>> call, Throwable t) {
//                Log.d("MyTag","에러내용 : " + t.getMessage());
//            }
//        });
//    }
//
//    public void testSavedInfo(){                          //저장한 내용 불러오기 테스트
//        Call<List<StudyInfo>> studyInfoCall=networkService.getSavedInfo(Token.getToken());
//        studyInfoCall.enqueue(new Callback<List<StudyInfo>>() {
//            @Override
//            public void onResponse(Call<List<StudyInfo>> call, Response<List<StudyInfo>> response) {
//                int statusCode = response.code();
//                if(response.isSuccessful()){
//                    List<StudyInfo> studyInfos=response.body();
//                    Log.d("MyTag", "성공! 응답코드 : : "+ statusCode );
//
//                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
//                }
//                else{
//
//                    Log.d("MyTag", "응답코드 : " + statusCode);
//                }
//            }
//
//            @Override
//            public void onFailure(Call<List<StudyInfo>> call, Throwable t) {
//                Log.d("MyTag", "에러내용 : " + t.getMessage());
//            }
//        });
//    }
//    public void testWriting(){
//        Call<List<Writing>> writingCall=networkService.getWriting(Token.getToken(), 7, false);   //4, true     //받아쓰기 true  , 말해보기 false 라고 알려줬지만 그 반대로 해야함.
//        writingCall.enqueue(new Callback<List<Writing>>() {
//            @Override
//            public void onResponse(Call<List<Writing>> call, Response<List<Writing>> response) {
//                int statusCode = response.code();
//                if(response.isSuccessful()){
//                    Log.d("MyTag", "성공! Writing 응답코드 : : "+ statusCode );
//                    List<Writing> writings=response.body();
//                    Log.d("MyTag", "" + writings.get(0).getAnswer());
//                    for(int i=0;i<writings.size();i++){
//                        Log.d("MyTag", ""+writings.get(i).getEnd_date());
//                    }
//                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
//                }
//                else{
//
//                    Log.d("MyTag", "응답코드 : " + statusCode);
//                }
//            }
//
//            @Override
//            public void onFailure(Call<List<Writing>> call, Throwable t) {
//                Log.d("MyTag","Writing 에러내용 : " + t.getMessage());
//            }
//        });
//    }
//
//    public void testSpeaking(){
//        Call<List<Speaking>> speakingCall=networkService.getSpeaking(Token.getToken(), 4, true);               //7 false
//        speakingCall.enqueue(new Callback<List<Speaking>>() {
//            @Override
//            public void onResponse(Call<List<Speaking>> call, Response<List<Speaking>> response) {
//                int statusCode = response.code();
//                if(response.isSuccessful()){
//                    List<Speaking> speakings=response.body();
//                    //  for(int i=0;i<speakings.size();i++)
//                    Log.d("MyTag",""+speakings.size());
//                    Log.d("MyTag", "성공! Speaking 응답코드 : : "+ statusCode );
//
//                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
//                }
//                else{
//
//                    Log.d("MyTag", "응답코드 : " + statusCode);
//                }
//            }
//
//            @Override
//            public void onFailure(Call<List<Speaking>> call, Throwable t) {
//                Log.d("MyTag","에러내용 : " + t.getMessage());
//            }
//        });
//    }
//
//    public void testSubmitSpeaking(){
//        SubmitSpeaking submitSpeaking=new SubmitSpeaking();                 //type true SubmitWriting , false SubmitSpeaking 이렇게 알려줬지만 그 반대로 해야함.
//        submitSpeaking.setType(true);                                            //이게 동작을 안하고 있음.
//        submitSpeaking.setHomework_id(2);
//        submitSpeaking.setSuccess_count(10);
//        submitSpeaking.setChallenge_count(50);
//        Call<Void> voidCall=networkService.submitSpeaking(Token.getToken(), submitSpeaking);
//        voidCall.enqueue(new Callback<Void>() {
//            @Override
//            public void onResponse(Call<Void> call, Response<Void> response) {
//                int statusCode = response.code();
//                if(response.isSuccessful()){
//                    Log.d("MyTag", "성공! 응답코드 : : "+ statusCode );
//
//                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
//                }
//                else{
//
//                    Log.d("MyTag", "응답코드 : " + statusCode);
//                }
//            }
//
//            @Override
//            public void onFailure(Call<Void> call, Throwable t) {
//                Log.d("MyTag","에러내용 : " + t.getMessage());
//            }
//        });
//    }
//
//    public void testSubmitWriting(){
//        SubmitWriting submitWriting=new SubmitWriting();
//        submitWriting.setType(false);
//        submitWriting.setHomework_id(6);
//        submitWriting.setRate(10);
//        submitWriting.setPlay_count(30);
//        submitWriting.setAnswer("박찬웅의 정답");
//        Call<Void> voidCall=networkService.submitWriting(Token.getToken(), submitWriting);
//        voidCall.enqueue(new Callback<Void>() {
//            @Override
//            public void onResponse(Call<Void> call, Response<Void> response) {
//                int statusCode = response.code();
//                if(response.isSuccessful()){
//                    Log.d("MyTag", "성공! 응답코드 : : "+ statusCode );
//
//                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
//                }
//                else{
//
//                    Log.d("MyTag", "응답코드 : " + statusCode);
//                }
//            }
//
//            @Override
//            public void onFailure(Call<Void> call, Throwable t) {
//                Log.d("MyTag","에러내용 : " + t.getMessage());
//            }
//        });
//    }
//
//    public void testSaveLearn(){
//        ItemId itemId=new ItemId();
//        itemId.setItem_id(7);
//        Call<Void> voidCall=networkService.saveLearn(Token.getToken(), itemId);
//        voidCall.enqueue(new Callback<Void>() {
//            @Override
//            public void onResponse(Call<Void> call, Response<Void> response) {
//                int statusCode = response.code();
//                if(response.isSuccessful()){
//                    Log.d("MyTag", "성공! 응답코드 : : "+ statusCode );
//
//                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
//                }
//                else{
//
//                    Log.d("MyTag", "응답코드 : " + statusCode);
//                }
//            }
//
//            @Override
//            public void onFailure(Call<Void> call, Throwable t) {
//                Log.d("MyTag","에러내용 : " + t.getMessage());
//            }
//        });
//    }
//
//    public void testSaveSave(){
//        ItemId itemId=new ItemId();
//        itemId.setItem_id(8);
//        Call<Void> voidCall=networkService.saveSave(Token.getToken(), itemId);
//        voidCall.enqueue(new Callback<Void>() {
//            @Override
//            public void onResponse(Call<Void> call, Response<Void> response) {
//                int statusCode = response.code();
//                if(response.isSuccessful()){
//                    Log.d("MyTag", "성공! 응답코드 : : "+ statusCode );
//
//                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
//                }
//                else{
//
//                    Log.d("MyTag", "응답코드 : " + statusCode);
//                }
//            }
//
//            @Override
//            public void onFailure(Call<Void> call, Throwable t) {
//                Log.d("MyTag","에러내용 : " + t.getMessage());
//            }
//        });
//    }
//}
