package com.brave.blank.erm.FinalConsonant;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
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
import com.brave.blank.erm.Network.Response.Letter;
import com.brave.blank.erm.R;
import com.brave.blank.erm.ToolbarActivity;

import java.util.ArrayList;
import java.util.List;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

/**
 * Created by jeonyongjin on 2016. 8. 7..
 */
public class FinalConsonantFragment extends BaseFragment{
    ArrayList<String> finalconsonantlist = null;
    ArrayList<CSdata> finalconsonantdata = null;
    ArrayList<Letter> finalconsonantnetworkdata =null;
    ArrayList<Letter> finalconsonantexampledata=null;
    ListView listView;
    HomeTalkFragment homeTalkFragment;
    private NetworkService networkService;
    private void initNetworkService(){
        // TODO: 13. ApplicationController 객체를 이용하여 NetworkService 가져오기
        networkService = ApplicationController.getInstance().getNetworkService();
    }
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
        initNetworkService();
        setLetter("2");            //받침 가져오기
        setLetter("3");            //받침에대한 예시 가져오기.
        ViewGroup rootView= (ViewGroup)inflater.inflate(R.layout.fragment_finalconsonant,container,false);


        finalconsonantlist = new ArrayList<String>();
        finalconsonantnetworkdata = new ArrayList<>();
        finalconsonantexampledata=new ArrayList<>();
        finalconsonantdata = new ArrayList<>();

        finalconsonantlist.add(0,"ㄱ(ㄱ,ㄲ,ㅋ,ㄱㅅ,ㄹㄱ 등)");
        finalconsonantlist.add(1,"ㄴ(ㄴ, ㄴㅈ, ㄴㅎ 등)");
        finalconsonantlist.add(2,"ㄷ(ㄷ, ㅅ, ㅆ, ㅈ, ㅊ, ㅌ 등)");
        finalconsonantlist.add(3,"ㄹ(ㄹ, ㄹㄱ, ㄹㅁ, ㄹㅂ, ㄹㅅ, ㄹㅌ, ㄹㅎ 등)");
        finalconsonantlist.add(4,"ㅁ(ㅁ, ㄹㅁ, ㄹㅂ 등)");
        finalconsonantlist.add(5,"ㅂ(ㅂ, ㄹㅂ, ㄹㅍ, ㅂㅅ 등)");
        finalconsonantlist.add(6,"ㅇ(ㅇ 등)");

        final String content_array[] ={
                "ㄱ(ㄱ,ㄲ,ㅋ,ㄱㅅ,ㄹㄱ 등)"
                ,"ㄴ(ㄴ, ㄴㅈ, ㄴㅎ 등)"
                ,"ㄷ(ㄷ, ㅅ, ㅆ, ㅈ, ㅊ, ㅌ 등)"
                ,"ㄹ(ㄹ, ㄹㄱ, ㄹㅁ, ㄹㅂ, ㄹㅅ, ㄹㅌ, ㄹㅎ 등)"
                ,"ㅁ(ㅁ, ㄹㅁ, ㄹㅂ 등"
                ,"ㅂ(ㅂ, ㄹㅂ, ㄹㅍ, ㅂㅅ 등)"
                ,"ㅇ(ㅇ 등)"};  //임시 데이터 값

        homeTalkFragment = new HomeTalkFragment();

        FinalConsonantCustomAdapter adapter = new FinalConsonantCustomAdapter(getActivity().getApplicationContext(), finalconsonantlist);
        listView= (ListView) rootView.findViewById(R.id.finalconsonantlist);
        listView.setAdapter(adapter);
        listView.setOnItemClickListener(mItemClickListener);

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
                        AssembledData.flag = 5;
                        return false;
                    }
                }
                else
                    return false;
            }
        });
        return rootView;
    }

    AdapterView.OnItemClickListener mItemClickListener = new AdapterView.OnItemClickListener() {
        public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
            Bundle bundle = new Bundle();
            setFCdata(position);
            bundle.putSerializable("content_item", finalconsonantdata);
            homeTalkFragment.setArguments(bundle);
            getFragmentManager().beginTransaction().replace(R.id.container,homeTalkFragment).addToBackStack(null).commit();
        }
    };

    public void setLetter(final String what){
        Call<List<Letter>> letterCall=networkService.getLetter(what);                 //받침 2  .  받침에 대한 예시는 3
        letterCall.enqueue(new Callback<List<Letter>>() {
            @Override
            public void onResponse(Call<List<Letter>> call, Response<List<Letter>> response) {
                int statusCode = response.code();
                if(response.isSuccessful()){
                    Log.d("MyTag", "성공! Letterfinalconsonantnetworkdata 응답코드 : : " + statusCode);
                    List<Letter> letters=response.body();
                    if(what.equals("2"))
                        finalconsonantnetworkdata = (ArrayList)letters;
                    else
                        finalconsonantexampledata=(ArrayList)letters;
                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
                }
                else{
                    Log.d("MyTag", "응답코드 : " + statusCode);
                }
            }
            @Override
            public void onFailure(Call<List<Letter>> call, Throwable t) {
                Log.d("MyTag","에러내용 : " + t.getMessage());
            }
        });
    }

    public void setFCdata(int index){
        CSdata item1 = new CSdata();
        CSdata item2=new CSdata();
        item1.setId(finalconsonantnetworkdata.get(index).getId());
        item1.setUrl(finalconsonantnetworkdata.get(index).getUrl());
        item1.setData(finalconsonantnetworkdata.get(index).getData());
        item1.setMode(2);
        item1.setImg_url(finalconsonantnetworkdata.get(index).getImg());

        item2.setId(finalconsonantexampledata.get(index).getId());
        item2.setUrl(finalconsonantexampledata.get(index).getUrl());
        item2.setData(finalconsonantexampledata.get(index).getData());
        item2.setMode(2);
        item2.setImg_url(finalconsonantexampledata.get(index).getImg());
        finalconsonantdata.add(0, item1);
        finalconsonantdata.add(1, item2);
    }

}