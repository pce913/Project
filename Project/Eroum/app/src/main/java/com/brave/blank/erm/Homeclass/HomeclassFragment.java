package com.brave.blank.erm.Homeclass;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ListView;

import com.brave.blank.erm.AssembledData;
import com.brave.blank.erm.BaseFragment;
import com.brave.blank.erm.ContentActivity;
import com.brave.blank.erm.Network.ApplicationController;
import com.brave.blank.erm.Network.NetworkService;
import com.brave.blank.erm.Network.Response.Homework;
import com.brave.blank.erm.Network.Response.Speaking;
import com.brave.blank.erm.Network.Response.Writing;
import com.brave.blank.erm.Network.Token;
import com.brave.blank.erm.R;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

/**
 * Created by chanung on 2016-07-31.
 */
public class HomeclassFragment extends BaseFragment {
    private static ArrayList<HomeclassList> itemDatas;
    ListView listview;
    private static HomeclassCustomAdapter adapter;
    SimpleDateFormat format;
    private NetworkService networkService;

    List<Homework> homeworksnotyet;
    List<Homework> homeworksdone;
    List<Writing> writings;
    List<Speaking> speakings;

    private void initNetworkService(){
        // TODO: 13. ApplicationController 객체를 이용하여 NetworkService 가져오기
        networkService = ApplicationController.getInstance().getNetworkService();
    }



    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        ViewGroup rootView = (ViewGroup) inflater.inflate(R.layout.fragment_homeclass, container, false);

        initNetworkService();
        networkSpeaking();
        networkWriting();
        itemDatas = new ArrayList<HomeclassList>();
        format=new SimpleDateFormat("yyyy.MM.dd");
        homeworksnotyet = AssembledData.getHomeworkNotyet();
        Log.d("homeworksnotyet", String.valueOf(homeworksnotyet.size()));
        homeworksdone = AssembledData.getHomeworkdone();
        Log.d("homeworksdone", String.valueOf(homeworksdone.size()));

        HomeclassList item;

        int type;
        for (int i = 0; i < homeworksnotyet.size(); i++) {
            item = new HomeclassList();
            type = homeworksnotyet.get(i).getType();
            item.setId(homeworksnotyet.get(i).getHomework_id());
            item.setButtonText(false);
            if(homeworksnotyet.get(i).getStart_date()!=null)
                item.setDate(format.format(homeworksnotyet.get(i).getStart_date()));
           // item.setDate(homeworksnotyet.get(i).getStart_date().toString());
            item.setSection(type);
            item.setQuestion(homeworksnotyet.get(i).getQuestion());
            itemDatas.add(item);
        }
        for (int i = 0; i < homeworksdone.size(); i++) {
            item = new HomeclassList();
            type = homeworksdone.get(i).getType();
            item.setId(homeworksdone.get(i).getHomework_id());
            item.setButtonText(true);

            if(homeworksdone.get(i).getEnd_date()!=null)
                item.setDate(format.format(homeworksdone.get(i).getEnd_date()));
           // item.setDate(homeworksdone.get(i).getEnd_date().toString());
            item.setSection(type);
            item.setQuestion(homeworksdone.get(i).getQuestion());
            itemDatas.add(item);
        }
        Log.d("itemDatas.size", String.valueOf(itemDatas.size()));

        adapter = new HomeclassCustomAdapter(getActivity().getApplicationContext(), itemDatas);
        listview = (ListView) rootView.findViewById(R.id.hclist1);
        listview.setAdapter(adapter);

        listview.setOnItemClickListener(mItemClickListener);

        return rootView;
    }
    AdapterView.OnItemClickListener mItemClickListener = new AdapterView.OnItemClickListener() {
        public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
            if(itemDatas.get(position).getConfirmsubmit()=="미제출"){
                if(itemDatas.get(position).getsection()=="받아쓰기") {
                    Log.d("id value", "id = "+ String.valueOf(itemDatas.get(position).getId()));
                    Intent intent = new Intent(getActivity().getApplicationContext(), ContentActivity.class);
                    intent.putExtra("class", "HomeclassDictationFragment.class");
                    intent.putExtra("homework_id", itemDatas.get(position).getId());
                    startActivity(intent);
                }
                else{
                    Log.d("id value", "id = "+ String.valueOf(itemDatas.get(position).getId()));
                    Intent intent = new Intent(getActivity().getApplicationContext(), ContentActivity.class);
                    intent.putExtra("class", "HomeclassSpeakingFragment.class");
                    intent.putExtra("homework_id", itemDatas.get(position).getId());
                    startActivity(intent);
                }
            }
            else if(itemDatas.get(position).getConfirmsubmit()=="제출완료"){
                if(itemDatas.get(position).getsection()=="받아쓰기") {
                    Log.d("id value", "id = "+ String.valueOf(itemDatas.get(position).getId()));
                    Intent intent = new Intent(getActivity().getApplicationContext(), ContentActivity.class);
                    intent.putExtra("class", "DictationFragment.class");
                    intent.putExtra("homework_id", itemDatas.get(position).getId());
                    startActivity(intent);
                }
                else{
                    Log.d("id value", "id = "+ String.valueOf(itemDatas.get(position).getId()));
                    Intent intent = new Intent(getActivity().getApplicationContext(), ContentActivity.class);
                    intent.putExtra("class", "PronunciationFragment.class");
                    intent.putExtra("homework_id", itemDatas.get(position).getId());
                    startActivity(intent);
                }
            }
        }
    };

    public void networkWriting(){
        Call<List<Writing>> writingCall=networkService.getWriting(Token.getToken(), true);   //4, true      7, false //받아쓰기 true  , 말해보기 false 라고 알려줬지만 그 반대로 해야함.
        writingCall.enqueue(new Callback<List<Writing>>() {
            @Override
            public void onResponse(Call<List<Writing>> call, Response<List<Writing>> response) {
                int statusCode = response.code();
                if(response.isSuccessful()){
                    Log.d("MyTag", "성공! Writing 응답코드 : : "+ statusCode );
                    writings=response.body();
                    AssembledData.setWritingList(writings);
                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
                }
                else{
                    Log.d("MyTag", "응답코드 : " + statusCode);
                }
            }
            @Override
            public void onFailure(Call<List<Writing>> call, Throwable t) {
                Log.d("MyTag","Writing 에러내용 : " + t.getMessage());
            }
        });
    }


    public void networkSpeaking(){
        Call<List<Speaking>> speakingCall=networkService.getSpeaking(Token.getToken(), false);               //7 false    4 true
        speakingCall.enqueue(new Callback<List<Speaking>>() {
            @Override
            public void onResponse(Call<List<Speaking>> call, Response<List<Speaking>> response) {
                int statusCode = response.code();
                if(response.isSuccessful()){
                    Log.d("MyTag", "성공! Speaking 응답코드 : : "+ statusCode );
                    speakings=response.body();
                    AssembledData.setSpeakingList(speakings);
                }
                else{
                    Log.d("MyTag", "응답코드 : " + statusCode);
                }
            }
            @Override
            public void onFailure(Call<List<Speaking>> call, Throwable t) {
                Log.d("MyTag","에러내용 : " + t.getMessage());
            }
        });
    }

    public static void refreshAdapter(){
        adapter.notifyDataSetChanged();
        Log.d("refresh", "notifyDataSetChanged() 호출됨");
    }

    public static ArrayList<HomeclassList> getItemDatas(){
        Log.d("refresh", "getItemDatas() 호출됨");
        return itemDatas;
    }

}