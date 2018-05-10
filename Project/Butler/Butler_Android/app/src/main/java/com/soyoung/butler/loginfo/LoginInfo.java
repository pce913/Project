package com.soyoung.butler.loginfo;

import android.app.ProgressDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.FacebookSdk;
import com.facebook.GraphRequest;
import com.facebook.GraphResponse;
import com.facebook.appevents.AppEventsLogger;
import com.facebook.login.LoginResult;
import com.facebook.login.widget.LoginButton;
import com.soyoung.butler.R;
import com.soyoung.butler.application.ApplicationController;
import com.soyoung.butler.main.MainActivity;
import com.soyoung.butler.network.NetworkService;
import com.soyoung.butler.person_dataset.PersonInfo;
import com.soyoung.butler.person_dataset.PersonInfoResult;
import com.soyoung.butler.register.SignupActivity;

import org.json.JSONObject;

import java.util.Arrays;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class LoginInfo extends AppCompatActivity {

    private CallbackManager callbackManager;
    Button loginBtn;
    Button joinBtn;
    EditText email;
    EditText password;

    NetworkService service;
    private ProgressDialog mProgressDialog;

    private static String id = "";
    private static String pw = "";
    InputMethodManager imm;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        FacebookSdk.sdkInitialize(getApplicationContext());
        AppEventsLogger.activateApp(this);
        setContentView(R.layout.activity_login_info);

        imm = (InputMethodManager)getSystemService(INPUT_METHOD_SERVICE);
        loginBtn = (Button)findViewById(R.id.loginBtn);
        joinBtn = (Button)findViewById(R.id.joinBtn);
        email = (EditText)findViewById(R.id.email);
        password = (EditText)findViewById(R.id.pwd);

        LoginButton loginButton = (LoginButton) findViewById(R.id.facebook_login_button);
        loginButton.setReadPermissions(Arrays.asList("public_profile", "email"));

        callbackManager = CallbackManager.Factory.create();

        mProgressDialog = new ProgressDialog(LoginInfo.this);
        mProgressDialog.setCancelable(false);
        mProgressDialog.setMessage("등록 중...");
        mProgressDialog.setIndeterminate(true);

        // TODO: 2016. 11. 21. 미리 retrofit를 build 한 것을 가져온다.
        service = ApplicationController.getInstance().getNetworkService();

        loginButton.registerCallback(callbackManager, new FacebookCallback<LoginResult>() {
            @Override
            public void onSuccess(LoginResult loginResult) {
                Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                GraphRequest graphRequest = GraphRequest.newMeRequest(loginResult.getAccessToken(), new GraphRequest.GraphJSONObjectCallback() {
                    @Override
                    public void onCompleted(JSONObject object, GraphResponse response) {
                        Log.v("result", object.toString());
                    }
                });

                Bundle parameters = new Bundle();
                parameters.putString("fields", "id,name,email,gender,birthday");
                graphRequest.setParameters(parameters);
                graphRequest.executeAsync();

                startActivity(intent);
                finish();
            }

            @Override
            public void onCancel() {
            }

            @Override
            public void onError(FacebookException error) {
                Log.e("LoginErr",error.toString());
            }
        });

        loginBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (email.length() == 0) {      //공란일때 토스트 띄우기
                    Toast.makeText(getApplicationContext(), "이메일을 작성해주세요", Toast.LENGTH_SHORT);
                }
                if (password.length() == 0) {
                    Toast.makeText(getApplicationContext(), "비밀번호를 작성해주세요", Toast.LENGTH_SHORT);
                }

                //이제부터 서버랑 통신해서 아이디, 비번 맞는지 확인
                id = email.getText().toString();
                pw = password.getText().toString();

             //   RequestBody email = RequestBody.create(MediaType.parse("multipart/form-data"), id);
               // RequestBody password = RequestBody.create(MediaType.parse("multipart/form-data"), pw);

                //MultipartBody.Part body;
                MainListData mainListData=new MainListData(id,pw);


                Call<MainResult> mainResultCall=service.requestMain(mainListData);
                mainResultCall.enqueue(new Callback<MainResult>() {
                    @Override
                    public void onResponse(Call<MainResult> call, Response<MainResult> response) {
                        if(response.isSuccessful()){
                            MainResult result=response.body();
                            if(result.result){
                                callPersonInfo(result);
                               // Toast.makeText(getApplicationContext(), result.user_id, Toast.LENGTH_SHORT).show();
                                Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                                Toast.makeText(getApplicationContext(), "로그인 성공", Toast.LENGTH_SHORT).show();

                                SharedPreferences setting;             //이메일 로그인.
                                SharedPreferences.Editor editor;
                                setting = getSharedPreferences("setting", MODE_PRIVATE);
                                editor = setting.edit();
                                editor.putString("user_id",result.user_id);
                                editor.commit();

                                mProgressDialog.dismiss();
                                startActivity(intent);
                            }else{
                                Toast.makeText(getApplicationContext(), "로그인 실패", Toast.LENGTH_SHORT).show();
                                mProgressDialog.dismiss();
                            }
                        }
                    }
                    @Override
                    public void onFailure(Call<MainResult> call, Throwable t) {
                        Log.d("result","fail");
                    }
                });

            }
        });

        joinBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), SignupActivity.class); //회원가입페이지로 이동
                startActivity(intent);
                finish();
            }
        });
    }

    public void linearOnClick(View v) {
        imm.hideSoftInputFromWindow(email.getWindowToken(), 0);
        imm.hideSoftInputFromWindow(password.getWindowToken(), 0);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        callbackManager.onActivityResult(requestCode, resultCode, data);
    }

    public void callPersonInfo(MainResult result){
        final String user_id = result.user_id;
        final Call<PersonInfoResult> getPersonInfo = service.getPersonInfoResult(result.user_id);
        getPersonInfo.enqueue(new Callback<PersonInfoResult>() {
            @Override
            public void onResponse(Call<PersonInfoResult> call, Response<PersonInfoResult> response) {
                PersonInfoResult personTemp = response.body();
               try {
                    PersonInfo person =  PersonInfo.getInstance();
                    person.setPersonInfo(personTemp.user_email,personTemp.user_name,personTemp.user_image_url,user_id);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
            @Override
            public void onFailure(Call<PersonInfoResult> call, Throwable t) {

            }
        });
    }

}
