package com.brave.blank.erm.Network;

/**
 * Created by chanung on 2016-08-04.
 */
import android.app.Application;
import android.util.Log;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

/**
 * Created by Sansung on 2016-06-18.
 */
public class ApplicationController extends Application {

    private final String IP="188.166.181.182";
    private final int PORT=9305;

    public static ApplicationController getInstance() {
        Log.d("Service:", "getInstance() 실행됨.");
        return instance;
    }

    public NetworkService getNetworkService() {
        return networkService;
    }

    //Application 인스턴스 선언
    private static ApplicationController instance;

    @Override
    public void onCreate() {
        super.onCreate();
        Log.d("Service:", "ApplicationController onCreate 실행됨");
        ApplicationController.instance = this;            //이부분 원래 this
        instance.buildNetworkService(IP, PORT);

    }

    //네트워크 인터페이스 구현
    private NetworkService networkService;
    private String baseurl;

    //인터페이스 구현 메소드
    public void buildNetworkService(String ip, int port){
        synchronized (ApplicationController.class){
            if(networkService == null){
                baseurl = String.format("http://%s:%d/", ip, port);
                Gson gson = new GsonBuilder()
                        .setDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSS'Z'")                    //질문
                        .create();

                GsonConverterFactory factory = GsonConverterFactory.create(gson);

                //Retrofit 설정
                Retrofit retrofit = new Retrofit.Builder()
                        .baseUrl(baseurl)
                        .addConverterFactory(factory)
                        .build();

                //인터페이스 구현
                networkService = retrofit.create(NetworkService.class);
            }
        }
    }

}