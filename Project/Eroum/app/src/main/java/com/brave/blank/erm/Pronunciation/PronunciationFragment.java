package com.brave.blank.erm.Pronunciation;

import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.brave.blank.erm.AssembledData;
import com.brave.blank.erm.BaseFragment;
import com.brave.blank.erm.R;

import java.text.SimpleDateFormat;
import java.util.ArrayList;

/**
 * Created by jeonyongjin on 2016. 8. 7..
 */
public class PronunciationFragment extends BaseFragment{
    View view;
    RecyclerView pronunciationRecycler;
    RecyclerView.Adapter adapter;
    ArrayList<PronunciationList> pronunciationitems;
    Bundle extra;
    int homework_id;
    SimpleDateFormat format;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
        view = inflater.inflate(R.layout.fragment_pronunciation, container, false);
        format=new SimpleDateFormat("yyyy년 MM월 dd일");
        pronunciationRecycler = (RecyclerView)view.findViewById(R.id.recycle);
        LinearLayoutManager layoutManager = new LinearLayoutManager(getActivity());
        pronunciationRecycler.setLayoutManager(layoutManager);
        pronunciationRecycler.setHasFixedSize(true);
        pronunciationitems = new ArrayList<>();

        extra = new Bundle();
        extra = getArguments();
        homework_id=extra.getInt("homework_id");

        PronunciationList item;

        for(int i=0;i<AssembledData.getSpeakingArrayList().size();i++) {
            Log.d("checkDictation" ,String.valueOf(homework_id));
            if(homework_id == AssembledData.getSpeakingArrayList().get(i).getId()){
                Log.d("checkPronunciation" ,"!!!!"+String.valueOf(homework_id));
                item = new PronunciationList();
                item.setPronunciation_date(format.format(AssembledData.getSpeakingArrayList().get(i).getStart_date()));
               // item.setPronunciation_date(AssembledData.getSpeakingArrayList().get(i).getStart_date().toString());
                item.setp_Teacher_id(AssembledData.getIdentify().getTeacher());
                item.setPronunciation_answer(AssembledData.getSpeakingArrayList().get(i).getQuestion());
                item.setPronunciation_answer_rate(AssembledData.getSpeakingArrayList().get(i).getSuccess_count());
                item.setPronunciation_playnum(AssembledData.getSpeakingArrayList().get(i).getChallenge_count());
                pronunciationitems.add(item);
            }
        }
        adapter = new PronunciationRecyclerAdapter(pronunciationitems, getActivity(),R.layout.pronunciationlist_item);
        pronunciationRecycler.setAdapter(adapter);
        return view;
    }
}
