package com.brave.blank.erm.Homeclass;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.brave.blank.erm.AssembledData;
import com.brave.blank.erm.BackKeyController;
import com.brave.blank.erm.BaseFragment;
import com.brave.blank.erm.ContentActivity;
import com.brave.blank.erm.Network.ApplicationController;
import com.brave.blank.erm.Network.NetworkService;
import com.brave.blank.erm.Network.Request.SubmitSpeaking;
import com.brave.blank.erm.Network.Response.Homework;
import com.brave.blank.erm.Network.Response.Speaking;
import com.brave.blank.erm.Network.Token;
import com.brave.blank.erm.Pronunciation.PronunciationFragment;
import com.brave.blank.erm.R;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

/**
 * Created by chanung on 2016-08-06.
 */
//다른 프레그먼트로 넘어가거나 할때 correctNum=0 해줘야함. 왜냐하면 static이니깐.
//imageView들이 static 이므로 다른 과제를 하러 갈때에 이미지를 모두 초기화 해줘야함.
//다른 프레그먼트에서 정보를 받아서 뿌려주어야함.
public class HomeclassSpeakingFragment extends BaseFragment {
    Button btn_record;
    static Button btn_submit;
    static ImageView imageView,imageView2,imageView3,imageView4,imageView5,imageView6,imageView7,imageView8,imageView9,imageView10;
    static TextView textView_input;
    TextView textView_question;
    TextView speaking_date;
    TextView s_teacher_id;
    PronunciationFragment pronunciationFragment;
    SimpleDateFormat format;
    private int notyetNum;
    ContentActivity activity;
    static String question;
    static String answer;
    static int correctNum;
    static int challengeNum;


    private NetworkService networkService;
    private void initNetworkService(){
        // TODO: 13. ApplicationController 객체를 이용하여 NetworkService 가져오기
        networkService = ApplicationController.getInstance().getNetworkService();
    }

    List<Homework> homeworksny_spk = null;
    Homework spk_detail = null;

    Bundle extra;
    int id;

    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        ViewGroup rootView = (ViewGroup) inflater.inflate(R.layout.fragment_homeclass_speaking, container, false);
        initNetworkService();
        init(rootView);
        BackKeyController.setIsHomeclassPractice(true);
        activity=(ContentActivity) getActivity();
        pronunciationFragment=new PronunciationFragment();
        spk_detail = new Homework();
        correctNum=0;
        challengeNum=0;
        extra = new Bundle();
        extra = getArguments();
        id=extra.getInt("homework_id");
        format=new SimpleDateFormat("yyyy.MM.dd");
        homeworksny_spk = AssembledData.getHomeworkNotyet();

        for(int i=0;i<homeworksny_spk.size();i++){
            if(id == homeworksny_spk.get(i).getHomework_id()){
                spk_detail = homeworksny_spk.get(i);
                notyetNum=i;
            }
        }

