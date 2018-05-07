package com.smu.cs.fookey.Network;

import okhttp3.MultipartBody;
import okhttp3.RequestBody;
import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.Multipart;
import retrofit2.http.POST;
import retrofit2.http.Part;
import retrofit2.http.Path;
import retrofit2.http.Query;

/**
 * Created by Chan on 2017-08-23.
 */
public interface NetworkService {
    @GET("/get_token")
    Call<Token> getToken();

    @Multipart
    @POST("/img_upload")     //request: 이미지 전송, response: 메인카테고리 목록들을 보여줌.
    Call<Category> sendImage(@Part("token") RequestBody token,
                             @Part MultipartBody.Part file);

    @GET("/select_main/{category}")
    Call<Category> sendMainAnswer(@Path("category") String ans, @Query("token") String token);

    @GET("/select_sub/{category}")
    Call<Description> sendSubAnswer(@Path("category") String ans, @Query("token") String token);
}