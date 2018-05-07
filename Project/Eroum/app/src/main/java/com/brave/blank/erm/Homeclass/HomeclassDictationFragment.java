package com.brave.blank.erm.Homeclass;

import android.os.Bundle;
import android.support.v4.app.FragmentTransaction;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.brave.blank.erm.AssembledData;
import com.brave.blank.erm.BackKeyController;
import com.brave.blank.erm.BaseFragment;
import com.brave.blank.erm.ContentActivity;
import com.brave.blank.erm.DeveloperKey;
import com.brave.blank.erm.Dictation.DictationFragment;
import com.brave.blank.erm.Network.ApplicationController;
import com.brave.blank.erm.Network.NetworkService;
import com.brave.blank.erm.Network.Request.SubmitWriting;
import com.brave.blank.erm.Network.Response.Homework;
import com.brave.blank.erm.Network.Response.Writing;
import com.brave.blank.erm.Network.Token;
import com.brave.blank.erm.R;
import com.google.android.youtube.player.YouTubeInitializationResult;
import com.google.android.youtube.player.YouTubePlayer;
import com.google.android.youtube.player.YouTubePlayerSupportFragment;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

/**
 * Created by chanung on 2016-08-06.
 */

//homework_id 랑 question 받아와야함.
public class HomeclassDictationFragment extends BaseFragment {
    ContentActivity activity;
    Button btnSubmit;
    EditText editText;
    TextView dateText;
    TextView teacherText;

    SimpleDateFormat format;
    private String videoId;
    YouTubePlayerSupportFragment youTubePlayerFragment;
    YouTubePlayer.OnInitializedListener onInitializedListener;
    YouTubePlayer youTubePlayer;
    PlayThread playThread;
    boolean isEnded=false;
    boolean changeToImage=false;
    private int count;
    private  float answerRate;
    String question;
    String answer;
    List<Homework> homeworkny_dic = null;
    Homework dic_detail;
    DictationFragment dictationFragment;
    private int notyetNum;


    private NetworkService networkService;
    private void initNetworkService(){
        // TODO: 13. ApplicationController 객체를 이용하여 NetworkService 가져오기
        networkService = ApplicationController.getInstance().getNetworkService();
    }

    Bundle extra;
    int id;

    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        ViewGroup rootView = (ViewGroup) inflater.inflate(R.layout.fragment_homeclass_dictation, container, false);
        initNetworkService();
        BackKeyController.setIsHomeclassPractice(true);

        format=new SimpleDateFormat("yyyy.MM.dd");
        dictationFragment=new DictationFragment();
        dic_detail = new Homework();
        count=0;
        extra = new Bundle();
        extra = getArguments();
        id=extra.getInt("homework_id");

        homeworkny_dic = AssembledData.getHomeworkNotyet();

        for(int i=0;i<homeworkny_dic.size();i++){
            if(id==homeworkny_dic.get(i).getHomework_id()){
                dic_detail = homeworkny_dic.get(i);
                notyetNum=i;
            }
        }
        btnSubmit=(Button)rootView.findViewById(R.id.btnSubmit);
        editText =(EditText)rootView.findViewById(R.id.editText);               //정답 입력
        dateText =(TextView)rootView.findViewById(R.id.dictation_date);
        teacherText = (TextView)rootView.findViewById(R.id.d_teacher_id);

        dateText.setText(format.format(dic_detail.getStart_date()));
        teacherText.setText(AssembledData.getIdentify().getTeacher());
        question=dic_detail.getQuestion();  // url에 대한 답 입력시켜 놓음                                                    //다른프래그먼트로부터 정보 받아와야 함.
        question=question.replace(" ","");
        question=question.substring(0, question.length() - 1);

        activity= (ContentActivity) getActivity();
        videoId=dic_detail.getUrl();                             //비디오아이디 입력설정완료

        onInitializedListener= new YouTubePlayer.OnInitializedListener() {
            @Override
            public void onInitializationSuccess(YouTubePlayer.Provider provider,
                                                YouTubePlayer player, boolean wasRestored) {
                if (!wasRestored) {
                    player.cueVideo(videoId);                     //String 변수로 바꾸자.
                    player.cueVideo(videoId);                     //String 변수로 바꾸자.

                    youTubePlayer=player;
                    //  player.loadVideo(videoId);                              //스레드 생성하자.
                    // player.play();
                    youTubePlayer.setPlayerStateChangeListener(new YouTubePlayer.PlayerStateChangeListener() {
                        @Override
                        public void onLoading() {

                        }

                        @Override
                        public void onLoaded(String s) {

                        }

                        @Override
                        public void onAdStarted() {

                        }

                        @Override
                        public void onVideoStarted() {
                            isEnded=false;
                            playThread=new PlayThread();
                            playThread.start();     //비디오 시작될때 스레드 start
                        }



                        @Override
                        public void onVideoEnded() {
                            isEnded=true;                       //비디오 끝나면 스레드 종료
                            count++;
                        }

                        @Override
                        public void onError(YouTubePlayer.ErrorReason errorReason) {

                        }
                    });
                    //   playThread=new PlayThread();
                    //  playThread.start();
                }
            }

            @Override
            public void onInitializationFailure(YouTubePlayer.Provider provider, YouTubeInitializationResult youTubeInitializationResult) {

            }
        };
        youTubePlayerFragment = YouTubePlayerSupportFragment.newInstance();
        youTubePlayerFragment.initialize(DeveloperKey.DEVELOPER_KEY, onInitializedListener);

