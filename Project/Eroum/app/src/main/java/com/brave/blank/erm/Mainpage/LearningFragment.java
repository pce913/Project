package com.brave.blank.erm.Mainpage;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import com.brave.blank.erm.AssembledData;
import com.brave.blank.erm.BaseFragment;
import com.brave.blank.erm.ContentActivity;
import com.brave.blank.erm.Network.ApplicationController;
import com.brave.blank.erm.Network.NetworkService;
import com.brave.blank.erm.Network.Response.StudyInfo;
import com.brave.blank.erm.Network.Response.Topic;
import com.brave.blank.erm.Network.Token;
import com.brave.blank.erm.R;

import java.util.ArrayList;
import java.util.List;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

/**
 * Created by jeonyongjin on 2016. 7. 27..
 */

// 배우기 탭 page 3
public class LearningFragment extends BaseFragment {
    ArrayList<String> learninglist = new ArrayList<String>();
    ListView listView;
    List<Topic> topics;
    List<StudyInfo> learnedInfos;
    private NetworkService networkService;
    private void initNetworkService(){
        // TODO: 13. ApplicationController 객체를 이용하여 NetworkService 가져오기
        networkService = ApplicationController.getInstance().getNetworkService();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
        initNetworkService();
        networkTopic("0");
        networkTopic("1");
        networkLearnedInfo();
        networkSavedInfo();
        learninglist.add(0,"소리내기");
        learninglist.add(1,"자음/모음");
        learninglist.add(2,"받침");
        learninglist.add(3,"단어");
        learninglist.add(4,"문장");


        ViewGroup rootView= (ViewGroup)inflater.inflate(R.layout.fragment_learning,container,false);
        ArrayAdapter adapter = new ArrayAdapter(getActivity().getApplicationContext(), R.layout.simple1, learninglist);
        listView= (ListView) rootView.findViewById(R.id.listView1);
        listView.setAdapter(adapter);
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            //임시로 toast발생시키게 처리 액티비티 이어줄때 각 조건에 해당하는 위치에 인텐트 발생시키도록 넣어주면 됨
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                if(id == 0){                       //소리내기로 이동.
                    Intent intent = new Intent(getActivity().getApplicationContext(), ContentActivity.class);
                    intent.putExtra("class", "SoundTestFragment.class");
                    startActivity(intent);
                }
                else if(id == 1) {
                    Intent intent = new Intent(getActivity().getApplicationContext(), ContentActivity.class);
                    intent.putExtra("class", "Consonant_VowelFragment.class");
                    startActivity(intent);
                }
                else if(id == 2){
                    Intent intent = new Intent(getActivity().getApplicationContext(), ContentActivity.class);
                    intent.putExtra("class", "FinalConsonantFragment.class");
                    startActivity(intent);
                }
                else if(id == 3){
                    Intent intent = new Intent(getActivity().getApplicationContext(), ContentActivity.class);
                    intent.putExtra("class", "SayingwordsFragment.class");
                    startActivity(intent);
                }
                else if(id == 4){
                    Intent intent = new Intent(getActivity().getApplicationContext(), ContentActivity.class);
                    intent.putExtra("class", "SayingsentenceFragment.class");
                    startActivity(intent);
                }
            }
        });
        return rootView;
    }

    public void networkTopic(final String type){
        Call<List<Topic>> topicCall=networkService.getTopic(type);              //단어에 대한 주제 가져오기.
        topicCall.enqueue(new Callback<List<Topic>>() {
            @Override
            public void onResponse(Call<List<Topic>> call, Response<List<Topic>> response) {
                int statusCode = response.code();
                if (response.isSuccessful()) {
                    Log.d("MyTag", "성공! Topic 응답코드  : " + statusCode);
                    topics = response.body();
                 //   AssembledData.setTopics(topics);
                    for(int i=0;i<topics.size();i++){
                      Log.d("networkTopic : ", topics.get(i).getData());
                    }
                    if(type.equals("0")){
                        AssembledData.setWordTopics(topics);
                    }
                    else
                        AssembledData.setSentenceTopics(topics);
                  //  networkLearnedInfo();
                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
                } else {
                    Log.d("MyTag", "Topic 응답코드 : " + statusCode);
                }
            }
            @Override
            public void onFailure(Call<List<Topic>> call, Throwable t) {
                Log.d("MyTag", "Topic 에러내용 : " + t.getMessage());
            }
        });
    }

    public void networkLearnedInfo(){
        Call<List<StudyInfo>> studyInfoCall=networkService.getLearnedInfo(Token.getToken());
        studyInfoCall.enqueue(new Callback<List<StudyInfo>>() {
            @Override
            public void onResponse(Call<List<StudyInfo>> call, Response<List<StudyInfo>> response) {
                int statusCode = response.code();
                if(response.isSuccessful()){
                    Log.d("MyTag", "성공! LearnedInfo 응답코드 : : " + statusCode);
                    learnedInfos=response.body();
                    AssembledData.setLearnedInfos(learnedInfos);
//                    for(int i=0;i<learnedInfos.size();i++){                                 //학습을 했던 단어인지 아닌지 체크.
//                        Log.d("homeTalk","learnedInfos.get(i).getId()"+learnedInfos.get(i).getId());
//                    }
                }
                else{
                    Log.d("MyTag", " LearnedInfo 응답코드 : " + statusCode);
                }
            }

            @Override
            public void onFailure(Call<List<StudyInfo>> call, Throwable t) {
                Log.d("MyTag"," LearnedInfo 에러내용 : " + t.getMessage());
            }
        });
    }

    public void networkSavedInfo(){
        Call<List<StudyInfo>> studyInfoCall=networkService.getSavedInfo(Token.getToken());
        studyInfoCall.enqueue(new Callback<List<StudyInfo>>() {
            @Override
            public void onResponse(Call<List<StudyInfo>> call, Response<List<StudyInfo>> response) {
                int statusCode = response.code();
                if(response.isSuccessful()){
                    List<StudyInfo> savedInfos=response.body();
                    AssembledData.setSavedInfos(savedInfos);
                    Log.d("MyTag", "성공! Saved 응답코드 : : "+ statusCode );

                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
                }
                else{
                    Log.d("MyTag", "Saved 응답코드 : " + statusCode);
                }
            }

            @Override
            public void onFailure(Call<List<StudyInfo>> call, Throwable t) {
                Log.d("MyTag", "Saved 에러내용 : " + t.getMessage());
            }
        });
    }

}
