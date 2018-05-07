package com.brave.blank.erm;

import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.brave.blank.erm.Consonant_Vowel.Consonant_VowelFragment;
import com.brave.blank.erm.FinalConsonant.FinalConsonantFragment;
import com.brave.blank.erm.Network.Response.StudyInfo;
import com.brave.blank.erm.Network.Response.Topic;
import com.brave.blank.erm.Sayingsentence.SayingsentenceFragment;
import com.brave.blank.erm.Sayingwords.SayingwordsFragment;
import com.brave.blank.erm.SoundWaveVibration.SoundTestFragment;
import com.brave.blank.erm.SpeechRecognition.SoundMeter;

import java.util.ArrayList;


/**
 * Created by chanung on 2016-07-24.
 */

//page 5
public class NoiseTestFragment extends BaseFragment {

    private static final int THRESHOLD = 60;
    ProgressBar progressBar;
    Button button_ok;
    TextView textView3;
    TextView textView_name;
    Long longAverage;
    Handler handler = new Handler();
    ArrayList<Topic> topics;
    ArrayList<StudyInfo> studyInfos;
    Bundle extra;
    String fragment_name;


    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        ViewGroup rootView = (ViewGroup) inflater.inflate(R.layout.fragment_noise_test, container, false);
        progressBar = (ProgressBar) rootView.findViewById(R.id.progressBar);
        button_ok = (Button) rootView.findViewById(R.id.button_ok);
        textView3 = (TextView) rootView.findViewById(R.id.textView3);
        textView_name=(TextView) rootView.findViewById(R.id.textView);
       // textView_name.setText("현재 " + AssembledData.getIdentify().getName()+"님이 계신 곳이");                          //name 받아오면 풀어주기.
        textView_name.setText("현재 테스터1 님이 계신 곳이");
        longAverage = new Long(0);

//        progressBar.getProgressDrawable().setColorFilter(                         //progressBar 색깔 바꾸기
//                Color.YELLOW, PorterDuff.Mode.SRC_IN);

//        progressBar.getProgressDrawable().setColorFilter(                         //progressBar 색깔 바꾸기
//                getResources().getColor(R.color.colorPrimary), PorterDuff.Mode.SRC_IN);

        extra = new Bundle();
        extra = getArguments();
        fragment_name = new String();
        fragment_name = extra.getString("fragment_name");

        button_ok.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (longAverage <= 0 || longAverage >= THRESHOLD) {
                    Log.d("test", "noise xxxx");
                    ProgressThread progressThread = new ProgressThread();
                    progressThread.start();
                } else {
                    if (fragment_name.equals("SoundTestFragment.class")) {
                        Log.d("test", "noise ok");
                        startFragment(getFragmentManager(), SoundTestFragment.class);
                    } else if (fragment_name.equals("Consonant_VowelFragment.class")) {
                        startFragment(getFragmentManager(), Consonant_VowelFragment.class);
                    }
                    if (fragment_name.equals("FinalConsonantFragment.class")) {
                        startFragment(getFragmentManager(), FinalConsonantFragment.class);
                    }
                    if (fragment_name.equals("SayingwordsFragment.class")) {
                        startFragment(getFragmentManager(), SayingwordsFragment.class);
                    }
                    if (fragment_name.equals("SayingsentenceFragment.class")) {
                        startFragment(getFragmentManager(), SayingsentenceFragment.class);
                    }
                }


            }
        });
        return rootView;
    }

    class ProgressThread extends Thread {


        public void run() {
            double sum = 0;
            double dB = 0;
            buttonSetting(false);  //이 부분에 버튼 비활성화 코드 넣어야함.

            final SoundMeter sm = new SoundMeter();
            sm.start();

            for (int i = 0; i < 100; i++) {

                progressbarSetting(i);

                try {
                    dB = 20 * Math.log10(sm.getAmplitude());
                    if(i!=0) {
                        sum = sum + dB;
                        Log.d("dB:", "#" + i + ": " + dB);
                        Thread.sleep(30);                       //3초간 측정. 30
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            sm.stop();
            longAverage = Math.round(sum / 99);

            buttonSetting(true);  //이 부분에 버튼 활성화 코드 넣어야 함.

        }
        private void progressbarSetting(final int i) {
            handler.post(new Runnable() {
                @Override
                public void run() {
                    progressBar.setProgress(i);
                }
            });
        }
        private void buttonSetting(final boolean act) {
            handler.post(new Runnable() {
                @Override
                public void run() {
                    button_ok.setEnabled(act);
                    if (act == true)
                        textView3.setText(longAverage.toString());

                    if (longAverage >= THRESHOLD) {                                //나중에 이부분 적절히 수정하자.
                        button_ok.setBackgroundResource(R.drawable.radius2);
                        // button_ok.setBackgroundColor(Color.parseColor("#80BE1E2D"));
                        button_ok.setText("다시시도");
                    } else
                    {
                        button_ok.setBackgroundResource(R.drawable.radius3);
                        // button_ok.setBackgroundColor(Color.parseColor("#801EBDC9"));
                        button_ok.setText("확인");
                    }
                }
            });
        }

    }

}