        FragmentTransaction transaction = getChildFragmentManager().beginTransaction();
        transaction.add(R.id.youtube_view, youTubePlayerFragment).commit();

        btnSubmit.setOnClickListener(new View.OnClickListener() {                             //제출하는 코드 추가.
            @Override
            public void onClick(View v) {
                setAnswerRate();
                networkSubmitWriting();                                                          //id 받아오면 주석 풀어주기.

                //////////////////////////////////////////////
            }
        });

        return rootView;
    }

    public void networkSubmitWriting(){
        SubmitWriting submitWriting=new SubmitWriting();
        submitWriting.setType(true);
        submitWriting.setHomework_id(dic_detail.getHomework_id());                                //id받아와야함.
        submitWriting.setRate((int) answerRate);
        submitWriting.setPlay_count(count);
        submitWriting.setAnswer(answer);

        Call<Void> voidCall=networkService.submitWriting(Token.getToken(), submitWriting);
        voidCall.enqueue(new Callback<Void>() {
            @Override
            public void onResponse(Call<Void> call, Response<Void> response) {
                int statusCode = response.code();
                if (response.isSuccessful()) {
                    Log.d("MyTag", "성공! submit 응답코드 : : " + statusCode);

                    btnSubmit.setEnabled(false);
                    Writing writing=new Writing();
                    writing.setId(id);
                    writing.setQuestion(dic_detail.getQuestion());
                    writing.setStart_date(dic_detail.getStart_date());
                    //writing.setStart_date(dic_detail.getEnd_date());
                    Date date=new Date();
                    writing.setEnd_date(date);
                    writing.setRate((int) answerRate);
                    writing.setPlay_count(count);
                    writing.setAnswer(answer);

                    dic_detail.setEnd_date(date);
                    AssembledData.getWritingArrayList().add(writing);                 //완료된 받아쓰기 과제 배열에 추가
                    AssembledData.getHomeworkdone().add(dic_detail);                //완료된 과제 배열에 추가
                    AssembledData.getHomeworkNotyet().remove(notyetNum);                      //미완료된 과제 배열에 삭제

                   // refreshData();

                    Bundle bundle=new Bundle();
                    bundle.putInt("homework_id", id);
                    dictationFragment.setArguments(bundle);
                    // startFragment(getFragmentManager(),DictationFragment.class);
                    getFragmentManager().beginTransaction().replace(R.id.container,dictationFragment).addToBackStack(null).commit();
                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
                } else {
                    Log.d("MyTag", "submit 응답코드 : " + statusCode);
                }
            }

            @Override
            public void onFailure(Call<Void> call, Throwable t) {
                Log.d("MyTag", "submit 에러내용 : " + t.getMessage());
            }
        });
    }

    public void setAnswerRate(){
        answer=editText.getText().toString();
        answer=answer.replace(" ", "");
        float answerCharNum=0;
        int i=0;
        int endLength= question.length()<answer.length() ?  question.length():answer.length();
        while(i<endLength){
            if(question.charAt(i)==answer.charAt(i)){
                answerCharNum++;
            }
            i++;
        }
        answerRate=answerCharNum/question.length()*100;
        Log.d("answerRate", "" + answerRate);
    }

//    private void refreshData(){
//        ArrayList<HomeclassList> itemDatas= HomeclassFragment.getItemDatas();
//        HomeclassList item = new HomeclassList();
//        Log.d("refresh", "itemDatas.size() 1 : " + itemDatas.size());
//        item.setId(dic_detail.getId());
//        item.setButtonText(false);
//        item.setDate(format.format(dic_detail.getStart_date()));
//        // item.setDate(homeworksnotyet.get(i).getStart_date().toString());
//        item.setSection(dic_detail.getType());
//        item.setQuestion(dic_detail.getQuestion());
//        itemDatas.add(item);
//
//        Log.d("refresh", "itemDatas.size() 2 : " + itemDatas.size());
//
//        HomeclassFragment.refreshAdapter();
//    }

    class PlayThread extends Thread{
        public void run(){
            boolean check=false;

            while(!isEnded){                          //다시 재시작 할때는 isEnded를 false로 만들어 주어야 함. 위의 콜백함수 이용
                if(changeToImage ==true){
                    break;
                }

                if(changeToImage ==false && youTubePlayer.isPlaying()==true && check==true){             //재생중
                    continue;
                }
                else if(changeToImage ==false && youTubePlayer.isPlaying()==false && check==true){           //재생중이다가 멈췄을때.
                    check=false;
                }
                else if(changeToImage ==false && youTubePlayer.isPlaying()==true && check==false){           //중지됐다가 다시 재생할때.
                    count++;
                    check=true;
                    Log.d("PlayCount", " " + count);
                }
                else{
                    continue;
                }
            }
        }
    }

}