package com.brave.blank.erm.record;

import android.os.Bundle;
import android.support.v4.view.ViewPager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.brave.blank.erm.BaseFragment;
import com.brave.blank.erm.ContentActivity;
import com.brave.blank.erm.R;
import com.brave.blank.erm.ViewPagerAdapter;

/**
 * Created by chanung on 2016-07-28.
 */
public class PracticeRecordFragment extends BaseFragment {
    ViewPager pager;
    ViewPagerAdapter adapter;
    SlidingTabLayout tabs;
    CharSequence Titles[] = {"받아쓰기", "말해보기"};
    int Numboftabs = 2;
    View view;
    DictationRecordFragment dictationRecordFragment;
    SpeakingRecordFragment speakingRecordFragment;


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        view = inflater.inflate(R.layout.fragment_practice_record, container, false);
        dictationRecordFragment = new DictationRecordFragment();
        speakingRecordFragment = new SpeakingRecordFragment();

        // Creating The ViewPagerAdapter and Passing Fragment Manager, Titles fot the Tabs and Number Of Tabs.

        ContentActivity activity = (ContentActivity) getActivity();
        adapter = new ViewPagerAdapter(activity.getSupportFragmentManager(), Titles, Numboftabs, dictationRecordFragment, speakingRecordFragment);                           //Activity에 있는 객체를 가져와서 쓰자.

        // Assigning ViewPager View and setting the adapter
        pager = (ViewPager) view.findViewById(R.id.pager);
        pager.setAdapter(adapter);

        // Assiging the Sliding Tab Layout View
        tabs = (SlidingTabLayout) view.findViewById(R.id.tabs);
        tabs.setDistributeEvenly(true); // To make the Tabs Fixed set this true, This makes the tabs Space Evenly in Available width

        // Setting Custom Color for the Scroll bar indicator of the Tab View
        tabs.setCustomTabColorizer(new SlidingTabLayout.TabColorizer() {
            @Override
            public int getIndicatorColor(int position) {
                return getResources().getColor(R.color.white);
            }
        });

        // Setting the ViewPager For the SlidingTabsLayout
        tabs.setViewPager(pager);
        return view;
    }
}