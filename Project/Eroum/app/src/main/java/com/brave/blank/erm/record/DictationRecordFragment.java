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
import com.brave.blank.erm.Network.Response.Writing;
import com.brave.blank.erm.R;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

public class DictationRecordFragment extends BaseFragment {
    View view;
    RecyclerView recordRecycler;
    RecyclerView.Adapter adapter;
    ArrayList<List_item_dictation> lists;
    List<Writing> writings;
    SimpleDateFormat format;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        view = inflater.inflate(R.layout.fragment_dictation_record, container, false);
        format=new SimpleDateFormat("yyyy.MM.dd");
        recordRecycler = (RecyclerView)view.findViewById(R.id.recycle);
        LinearLayoutManager layoutManager = new LinearLayoutManager(getActivity());
        layoutManager.setOrientation(LinearLayoutManager.VERTICAL);
        recordRecycler.setLayoutManager(layoutManager);
        recordRecycler.setHasFixedSize(true);

        Log.i("MyTag", "recycler2");

        writings = AssembledData.getWritingArrayList(); //assembleddata에서 가공한 데이터를 얻어옴
//        그후 size를 할당받아야지 민주야 그런데 밑애있는 애는 필요없는 애네
//        List_item_dictation[] item = new List_item_dictation[writings.size()];

        lists = new ArrayList<>(); //얘가 필요한거지

        List_item_dictation item;


        for (int i = 0; i < writings.size(); i++){
            Log.d("writing아 size가 몇이니" , String.valueOf(writings.size()));
            item = new List_item_dictation(); // 그럼 list_item_dication객체하나를 선언혀
            item.setDate(format.format(writings.get(i).getEnd_date())); //차례대로 해당하는 값에 맞춰서 데이터들을 setting해주고
            item.setTeacher_id(AssembledData.getIdentify().getTeacher()); // 얘는 임시 데이터값
            item.setAnswer(writings.get(i).getQuestion());  // answer랑 question중에 어떤게 정답이고 어떤게 제출한 답인지 모르겠드
            item.setQuestion(writings.get(i).getAnswer()); // 그러면 서버에 연결해서 출력되는거 보고 어떤게 정답이고 제출한 답인지 알겟지
            item.setRate(writings.get(i).getRate());
            item.setPlay_count(writings.get(i).getPlay_count()); //이렇게 하면 새로 할당받았던 list_item_dictation한개 에 대해서
                                                                 //데이터가 세팅이 완료된거지
            lists.add(item); //그러면 이제 아까 선언했던 list_item_dictation타입의 arraylist에 하나한 넣어주는거임
                             //그럼 끝
        }

        adapter = new RecyclerAdapter_dic(lists, getActivity(), R.layout.dictation_item);
        recordRecycler.setAdapter(adapter);


        return view;
    }
}