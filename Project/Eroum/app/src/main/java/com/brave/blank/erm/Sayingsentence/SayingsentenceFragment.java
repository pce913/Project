package com.brave.blank.erm.Sayingsentence;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import com.brave.blank.erm.AssembledData;
import com.brave.blank.erm.BaseFragment;
import com.brave.blank.erm.Consonant_Vowel.CSdata;
import com.brave.blank.erm.HomeTalkFragment;
import com.brave.blank.erm.Network.ApplicationController;
import com.brave.blank.erm.Network.NetworkService;
import com.brave.blank.erm.Network.Response.Letter;
import com.brave.blank.erm.Network.Response.Topic;
import com.brave.blank.erm.R;
import com.brave.blank.erm.ToolbarActivity;

import java.util.ArrayList;
import java.util.List;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

/**
 * Created by jeonyongjin on 2016. 7. 30..
 */

//문장 page 16
public class SayingsentenceFragment extends BaseFragment {
    ArrayList<String> sentencelist = null;
    ListView listView;
    List<Topic> topics2;

    int item_id;
    HomeTalkFragment homeTalkFragment;
    Bundle bundle;
    ArrayList<CSdata> sentencesData;

    private NetworkService networkService;
    private void initNetworkService(){
        // TODO: 13. ApplicationController 객체를 이용하여 NetworkService 가져오기
        networkService = ApplicationController.getInstance().getNetworkService();
    }
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
        initNetworkService();
        bundle=new Bundle();
        sentencesData=new ArrayList<CSdata>();
        sentencelist=new  ArrayList<String>();
        homeTalkFragment=new HomeTalkFragment();
        topics2= AssembledData.getSentenceTopics();
        Log.d("topics", ""+topics2.size());
        for(int i=0;i<topics2.size();i++){
            Log.d("topics", "topics data :"+topics2.get(i).getData());
            sentencelist.add(topics2.get(i).getData());
        }

        ViewGroup rootView= (ViewGroup)inflater.inflate(R.layout.fragment_sayingsentence,container,false);
        ArrayAdapter adapter = new ArrayAdapter(getActivity().getApplicationContext(), R.layout.simple1, sentencelist);
        listView= (ListView) rootView.findViewById(R.id.listView2);
        listView.setAdapter(adapter);

        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            //임시로 toast발생시키게 처리 액티비티 이어줄때 각 조건에 해당하는 위치에 인텐트 발생시키도록 넣어주면 됨
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                item_id=topics2.get(position).getItem_type();
                networkSentences(item_id);
                listView.setEnabled(false);

            }
        });
        rootView.setFocusableInTouchMode(true);
        rootView.requestFocus();
        rootView.setOnKeyListener(new View.OnKeyListener(){
            @Override
            public boolean onKey(View v,int keyCode, KeyEvent event) {
                if (keyCode == KeyEvent.KEYCODE_BACK) {
                    if(AssembledData.flag == 5) {
                        Log.d("keyname", "backkey");
                        Intent intentMain = new Intent(getActivity(), ToolbarActivity.class);
                        intentMain.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                        intentMain.addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
                        startActivity(intentMain);
                        getActivity().finish();
                        return true;
                    }
                    else {
                        AssembledData.flag=5;
                        return false;
                    }
                }
                else
                    return false;
            }
        });
        return rootView;
    }
    private void networkSentences(int item_id){
        Integer id=item_id;
        Call<List<Letter>> getLetter=networkService.getLetter(id.toString());
        getLetter.enqueue(new Callback<List<Letter>>() {
            @Override
            public void onResponse(Call<List<Letter>> call, Response<List<Letter>> response) {
                int statusCode = response.code();
                if(response.isSuccessful()){
                    Log.d("MyTag", "성공! Letter 응답코드 : : " + statusCode);
                    ArrayList<Letter> sentences=(ArrayList)response.body();
                    changeToCSdata(sentences);
                    bundle.putSerializable("content_item", sentencesData);
                    homeTalkFragment.setArguments(bundle);
                    // startFragment(getFragmentManager(), HomeTalkFragment.class);
                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
                    getFragmentManager().beginTransaction().replace(R.id.container,homeTalkFragment).addToBackStack(null).commit();
                    listView.setEnabled(true);
                }
                else{

                    Log.d("MyTag", "Letter 응답코드 : " + statusCode);
                }
            }

            @Override
            public void onFailure(Call<List<Letter>> call, Throwable t) {
                Log.d("MyTag","Letter 에러내용 : " + t.getMessage());
            }
        });
    }

    private void changeToCSdata(ArrayList<Letter> sentences){
        CSdata item1;
        for(int i=0;i<sentences.size();i++){
            item1 = new CSdata();
            item1.setId(sentences.get(i).getId());
            item1.setUrl(sentences.get(i).getUrl());
            item1.setData(sentences.get(i).getData());
            item1.setMode(5);
            //item1.setImg_url();                       이미지 url 받아오는 네트워크 작성후에 추가하자.
            sentencesData.add(item1);
        }
    }

}
