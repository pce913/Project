package com.smu.cs.fookey.Network;

import android.app.Application;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

/**
 * Created by Chan on 2017-08-23.
 */

//인터넷 permission 켜야 함.  done
//앱의 시작시에 Manifest에서 ApplicationController부터 시작해야 함.   done
    //Retrofit2 추가해야함.  done
public class ApplicationController extends Application {
    private final String IP="117.16.44.14";
    private final int PORT=2014;
    //Application 인스턴스 선언
    private static ApplicationController instance;
    public static ApplicationController getInstance() {
        return instance;
    }
    public NetworkService getNetworkService() {
        return networkService;
    }
    @Override
    public void onCreate() {
        super.onCreate();
        ApplicationController.instance = this;            //이부분 원래 this
        instance.buildNetworkService(IP, PORT);
        new NetworkApi();     //NetworkApi를 만들어 놓고 계속 사용할 것이다.
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
                        .setDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSS'Z'")
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
