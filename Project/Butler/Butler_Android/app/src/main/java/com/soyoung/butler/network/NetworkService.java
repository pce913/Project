package com.soyoung.butler.network;

import com.soyoung.butler.attraction.AlternativesCityID;
import com.soyoung.butler.attraction.AttractionResult;
import com.soyoung.butler.attraction.AttractionSend;
import com.soyoung.butler.attraction.EssentailCityID;
import com.soyoung.butler.detail.DetailResult;
import com.soyoung.butler.drag.CityData;
import com.soyoung.butler.drag.DaySend;
import com.soyoung.butler.drag.OneDayResult;
import com.soyoung.butler.drag.OneDaySend;
import com.soyoung.butler.journey_day.JourneyDaySend;
import com.soyoung.butler.journey_day.MapData;
import com.soyoung.butler.loginfo.MainListData;
import com.soyoung.butler.loginfo.MainResult;
import com.soyoung.butler.main.List_item;
import com.soyoung.butler.person_dataset.PersonInfoResult;
import com.soyoung.butler.recommend_path.RecommendResult;
import com.soyoung.butler.register.RegisterData;
import com.soyoung.butler.register.RegisterResult;
import com.soyoung.butler.select_spot.SelectResult;
import com.soyoung.butler.select_spot.SelectSend;

import java.util.ArrayList;
import java.util.List;

import retrofit2.Call;
import retrofit2.http.Body;
import retrofit2.http.GET;
import retrofit2.http.POST;
import retrofit2.http.Path;

/**
 * Created by Soyoung on 16. 12. 28..
 */
public interface NetworkService {

    @POST("sign/in_email")
    Call<MainResult> requestMain(@Body MainListData mainListDatas);
    //Call<MainResult> requestMain(@Part("email")RequestBody email,
     //                            @Part("password") RequestBody password);

    @POST("sign/up_email")
    Call<RegisterResult> requestRegister(@Body RegisterData registerData);

    @GET("sign/info/{user_id}")
    Call<PersonInfoResult> getPersonInfoResult(@Path("user_id")String user_id);

    @GET("main/{what_city}")
    Call<List<List_item>> getNewList(@Path("what_city")String what_city);

    @POST("main/search")
    Call<ArrayList<AttractionResult>> requestAttraction(@Body AttractionSend attractionSend);

    @GET("land/spot/{city_sight_id}")
    Call<DetailResult> getDetail(@Path("city_sight_id")String id);

    @POST("main/send_essentials")
    Call<EssentailCityID> requestEssential(@Body EssentailCityID essentailCityID);

    @POST("main/send_alternatives")
    Call<AlternativesCityID> requestAlternative(@Body AlternativesCityID alternativesCityID);

    @POST("main/show_selected_spot")
    Call<SelectResult> requestSelectResult(@Body SelectSend user_id);

    @POST("main/sub_spot")
    Call<List<CityData>> requestSubspot(@Body CityData cityData);

    @POST("bucket/save_schedule")
    Call<DaySend> sendDay(@Body DaySend daySend);

    @GET("recommend/{user_id}")
    Call<ArrayList<ArrayList<String>>> getRecommend(@Path("user_id")String userid);

    @POST("today/route")
    Call <List<MapData>> requestMap(@Body JourneyDaySend journeyDaySend);

    @POST("land/oneday")
    Call <ArrayList<OneDayResult>> requestLocation(@Body OneDaySend oneDaySend);

    @GET("bucket/show_schedule/{user_id}")
    Call<RecommendResult>  getScheduleDatas(@Path("user_id")String user_id);

}
