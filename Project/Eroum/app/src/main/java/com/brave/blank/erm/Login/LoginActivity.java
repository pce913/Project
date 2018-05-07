package com.brave.blank.erm.Login;

import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.Toast;

import com.brave.blank.erm.AssembledData;
import com.brave.blank.erm.Network.ApplicationController;
import com.brave.blank.erm.Network.NetworkService;
import com.brave.blank.erm.Network.Request.Login;
import com.brave.blank.erm.Network.Response.Homework;
import com.brave.blank.erm.Network.Response.Identify;
import com.brave.blank.erm.Network.Token;
import com.brave.blank.erm.R;
import com.brave.blank.erm.ToolbarActivity;

import java.util.List;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

/**
 * Created by IT on 2016-07-26.
 */
public class LoginActivity extends AppCompatActivity {
    Button singup;
    Button loginbtn;
    EditText userid, userpasswd;
    private NetworkService networkService;
    List<Homework> wrhomeworks;
    List<Homework> sphomeworks;

    private Boolean buttonclicked = false;
    // 자동 로그인
    CheckBox Auto_Login;
    SharedPreferences setting;
    SharedPreferences.Editor editor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        initNetworkService();

        singup = (Button) findViewById(R.id.singupbtn);
        loginbtn = (Button) findViewById(R.id.loginbtn);
        userid = (EditText) findViewById(R.id.idinput);
        userpasswd = (EditText) findViewById(R.id.passwdinput);
        Auto_Login = (CheckBox) findViewById(R.id.auto_login);
        setting = getSharedPreferences("setting", MODE_PRIVATE);
        editor = setting.edit();

        if (setting.getBoolean("Auto_Login_enabled", false)) {
            userid.setText(setting.getString("ID", ""));
            userpasswd.setText(setting.getString("PW", ""));
            Auto_Login.setChecked(true);

        }
        else if(setting.getBoolean("Auto_Login_enabled", true)){
            networkLogin();
            loginbtn.setEnabled(false);
        }



        singup.setOnClickListener(new View.OnClickListener() {           //회원가입 페이지로 이동
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), JoinActivity.class);
                startActivity(intent);
            }
        });

        if(buttonclicked == false){
            loginbtn.setEnabled(true);
        } else {
            loginbtn.setBackgroundColor(Color.WHITE);
            loginbtn.setTextColor(Color.parseColor("#F48C88"));
        }


        loginbtn.setOnClickListener(new View.OnClickListener() {               //메인페이지로 이동

            @Override
            public void onClick(View v) {
                if (TextUtils.isEmpty(userid.getText().toString()) || TextUtils.isEmpty(userpasswd.getText().toString())) {
                    Toast.makeText(LoginActivity.this, "아이디와 비밀번호를 확인해주세요", Toast.LENGTH_SHORT).show();
                    return;
                }

                loginbtn.setEnabled(false);
                buttonclicked = false;

                networkLogin();

            }
        });

        Auto_Login.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                // TODO Auto-generated method stub

                if (!isChecked) {
                    editor.clear();
                    editor.commit();
                }
            }
        });
    }

    private void setAutoLogin(){
        String ID = userid.getText().toString();
        String PW = userpasswd.getText().toString();

        editor.putString("ID", ID);
        editor.putString("PW", PW);
        editor.putBoolean("Auto_Login_enabled", true);
        editor.commit();
    }


    private void initNetworkService() {
        // TODO: 13. ApplicationController 객체를 이용하여 NetworkService 가져오기
        networkService = ApplicationController.getInstance().getNetworkService();
    }

    private void networkLogin(){
        Login login = new Login();
        login.setUser(userid.getText().toString());
        login.setPassword(userpasswd.getText().toString());

        Call<Identify> addUser = networkService.getIdentify(login);
        Log.d("MyTag", "요청이가나? ");
        addUser.enqueue(new Callback<Identify>() {
            @Override
            public void onResponse(Call<Identify> call, Response<Identify> response) {
                int statusCode = response.code();
                Log.d("MyTag", "요청이오나? " + statusCode);
                if (response.isSuccessful()) {
                    Identify identify = response.body();

                    if (identify.isResult() == true) {
//                        Log.d("identifyname", identify.getName());             //name이 안넘어오고 있음.
                        Token.setToken(identify.getToken());

                        AssembledData.setIdentifies(identify);
                        networkHomeworkWriting();
                        if(Auto_Login.isChecked()==true){
                            setAutoLogin();
                        }

                    } else {
                        Toast.makeText(LoginActivity.this, "아이디와 비밀번호를 확인해주세요", Toast.LENGTH_SHORT).show();
                        buttonclicked = false;
                        loginbtn.setEnabled(true);
                    }
                } else {
                    Log.d("MyTag", "응답코드 : " + statusCode);
                    buttonclicked = false;
                    loginbtn.setEnabled(true);
                }
            }

            @Override
            public void onFailure(Call<Identify> call, Throwable t) {
                Log.d("MyTag", "에러내용 : " + t.getMessage());
                buttonclicked = false;
                loginbtn.setEnabled(true);
            }
        });
    }

    public void networkHomeworkWriting() {                 //과제 목록 불러오기
        Call<List<Homework>> homeworkWritingCall = networkService.getHomework(Token.getToken(),1);
        Log.d("MyTag", "writing call 여기로 들어오니? "); //받아쓰기 과제 목록 불러오기
        homeworkWritingCall.enqueue(new Callback<List<Homework>>() {
            @Override
            public void onResponse(Call<List<Homework>> call, Response<List<Homework>> response) {
                int statusCode = response.code();
                Log.d("MyTag", "여기로 들어오니? " + statusCode);
                if (response.isSuccessful()) {
                    wrhomeworks = response.body();
                    AssembledData.setHomeworks(wrhomeworks);

                    networkHomeworkSpeaking();
                    Log.d("MyTag", "speaking요청을하나? " + statusCode);
                } else {
                    Log.d("MyTag", "homework가가가가가가가가응답코드 : " + statusCode);
                }
            }
            @Override
            public void onFailure(Call<List<Homework>> call, Throwable t) {
                Log.d("MyTag", "에러내용 : " + t.getMessage());
            }
        });
    }

    private  void networkHomeworkSpeaking(){
        Call<List<Homework>> homeworkSpeakingCall = networkService.getHomework(Token.getToken(),0);            //말하기 과제 목록 불러오기
        homeworkSpeakingCall.enqueue(new Callback<List<Homework>>() {
            @Override
            public void onResponse(Call<List<Homework>> call, Response<List<Homework>> response) {
                int statusCode = response.code();
                if (response.isSuccessful()) {
                    sphomeworks = response.body();
                    AssembledData.setHomeworks(sphomeworks);
                    Intent intent = new Intent(getApplicationContext(), ToolbarActivity.class);
                    intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);               //모든 activity 스택을 지우는 플래그

                    startActivity(intent);
                    loginbtn.setEnabled(true);
                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
                } else {
//                    Log.d("MyTag", "homework가가가가가가가가응답코드 : " + statusCode);
                }
            }
            @Override
            public void onFailure(Call<List<Homework>> call, Throwable t) {
                Log.d("MyTag", "에러내용 : " + t.getMessage());
            }
        });
    }



}