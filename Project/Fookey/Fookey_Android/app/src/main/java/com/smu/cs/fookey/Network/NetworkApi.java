package com.smu.cs.fookey.Network;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;

import okhttp3.MediaType;
import okhttp3.MultipartBody;
import okhttp3.RequestBody;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

/**
 * Created by Chan on 2017-08-23.
 */
public class NetworkApi extends AppCompatActivity {
    private NetworkService networkService;
    private static NetworkApi instance;
    private Token token;

    private void initNetworkService(){
        // TODO: 13. ApplicationController 객체를 이용하여 NetworkService 가져오기
        networkService = ApplicationController.getInstance().getNetworkService();
    }

    NetworkApi(){
        NetworkApi.instance=this;
        initNetworkService();
        getNetworkToken();
    }

    public static NetworkApi getNetworkApi() {
        return instance;
    }

    private void getNetworkToken(){
        Call<Token> getToken=networkService.getToken();
        getToken.enqueue(new Callback<Token>() {
            @Override
            public void onResponse(Call<Token> call, Response<Token> response) {
                int statusCode = response.code();
                if(response.isSuccessful()){
                    token=(Token)response.body();
                }
                else{
                }
            }

            @Override
            public void onFailure(Call<Token> call, Throwable t) {
            }
        });
    }

    public List<String> sendImage(Context context, String path)  {
        List<String> mainList = null;
        MultipartBody.Part body = getCompressedImage(context, path);
        RequestBody description = getMultipartDescription(token.getToken());
        Call<Category> call = networkService.sendImage(description, body);
        Category category = null;
        try {
            category = call.execute().body();
        } catch (IOException e) {
            e.printStackTrace();
        }
        if(call.isExecuted())
            mainList = category.getCategories();
        else
            mainList = new ArrayList<>();
        return mainList;
    }

    public List<String> sendMainAnswer(String ans){
        List<String> subList;
        Call<Category> call = networkService.sendMainAnswer(ans, token.getToken());
        Category category = null;
        try {
            category = call.execute().body();
        } catch (IOException e) {
            e.printStackTrace();
        }
        if(call.isExecuted())
            subList = category.getCategories();
        else
            subList = new ArrayList<>();
        return subList;
    }

    public List<String> sendSubAnswer(String ans){
        List<String> retDesc = null;
        Call<Description> call = networkService.sendSubAnswer(ans, token.getToken());
        Description description = null;
        try {
            description = call.execute().body();
        } catch (IOException e) {
            e.printStackTrace();
        }
        if(call.isExecuted())
            retDesc = description.getFood_info();
        else
            retDesc = new ArrayList<>();

        Log.i("NET", retDesc.get(0));
        return retDesc;
    }

    private MultipartBody.Part getCompressedImage(Context context, String path){
        String imgUri = path;
        BitmapFactory.Options options = new BitmapFactory.Options();
//                        options.inSampleSize = 4; //얼마나 줄일지 설정하는 옵션 4--> 1/4로 줄이겠다
        //입력으로 들어오는 uri가 사실은 String이다. String to Uri로 바꿔주는 작업이 필요하다.
        Uri uri= Uri.fromFile(new File(imgUri));//Uri.parse((imgUri));
        Log.i("imgUri", uri.toString());
        InputStream in = null;
        try {
            in = context.getContentResolver().openInputStream(uri);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        if(in == null)
            Log.w("INPUT_STREAM", "NULL");
        Bitmap bitmap = BitmapFactory.decodeStream(in, null, options); // InputStream 으로부터 Bitmap 을 만들어 준다.
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        if(bitmap == null)
            Log.w("BITMAP", "NULL");
        bitmap.compress(Bitmap.CompressFormat.JPEG, 20, baos); // 압축 옵션( JPEG, PNG ) , 품질 설정 ( 0 - 100까지의 int형 ),

        RequestBody photoBody = RequestBody.create(MediaType.parse("image/jpg"), baos.toByteArray());
        File photo = new File(imgUri);
        MultipartBody.Part body = MultipartBody.Part.createFormData("picture", photo.getName(), photoBody);
        return body;
    }

    private RequestBody getMultipartDescription(String descriptionString){
        RequestBody description = RequestBody.create(okhttp3.MultipartBody.FORM, descriptionString);
        return description;
    }
}


