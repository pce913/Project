package com.brave.blank.erm.Sayingwords;

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

// 단어 page 14
public class SayingwordsFragment extends BaseFragment {
    ArrayList<String> wordlist = null;
    ListView listView;
    List<Topic> topics1;

    int item_id;
    HomeTalkFragment homeTalkFragment;
    Bundle bundle;
    ArrayList<CSdata> wordsData;

    private NetworkService networkService;
    private void initNetworkService(){
        // TODO: 13. ApplicationController 객체를 이용하여 NetworkService 가져오기
        networkService = ApplicationController.getInstance().getNetworkService();
    }
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
        initNetworkService();
        wordlist = new ArrayList<String>();
        wordsData=new ArrayList<CSdata>();

        homeTalkFragment=new HomeTalkFragment();
        bundle=new Bundle();
        Log.d("assembledData",String.valueOf(AssembledData.getWordTopics().size()));
        topics1=AssembledData.getWordTopics();
        Log.d("damn topics", String.valueOf(topics1.size()));
        for(int i=0;i<topics1.size();i++){
            wordlist.add(i,topics1.get(i).getData());
        }

        ViewGroup rootView= (ViewGroup)inflater.inflate(R.layout.fragment_sayingwords,container,false);
        ArrayAdapter adapter = new ArrayAdapter(getActivity().getApplicationContext(), R.layout.simple1, wordlist);
        listView= (ListView) rootView.findViewById(R.id.listView1);
        listView.setAdapter(adapter);

        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            //임시로 toast발생시키게 처리 액티비티 이어줄때 각 조건에 해당하는 위치에 인텐트 발생시키도록 넣어주면 됨
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                item_id=topics1.get(position).getItem_type();
                networkWords(item_id);
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

    private void networkWords(int item_id){
        Integer id=item_id;
        Call<List<Letter>> getLetter=networkService.getLetter(id.toString());
        getLetter.enqueue(new Callback<List<Letter>>() {
            @Override
            public void onResponse(Call<List<Letter>> call, Response<List<Letter>> response) {
                int statusCode = response.code();
                if(response.isSuccessful()){
                    Log.d("MyTag", "성공! Letter 응답코드 : : " + statusCode);
                    ArrayList<Letter> words=(ArrayList)response.body();
                    changeToCSdata(words);

                    bundle.putSerializable("content_item",wordsData);
                    homeTalkFragment.setArguments(bundle);
                    //startFragment(getFragmentManager(), HomeTalkFragment.class);
                    getFragmentManager().beginTransaction().replace(R.id.container,homeTalkFragment).addToBackStack(null).commit();
                    listView.setEnabled(true);

                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
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


    private void changeToCSdata(ArrayList<Letter> words){
        CSdata item1;
        for(int i=0;i<words.size();i++){
            item1 = new CSdata();
            item1.setId(words.get(i).getId());
            item1.setUrl(words.get(i).getUrl());
            item1.setData(words.get(i).getData());
            item1.setMode(4);
            //item1.setImg_url();                       이미지 url 받아오는 네트워크 작성후에 추가하자.
            wordsData.add(item1);
        }
    }

}
