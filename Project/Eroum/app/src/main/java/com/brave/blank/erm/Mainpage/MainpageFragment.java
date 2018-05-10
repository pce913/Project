package com.brave.blank.erm.Mainpage;

import android.os.Bundle;
import android.support.v4.view.ViewPager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.brave.blank.erm.BaseFragment;
import com.brave.blank.erm.Homeclass.HomeclassFragment;
import com.brave.blank.erm.R;
import com.brave.blank.erm.record.SlidingTabLayout;
import com.brave.blank.erm.ViewPagerAdapter;

/**
 * Created by jeonyongjin on 2016. 7. 28..
 */
//메인페이지(배우기) page 3

public class MainpageFragment extends BaseFragment {
    ViewPager pager;
    ViewPagerAdapter adapter;
    SlidingTabLayout tabs;
    CharSequence Titles[] = {"배우기","홈 클래스"};
    int Numboftabs = 2;
    LearningFragment learningFragment;
    HomeclassFragment homeclassFragment;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
        ViewGroup rootView= (ViewGroup)inflater.inflate(R.layout.fragment_mainpage,container,false);
        learningFragment = new LearningFragment();
        homeclassFragment = new HomeclassFragment();

        adapter = new ViewPagerAdapter(getActivity().getSupportFragmentManager(),Titles,Numboftabs, learningFragment, homeclassFragment);    // 뷰페이져 어댑터 생성

        pager = (ViewPager) rootView.findViewById(R.id.pager);  // 뷰페이져 뷰를 할당
        pager.setAdapter(adapter);                              // 어뎁터 세팅

        tabs = (SlidingTabLayout) rootView.findViewById(R.id.tabs); // sliding tab layout 뷰를 할당
        tabs.setDistributeEvenly(true);     // true 설정시 tab 공간을 가능한 넓이에 균등하게 분배함

        tabs.setCustomTabColorizer(new SlidingTabLayout.TabColorizer(){
            @Override
            public int getIndicatorColor(int position){
                return getResources().getColor(R.color.colorPrimary);
            }
        });

        tabs.setViewPager(pager);
        return rootView;
    }

}