        speaking_date.setText(format.format(spk_detail.getStart_date()));
        s_teacher_id.setText(AssembledData.getIdentify().getTeacher());
        textView_question.setText(spk_detail.getQuestion());
        question=textView_question.getText().toString();
        question=question.replace(" ","");
        question=question.substring(0, question.length());
        /////////////////////////////////////////////// 글자 비교하는 코드 넣어줘야 함.
        btn_record.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                activity.startRecord(1);
                challengeNum++;
                //setAnswer();
                Log.d("btnRecord", " btn_record 실행됨.");

            }
        });

        btn_submit.setOnClickListener(new View.OnClickListener() {                     //제출하는 코드 집어넣기.
            @Override
            public void onClick(View v) {
                networkSubmitSpeaking();                                          //id받아오면 주석 풀기.

                ///////////////////////////////////////////////////////
            }
        });



        return rootView;
    }

    public static void setAnswer(){                                //녹음 부분이 쓰레드처럼 동작하므로 녹음이 끝난후 메서드 실행.
        answer=textView_input.getText().toString();
        answer=answer.replace(" ", "");
        Log.d("HomeclassSpeaking", "answer: "+answer);
        Log.d("HomeclassSpeaking", "question: "+question);
        if(question.equals(answer)){
            correctNum++;
            Log.d("HomeclassSpeaking","correctNum: "+correctNum);
            //   imageView.setImageResource();
            switch (correctNum){
                case 1:
                    imageView.setImageResource(R.drawable.ic_1_1);
                    break;
                case 2:
                    imageView2.setImageResource(R.drawable.ic_2_1);
                    break;
                case 3:
                    imageView3.setImageResource(R.drawable.ic_3_1);
                    break;
                case 4:
                    imageView4.setImageResource(R.drawable.ic_4_1);
                    break;
                case 5:
                    imageView5.setImageResource(R.drawable.ic_5_1);
                    break;
                case 6:
                    imageView6.setImageResource(R.drawable.ic_6_1);
                    break;
                case 7:
                    imageView7.setImageResource(R.drawable.ic_7_1);
                    break;
                case 8:
                    imageView8.setImageResource(R.drawable.ic_8_1);
                    break;
                case 9:
                    imageView9.setImageResource(R.drawable.ic_9_1);
                    break;
                case 10:
                    imageView10.setImageResource(R.drawable.ic_10_1);
                    break;
            }

        }

        if(challengeNum >= 10 || correctNum >= 1){
            Log.d("btnRecord","if문 실행됨.");
            Log.d("btnRecord",""+challengeNum);
            Log.d("btnRecord",""+correctNum);
            btn_submit.setEnabled(true);
        }

    }

    public void getRecordText(String text){
        textView_input.setText(text);
    }

    public void init(ViewGroup rootView){
        speaking_date = (TextView)rootView.findViewById(R.id.speaking_date);
        s_teacher_id = (TextView)rootView.findViewById(R.id.s_teacher_id) ;
        btn_record=(Button)rootView.findViewById(R.id.btn_record);
        btn_submit=(Button)rootView.findViewById(R.id.btn_sumbit);
        btn_submit.setEnabled(false);
        textView_input=(TextView)rootView.findViewById(R.id.textView_input);
        textView_question=(TextView)rootView.findViewById(R.id.textView_question);
        imageView=(ImageView)rootView.findViewById(R.id.imageView);
        imageView2=(ImageView)rootView.findViewById(R.id.imageView2);
        imageView3=(ImageView)rootView.findViewById(R.id.imageView3);
        imageView4=(ImageView)rootView.findViewById(R.id.imageView4);
        imageView5=(ImageView)rootView.findViewById(R.id.imageView5);
        imageView6=(ImageView)rootView.findViewById(R.id.imageView6);
        imageView7=(ImageView)rootView.findViewById(R.id.imageView7);
        imageView8=(ImageView)rootView.findViewById(R.id.imageView8);
        imageView9=(ImageView)rootView.findViewById(R.id.imageView9);
        imageView10=(ImageView)rootView.findViewById(R.id.imageView10);
    }

    public void networkSubmitSpeaking(){
        SubmitSpeaking submitSpeaking=new SubmitSpeaking();                 //type true SubmitWriting , false SubmitSpeaking 이렇게 알려줬지만 그 반대로 해야함.
        submitSpeaking.setType(false);                                            //이게 동작을 안하고 있음.
        submitSpeaking.setHomework_id(spk_detail.getHomework_id());
        submitSpeaking.setSuccess_count(correctNum);
        submitSpeaking.setChallenge_count(challengeNum);
        Call<Void> voidCall=networkService.submitSpeaking(Token.getToken(), submitSpeaking);
        voidCall.enqueue(new Callback<Void>() {
            @Override
            public void onResponse(Call<Void> call, Response<Void> response) {
                int statusCode = response.code();
                if(response.isSuccessful()){
                    Log.d("MyTag", "성공! SubmitSpeaking 응답코드 : : " + statusCode);

                    Speaking speaking=new Speaking();
                    speaking.setId(id);
                    speaking.setQuestion(spk_detail.getQuestion());
                    speaking.setStart_date(spk_detail.getStart_date());
                    //writing.setEnd_date(dic_detail.getEnd_date());
                    Date date=new Date();
                    speaking.setEnd_date(date);
                    speaking.setSuccess_count(correctNum);
                    speaking.setChallenge_count(challengeNum);

                    spk_detail.setEnd_date(date);
                    AssembledData.getSpeakingArrayList().add(speaking);    //완료된 받아쓰기 과제 배열에 추가
                    AssembledData.getHomeworkdone().add(spk_detail);                //완료된 과제 배열에 추가
                    AssembledData.getHomeworkNotyet().remove(notyetNum);                      //미완료된 과제 배열에 삭제


                    Bundle bundle=new Bundle();
                    bundle.putInt("homework_id", id);
                    pronunciationFragment.setArguments(bundle);
                    // startFragment(getFragmentManager(),DictationFragment.class);
                    getFragmentManager().beginTransaction().replace(R.id.container, pronunciationFragment).addToBackStack(null).commit();
                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
                }
                else{

                    Log.d("MyTag", "SubmitSpeaking 응답코드 : " + statusCode);
                }
            }

            @Override
            public void onFailure(Call<Void> call, Throwable t) {
                Log.d("MyTag","SubmitSpeaking 에러내용 : " + t.getMessage());
            }
        });
    }
}