package com.brave.blank.erm.Consonant_Vowel;

import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.TextView;

import com.brave.blank.erm.BaseFragment;
import com.brave.blank.erm.HomeTalkFragment;
import com.brave.blank.erm.Network.ApplicationController;
import com.brave.blank.erm.Network.NetworkService;
import com.brave.blank.erm.Network.Response.Letter;
import com.brave.blank.erm.Network.Response.StudyInfo;
import com.brave.blank.erm.Network.Token;
import com.brave.blank.erm.R;

import java.util.ArrayList;
import java.util.List;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

/**
 * Created by jeonyongjin on 2016. 7. 30..
 */

//자음모음(자음클릭) page 9
public class ConsonantFragment extends BaseFragment {
    GridView gridview;
    ArrayList<Letter> consonantdata = null;
    ArrayList<Integer> studiedId;
    ArrayList<CSdata> csindexdata = null;
    HomeTalkFragment homeTalkFragment;

    private NetworkService networkService;

    private void initNetworkService() {
        // TODO: 13. ApplicationController 객체를 이용하여 NetworkService 가져오기
        networkService = ApplicationController.getInstance().getNetworkService();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, final ViewGroup container, Bundle savedInstanceState) {
        initNetworkService();
        setLetter(); //글자 받아오기
        consonantdata = new ArrayList<Letter>();
        csindexdata = new ArrayList<CSdata>();
        //type 1 가져오기.
        // 가정 id는 정렬된 값으로 들어온다.

        ViewGroup rootView = (ViewGroup) inflater.inflate(R.layout.fragment_consonant_vowel, container, false);
        gridview = (GridView) rootView.findViewById(R.id.gridView1);


        //어떠한 컨텐츠를 HomeTalkFragment

        homeTalkFragment = new HomeTalkFragment();

        gridview.setOnItemClickListener(mItemClickListener);
        return rootView;
    }

    AdapterView.OnItemClickListener mItemClickListener = new AdapterView.OnItemClickListener() {
        public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
            Bundle bundle = new Bundle();
            setData_cv(position);
            bundle.putSerializable("content_item", csindexdata);
            homeTalkFragment.setArguments(bundle);
            getFragmentManager().beginTransaction().replace(R.id.container, homeTalkFragment).addToBackStack(null).commit();
        }
    };

    public class gridAdapter extends BaseAdapter {
        LayoutInflater inf;
        int j = 0;

        public gridAdapter() {
            inf = (LayoutInflater) getActivity().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        }

        @Override
        public int getCount() {
            return consonantdata.size();
        }

        @Override
        public Object getItem(int position) {
            return consonantdata.get(position);
        }

        @Override
        public long getItemId(int position) {
            return position;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            if (convertView == null) {
                convertView = inf.inflate(R.layout.item, parent, false);
            }
            TextView textView = (TextView) convertView.findViewById(R.id.consonant);
            textView.setText(consonantdata.get(position).getData());
            Log.d("checking","j : "+j);
            //학습한 데이터면 배경색을 회색으로 칠해주는 코
            if (j < studiedId.size() && studiedId.get(j) == position) {
                convertView.setBackgroundColor(Color.parseColor("#80FBAF3F"));
                Log.d("checking", "studiedId.size() :  " + studiedId.size());
                j++;
            }

            return convertView;
        }
    }

    public void setLetter() {
        Call<List<Letter>> letterCall = networkService.getLetter("0");                    //자음 0
        letterCall.enqueue(new Callback<List<Letter>>() {
            @Override
            public void onResponse(Call<List<Letter>> call, Response<List<Letter>> response) {
                int statusCode = response.code();
                if (response.isSuccessful()) {
                    Log.d("MyTag", "성공! Letter 응답코드 : : " + statusCode);
                    List<Letter> letters = response.body();
                    consonantdata = (ArrayList) letters;
                    setBeforehandStudy();                                        //학습한 자음 알아내기.
                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
                } else {
                    Log.d("MyTag", "응답코드 : " + statusCode);
                }
            }

            @Override
            public void onFailure(Call<List<Letter>> call, Throwable t) {
                Log.d("MyTag", "에러내용 : " + t.getMessage());
            }
        });
    }

    public void setBeforehandStudy() {
        Log.d("MyTag", Token.getToken());
        Call<List<StudyInfo>> studyInfoCall = networkService.getLearnedInfo(Token.getToken());
        studyInfoCall.enqueue(new Callback<List<StudyInfo>>() {
            @Override
            public void onResponse(Call<List<StudyInfo>> call, Response<List<StudyInfo>> response) {
                int statusCode = response.code();
                if (response.isSuccessful()) {
                    Log.d("MyTag", "성공! StudyInfo응답코드 : : " + statusCode);
                    List<StudyInfo> studyInfos = response.body();

                    for(int i=0;i<studyInfos.size();i++){
                        Log.d("studyInfo : :",studyInfos.get(i).getData());
                    }

                    studiedId = new ArrayList<Integer>();
                    for (int i = 0; i < consonantdata.size(); i++) {
                        for (int j = 0; j < studyInfos.size(); j++) {
                            if (consonantdata.get(i).getId() == studyInfos.get(j).getId()) {
                                studiedId.add(i);
                               // j++;
                            }
                        }
                    }
                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
                    gridview.setAdapter(new gridAdapter());
                } else {
                    Log.d("MyTag", "studyInfo 응답코드 : " + statusCode);
                }
            }

            @Override
            public void onFailure(Call<List<StudyInfo>> call, Throwable t) {
                Log.d("MyTag", "에러내용 : " + t.getMessage());
            }
        });
    }

    private void setData_cv(int index) {
        CSdata item1 = new CSdata();
        item1.setId(consonantdata.get(index).getId());
        item1.setUrl(consonantdata.get(index).getUrl());
        item1.setData(consonantdata.get(index).getData());
        item1.setImg_url(consonantdata.get(index).getImg());
        item1.setMode(0);
        csindexdata.add(0, item1);
    }
}