package com.brave.blank.erm.record;

import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.brave.blank.erm.AssembledData;
import com.brave.blank.erm.BaseFragment;
import com.brave.blank.erm.Network.Response.Speaking;
import com.brave.blank.erm.R;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by IT on 2016-07-24.
 */
public class SpeakingRecordFragment extends BaseFragment {
    View view;
    RecyclerView recyclerView;
    RecyclerView.Adapter adapter;
    ArrayList<List_item_speaking> lists;
    List<Speaking> speakings;
    SimpleDateFormat format;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        view = inflater.inflate(R.layout.fragment_speaking_record, container, false);
        format=new SimpleDateFormat("yyyy.MM.dd");
        recyclerView = (RecyclerView) view.findViewById(R.id.recycle_speaking);
        LinearLayoutManager layoutManager = new LinearLayoutManager(getActivity());
        layoutManager.setOrientation(LinearLayoutManager.VERTICAL);
        recyclerView.setLayoutManager(layoutManager);
        recyclerView.setHasFixedSize(true);

        speakings = AssembledData.getSpeakingArrayList(); //assembleddata에서 가공한 데이터를 얻어옴

        lists = new ArrayList<>(); //얘가 필요한거지

        List_item_speaking item;


        for (int i = 0; i < speakings.size(); i++){
            Log.d("speaking아 size가 몇이니" , String.valueOf(speakings.size()));
            item = new List_item_speaking(); // 그럼 list_item_dication객체하나를 선언혀
            item.setSpeaking_date(format.format(speakings.get(i).getEnd_date())); //차례대로 해당하는 값에 맞춰서 데이터들을 setting해주고
            item.setTeacher_id(AssembledData.getIdentify().getTeacher()); // 얘는 임시 데이터값
            item.setSpeaking_question(speakings.get(i).getQuestion());  // answer랑 question중에 어떤게 정답이고 어떤게 제출한 답인지 모르겠드
            item.setSpeaking_success_num(speakings.get(i).getSuccess_count()); // 그러면 서버에 연결해서 출력되는거 보고 어떤게 정답이고 제출한 답인지 알겟지
            item.setSpeaking_try_num(speakings.get(i).getChallenge_count());

            lists.add(item); //그러면 이제 아까 선언했던 list_item_dictation타입의 arraylist에 하나한 넣어주는거임
            //그럼 끝

        }



//        List_item_speaking[] item = new List_item_speaking[speakings.size()];
//        lists = new ArrayList<>();
////
//        speakings = AssembledData.getSpeakingArrayList();
//
//        for (int i = 0; i < item.length; i++)
//            item[i] = new List_item_speaking(speakings.get(i).getStart_date().toString(), speakings.get(i).getEnd_date().toString(),
//                    speakings.get(i).getSpk_answer().toString(), Integer.toString(speakings.get(i).getSuccess_count()),
//                    Integer.toString(speakings.get(i).getChallenge_count()));
//
//        for (int i = 0; i < item.length; i++)
//            lists.add(item[i]);
//
        adapter = new RecyclerAdapter_spk(lists, getActivity(), R.layout.speaking_item);
        recyclerView.setAdapter(adapter);


        return view;
    }
}