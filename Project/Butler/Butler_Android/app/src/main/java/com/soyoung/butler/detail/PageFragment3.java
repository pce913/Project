package com.soyoung.butler.detail;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import com.bumptech.glide.Glide;
import com.soyoung.butler.R;
import com.soyoung.butler.application.ApplicationController;
import com.soyoung.butler.network.NetworkService;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class PageFragment3 extends Fragment {
    NetworkService networkService = ApplicationController.getInstance().getNetworkService();
    private int mPageNumber;
    public static String city_id;
    DetailResult detailResult;


    public static PageFragment3 create(int pageNumber) {
        PageFragment3 fragment = new PageFragment3();
        Bundle args = new Bundle();
        args.putInt("page", pageNumber);
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mPageNumber = getArguments().getInt("page");
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        final ViewGroup rootView = (ViewGroup) inflater.inflate(R.layout.fragment_page_detail, container, false);
        final ImageView image = (ImageView)rootView.findViewById(R.id.detail_image);

        final Call<DetailResult> detail_item = networkService.getDetail(city_id);
        detail_item.enqueue(new Callback<DetailResult>() {
            @Override
            public void onResponse(Call<DetailResult> call, Response<DetailResult> response) {
                detailResult = response.body();
                Glide.with(rootView.getContext()).load(detailResult.image_url.get(mPageNumber)).into(image);
            }

            @Override
            public void onFailure(Call<DetailResult> call, Throwable t) {

            }
        });
        return rootView;
    }

}