package com.brave.blank.erm.Dictation;

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
public class DictationFragment extends BaseFragment {
    View view;
    RecyclerView dictationRecycler;
    RecyclerView.Adapter adapter;
    ArrayList<DictationList> dictationitems;
    Bundle extra;
    int homework_id;
    SimpleDateFormat format;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
        view = inflater.inflate(R.layout.fragment_dictation, container, false);
        format=new SimpleDateFormat("yyyy년 MM월 dd일");
        dictationRecycler = (RecyclerView)view.findViewById(R.id.recycle);
        LinearLayoutManager layoutManager = new LinearLayoutManager(getActivity());
        dictationRecycler.setLayoutManager(layoutManager);
        dictationRecycler.setHasFixedSize(true);
        dictationitems = new ArrayList<>();

//                getArguments().getInt("homework_id", 0);
        extra = new Bundle();
        extra = getArguments();
        homework_id=extra.getInt("homework_id");

        Log.d("what" ," "+String.valueOf(homework_id));
        DictationList item;
        Log.d("checkDictation" ,"포문직전");

        for(int i = 0; i< AssembledData.getWritingArrayList().size(); i++){
            Log.d("checkDictation" ,"포문안쪽");
            if(homework_id==AssembledData.getWritingArrayList().get(i).getId()){
           //     Log.d("checkDictation" ,"!!!!"+String.valueOf(homework_id));
                item = new DictationList();
                item.setDictation_date(format.format(AssembledData.getWritingArrayList().get(i).getStart_date()));
        //        item.setDictation_date(AssembledData.getWritingArrayList().get(i).getStart_date().toString());
//                Log.d("checkDictation", "!!!!" + AssembledData.getWritingArrayList().get(i).getEnd_date().toString());
                item.setTeacher_id(AssembledData.getIdentify().getTeacher());
                item.setDictation_answer(AssembledData.getWritingArrayList().get(i).getQuestion());
                item.setSubmit_answer(AssembledData.getWritingArrayList().get(i).getAnswer());
                item.setDictation_answer_rate(AssembledData.getWritingArrayList().get(i).getRate());
                item.setDictation_playnum(AssembledData.getWritingArrayList().get(i).getPlay_count());
                dictationitems.add(item);
            }
        }
        adapter = new DictationRecyclerAdapter(dictationitems, getActivity(), R.layout.dictation_item);
        dictationRecycler.setAdapter(adapter);
        Log.d("checkDictation", "리턴 직전");
        return view;
    }
}