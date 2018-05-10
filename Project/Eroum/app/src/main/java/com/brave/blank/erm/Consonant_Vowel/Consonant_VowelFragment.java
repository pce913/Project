package com.brave.blank.erm.Consonant_Vowel;

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
import com.brave.blank.erm.R;
import com.brave.blank.erm.ToolbarActivity;

import java.util.ArrayList;

/**
 * Created by jeonyongjin on 2016. 7. 29..
 */

//자음모음 page 8
public class Consonant_VowelFragment extends BaseFragment {
    ArrayList<String> c_list = null;
    ArrayList<String> v_list = null;
    ConsonantFragment consonantFragment;
    VowelFragment vowelFragment;

    ListView listView, listView1;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
        c_list = new ArrayList<>();
        c_list.add("<자음>");
        v_list = new ArrayList<>();
        v_list.add("<모음>");

        consonantFragment = new ConsonantFragment();
        vowelFragment = new VowelFragment();

        ViewGroup rootView= (ViewGroup)inflater.inflate(R.layout.fragment_consonant_vowel,container,false);
        ArrayAdapter adapter = new ArrayAdapter(getActivity().getApplicationContext(), R.layout.simple, c_list);
        ArrayAdapter adapter1 = new ArrayAdapter(getActivity().getApplicationContext(), R.layout.simple,v_list);

        listView = (ListView) rootView.findViewById(R.id.listView3);
        listView1 = (ListView) rootView.findViewById(R.id.listView4);

        listView.setAdapter(adapter);
        listView1.setAdapter(adapter1);

        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            //임시로 toast발생시키게 처리 액티비티 이어줄때 각 조건에 해당하는 위치에 인텐트 발생시키도록 넣어주면 됨
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                if(id == 0){
                    startFragment(getFragmentManager(),ConsonantFragment.class);
                }
            }
        });
        listView1.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            //임시로 toast발생시키게 처리 액티비티 이어줄때 각 조건에 해당하는 위치에 인텐트 발생시키도록 넣어주면 됨
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                if(id == 0){
                    startFragment(getFragmentManager(),VowelFragment.class);
                }
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


}
