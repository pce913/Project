package com.soyoung.butler.main;

import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.bumptech.glide.Glide;
import com.soyoung.butler.R;
import com.soyoung.butler.application.ApplicationController;
import com.soyoung.butler.network.NetworkService;

import java.util.List;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class PageFragment extends Fragment {
    NetworkService networkService = ApplicationController.getInstance().getNetworkService();
    private int mPageNumber;
    List<List_item> new_list;
    public static PageFragment create(int pageNumber) {
        PageFragment fragment = new PageFragment();
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

        final ViewGroup rootView = (ViewGroup) inflater.inflate(R.layout.fragment_page, container, false);
        final ImageView image = (ImageView)rootView.findViewById(R.id.iv_fragment);
        final TextView textview1 = (TextView)rootView.findViewById(R.id.tv_home_new_title);


        final Call<List<List_item>> new_item = networkService.getNewList("1");
        new_item.enqueue(new Callback<List<List_item>>() {
            @Override
            public void onResponse(Call<List<List_item>> call, Response<List<List_item>> response) {
                if(response.isSuccessful()){
                  new_list = response.body();
                    Glide.with(rootView.getContext()).load(new_list.get(mPageNumber).city_image_url).into(image);
                    textview1.setText(Integer.parseInt(new_list.get(mPageNumber).onenight) - 1 + "박 " + new_list.get(mPageNumber).onenight+"일 추천여행지");
                }else {
                }
            }
            @Override
            public void onFailure(Call<List<List_item>> call, Throwable t) {

            }
        });
        rootView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent intent = new Intent(rootView.getContext(),RecommendPage.class);
                intent.putExtra("pages",String.valueOf(mPageNumber));
                startActivity(intent);

            }
        });
        return rootView;

    }

}