package com.soyoung.butler.loginfo;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;

import com.soyoung.butler.R;
import com.soyoung.butler.application.ApplicationController;
import com.soyoung.butler.main.MainActivity;
import com.soyoung.butler.network.NetworkService;
import com.soyoung.butler.person_dataset.PersonInfo;
import com.soyoung.butler.person_dataset.PersonInfoResult;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class SplashActivity extends AppCompatActivity {
    NetworkService service;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_splash);
        service = ApplicationController.getInstance().getNetworkService();
        Handler hd = new Handler();
        hd.postDelayed(new Runnable() {
            @Override
            public void run() {
                SharedPreferences setting;             //이메일 로그인.
                SharedPreferences.Editor editor;
                setting = getSharedPreferences("setting", MODE_PRIVATE);
                String user_id=setting.getString("user_id","null");
                if(user_id!="null"){
                    callPersonInfo(user_id);     // PersonInfo 갱신.
                    Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                    startActivity(intent);
                    finish();
                }
                else{
                    Intent intent = new Intent(getApplicationContext(), LoginInfo.class);
                    startActivity(intent);
                    finish();
                }

                editor = setting.edit();
                editor.commit();
            }
        }, 2000);
    }
    public void callPersonInfo(String user_id1){
        final String user_id = user_id1;
        service = ApplicationController.getInstance().getNetworkService();
        final Call<PersonInfoResult> getPersonInfo = service.getPersonInfoResult(user_id);
        getPersonInfo.enqueue(new Callback<PersonInfoResult>() {
            @Override
            public void onResponse(Call<PersonInfoResult> call, Response<PersonInfoResult> response) {
                PersonInfoResult personTemp = response.body();
                try {
                    PersonInfo person = PersonInfo.getInstance();
                    person.setPersonInfo(personTemp.user_email, personTemp.user_name, personTemp.user_image_url, user_id);      //  로그인 Singleton 갱신
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
