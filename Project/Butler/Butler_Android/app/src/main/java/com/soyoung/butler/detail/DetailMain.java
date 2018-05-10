package com.soyoung.butler.detail;

import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentStatePagerAdapter;
import android.support.v4.view.ViewPager;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.widget.ImageButton;
import android.widget.TextView;

import com.soyoung.butler.R;
import com.soyoung.butler.application.ApplicationController;
import com.soyoung.butler.network.NetworkService;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class DetailMain extends AppCompatActivity {
    TextView kor_title,eng_title,location_info,content_info;
    private ViewPager mViewPager;
    private PagerAdapter mPagerAdapter;
    private DetailResult detailResult;
    NetworkService networkService ;
    String city_id;
    ImageButton nextBtn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_detail_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        initView();
        Intent intent = getIntent();
        city_id = intent.getExtras().getString("city_id");
        getTextInfo();

    }
    public void initView(){
        kor_title = (TextView)findViewById(R.id.kor_title);
        eng_title = (TextView)findViewById(R.id.eng_title);
        location_info = (TextView)findViewById(R.id.location);
        content_info = (TextView)findViewById(R.id.content_info);
        mViewPager = (ViewPager)findViewById(R.id.pager_detail);
        nextBtn = (ImageButton)findViewById(R.id.nextBtn);
    }

    public void getTextInfo(){
        networkService = ApplicationController.getInstance().getNetworkService();
        Call<DetailResult> detail_item = networkService.getDetail(city_id);
        detail_item.enqueue(new Callback<DetailResult>() {
            @Override
            public void onResponse(Call<DetailResult> call, Response<DetailResult> response) {
                detailResult = response.body();
                kor_title.setText(detailResult.spot);
                eng_title.setText(detailResult.spot_eng);
                location_info.setText(detailResult.address);
                int index = detailResult.information.indexOf('&');
                int end = detailResult.information.length();
                content_info.setText(detailResult.information.substring(0,index-1) + "\n" + detailResult.information.substring(index+1,end-1));
                content_info.setText(detailResult.information);
                mPagerAdapter = new PagerAdapter(getSupportFragmentManager());
                mViewPager.setAdapter(mPagerAdapter);

            }
            @Override
            public void onFailure(Call<DetailResult> call, Throwable t) {

            }
        });

    }

    private class PagerAdapter extends FragmentStatePagerAdapter {

        public PagerAdapter(FragmentManager fm) {super(fm);}
        @Override
        public Fragment getItem(int position) {
            PageFragment3.city_id = city_id;
            return PageFragment3.create(position);
        }

        @Override
        public int getCount() {
            return 3;  // 총 5개의 page를 보여줍니다.
        }
    }
}
