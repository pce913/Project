package com.brave.blank.erm.StoredExercise;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ListView;

import com.brave.blank.erm.AssembledData;
import com.brave.blank.erm.BaseFragment;
import com.brave.blank.erm.Consonant_Vowel.CSdata;
import com.brave.blank.erm.HomeTalkFragment;
import com.brave.blank.erm.Network.ApplicationController;
import com.brave.blank.erm.Network.NetworkService;
import com.brave.blank.erm.Network.Response.StudyInfo;
import com.brave.blank.erm.R;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by jeonyongjin on 2016. 8. 7..
 */
// 저장한 학습내용

public class StoredExerciseFragment extends BaseFragment{
    private ArrayList<StoredExerciseList> exerciseDatas = null;
    ListView listview;
    List<StudyInfo> savedInfos;
    StoredExerciseCustomAdapter adapter;

    ArrayList<CSdata> storeddata = null;

    HomeTalkFragment homeTalkFragment;

    private NetworkService networkService;
    private void initNetworkService(){
        // TODO: 13. ApplicationController 객체를 이용하여 NetworkService 가져오기
        networkService = ApplicationController.getInstance().getNetworkService();
    }
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        ViewGroup rootView = (ViewGroup) inflater.inflate(R.layout.fragment_storedexercise, container, false);
        initNetworkService();
      //  networkSavedInfo();
        savedInfos= AssembledData.getSavedInfos();

        exerciseDatas = new ArrayList<StoredExerciseList>();

        storeddata = new ArrayList<>();

        homeTalkFragment = new HomeTalkFragment();

        StoredExerciseList item;
        int type;
        for(int i=0;i<savedInfos.size();i++){
            item=new StoredExerciseList();
            type=savedInfos.get(i).getType();
            if(type==0 || type==1)                        //가정 type 0,1 자음모음 /2 받침 /3 단어 /4 문장
                item.setSection(0);                        //section 0 자음모음 /3 받침 /2 단어 /1 문장
          else if(type==2)
              item.setSection(3);
          else if(type==3)
              item.setSection(2);
          else if(type==4)
              item.setSection(1);
            item.setId(savedInfos.get(i).getId());
            item.setDate(savedInfos.get(i).getDate().toString());
            item.setExercise_sentence(savedInfos.get(i).getData());
            item.setUrl(savedInfos.get(i).getUrl());
            item.setType(type);
            exerciseDatas.add(item);
        }
//        StoredExerciseList item1 = new StoredExerciseList();
//        item1.setSection(0);
//        item1.setDate(Date.UTC(2016,7,30,0,0,0));
//        item1.setExercise_sentence("헬로 뤠드 헤얼 미스터 펄크");
//        exerciseDatas.add(0,item1);

        adapter = new StoredExerciseCustomAdapter(getActivity().getApplicationContext(), exerciseDatas);
        listview = (ListView) rootView.findViewById(R.id.hclist1);
        listview.setAdapter(adapter);
        listview.setOnItemClickListener(mItemClickListener);
        return rootView;
    }
    AdapterView.OnItemClickListener mItemClickListener = new AdapterView.OnItemClickListener() {
        public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
            Bundle bundle = new Bundle();
            setStoreddata(position);
            bundle.putSerializable("content_item", storeddata);
            homeTalkFragment.setArguments(bundle);
            getFragmentManager().beginTransaction().replace(R.id.container,homeTalkFragment).addToBackStack(null).commit();
        }
    };


    private void setStoreddata(int index){
        CSdata item1 = new CSdata();
        item1.setId(exerciseDatas.get(index).getId());
        item1.setUrl(exerciseDatas.get(index).getUrl());
        item1.setData(exerciseDatas.get(index).getExercise_sentence());
        if(exerciseDatas.get(index).getType() == 1){
            item1.setMode(0);
        }
        else if(exerciseDatas.get(index).getType() == 2){
            item1.setMode(1);
        }
        else if(exerciseDatas.get(index).getType() == 3){
            item1.setMode(2);
        }
        else if(exerciseDatas.get(index).getType() == 4){
            item1.setMode(3);
        }
        else{
            item1.setMode(4);
        }
        storeddata.add(0,item1);
    }

}
