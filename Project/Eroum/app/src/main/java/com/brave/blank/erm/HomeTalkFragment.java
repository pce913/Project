package com.brave.blank.erm;

import android.os.Bundle;
import android.support.v4.app.FragmentTransaction;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.TextView;

import com.brave.blank.erm.Consonant_Vowel.CSdata;
import com.brave.blank.erm.Network.ApplicationController;
import com.brave.blank.erm.Network.NetworkService;
import com.brave.blank.erm.Network.Request.ItemId;
import com.brave.blank.erm.Network.Response.StudyInfo;
import com.brave.blank.erm.Network.Token;
import com.google.android.youtube.player.YouTubeInitializationResult;
import com.google.android.youtube.player.YouTubePlayer;
import com.google.android.youtube.player.YouTubePlayerSupportFragment;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

/**
 * Created by chanung on 2016-07-26.
 */

public class HomeTalkFragment extends BaseFragment{
    ImageButton btn_save;
    ImageButton btn_complete;
    ContentActivity activity;
    private String videoId;
    private TextView textView;
    private TextView textView_practivewords;
    private Button btnRecord;
    private Button btnNext;
    private Button btnImage;
    private Button btnVideo;
    FrameLayout frameLayout;
    ImageFragment imageFragment;
    int mode;
    int type;
    int random;                   //단어, 문장에서 랜덤하게 뿌려주기 위한 변수
    boolean isLearned;
    boolean isSaved;
    int wordsCount;

    ArrayList<CSdata> showingWords;

    List<StudyInfo> learnedInfos;
    List<StudyInfo> savedInfos;

    YouTubePlayerSupportFragment youTubePlayerFragment;
    YouTubePlayer.OnInitializedListener onInitializedListener;

    // ConsonantVowelFragment로부터 각각 그리드뷰에 할당되는 정보를 네트워킹에 받아서 현재fragment에 넘길때 넘어오는 정보를 받기위한 변수
    Bundle extra_cv;
    ArrayList<CSdata> content_item_cv;
    private static final int COMPLETE_IMAGE=R.drawable.ic_check_2;

    private NetworkService networkService;
    private void initNetworkService(){
        // TODO: 13. ApplicationController 객체를 이용하여 NetworkService 가져오기
        networkService = ApplicationController.getInstance().getNetworkService();
    }
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        ViewGroup rootView = (ViewGroup) inflater.inflate(R.layout.fragment_home_talk, container, false);
        init(rootView);
        initNetworkService();

        learnedInfos=AssembledData.getLearnedInfos();                    //학습한 정보 가져오기
        savedInfos=AssembledData.getSavedInfos();                       //저장한 정보 가져오기
        wordsCount=0;
        btn_save.setImageResource(R.drawable.ic_heart_1);
        btn_complete.setImageResource(R.drawable.ic_check_1);
        activity = (ContentActivity)getActivity();

        content_item_cv = new ArrayList<CSdata>();
        content_item_cv = (ArrayList<CSdata>)getArguments().get("content_item");
        imageFragment=new ImageFragment();
        imageFragment.getImageUrl(content_item_cv.get(0).getImg_url());


        setMode(content_item_cv.get(0).getMode());                                      //Mode별로 View가 다르게 보여진다.
        setListener();

        if(type==4 || type==5){
            makeRandomSequence();                  //단어 및 문장일때에 랜덤한 배열을 만들어줌.
            checkSaveAndComplete(showingWords,1);              //학습 및 저장 완료여부 체크
            textView_practivewords.setText(showingWords.get(0).getData());
            videoId=showingWords.get(0).geturl();
        }           //개별 단어 및 문장일때는 랜덤한 값으로 시작
        else{
            checkSaveAndComplete(content_item_cv,0);             //학습 및 저장 완료여부 체크
            textView_practivewords.setText(content_item_cv.get(0).getData());            //이곳에서 출력
            videoId= content_item_cv.get(0).geturl();         // videoUrl 준비되면 이걸로 바꾸기
        }

/////////////////////////////////////////////////////////////
        // 유튜브 플레이어 셋팅 부분
        onInitializedListener= new YouTubePlayer.OnInitializedListener() {
            @Override
            public void onInitializationSuccess(YouTubePlayer.Provider provider,
                                                final YouTubePlayer player, boolean wasRestored) {
                if (!wasRestored)
                    player.cueVideo(videoId);
            }
            @Override
            public void onInitializationFailure(YouTubePlayer.Provider provider, YouTubeInitializationResult youTubeInitializationResult) {}
        };
        youTubePlayerFragment = YouTubePlayerSupportFragment.newInstance();
        youTubePlayerFragment.initialize(DeveloperKey.DEVELOPER_KEY, onInitializedListener);

        FragmentTransaction transaction = getChildFragmentManager().beginTransaction();
        transaction.add(R.id.youtube_view, youTubePlayerFragment).commit();
////////////////////////////////////////////////////////////
        return rootView;
    }

    private void setListener(){
        btnNext.setOnClickListener(new View.OnClickListener() {            //다음문장으로 이동
            @Override
            public void onClick(View v) {                                   // 다음단어, 다음이미지,VedioId,저장하기 여부, 학습완료 여부를 다시 셋팅한다.
                setBtnNext();
            }
        });
        btn_save.setOnClickListener(new View.OnClickListener() {             //이미지 전환 코드 넣기
            @Override
            public void onClick(View v) {
                if(!isSaved){              //저장 안되었을때 저장으로 버튼 바꾸는 부분
                    Log.d("networkSave", "isSaved 동작 동작");
                    btn_save.setImageResource(R.drawable.ic_heart_2);
                    networkSave(0);                //0 이면 저장하기
                    StudyInfo addInfo=new StudyInfo();
                    addInfo.setType(type);
                    addInfo.setDate(new Date());
                    if(type==1 || type==2 || type==3){
                        addInfo.setId(content_item_cv.get(0).getId());
                        addInfo.setData(content_item_cv.get(0).getData());
                    }
                    else{                                     //단어, 문장일 경우
                        addInfo.setId(showingWords.get(wordsCount).getId());
                        addInfo.setData(showingWords.get(wordsCount).getData());
                    }
                    AssembledData.getSavedInfos().add(addInfo);
                    isSaved=true;
                }
                else{                 // 저장 되어있을때 저장 안됨으로 버튼 바꾸는 부분
                    Log.d("networkSave","isSaved 동작 동작");
                    btn_save.setImageResource(R.drawable.ic_heart_1);
                    networkSave(2);                   //2이면 저장취소
                    int item_id;
                    if(type==1 || type==2 || type==3)
                        item_id=content_item_cv.get(0).getId();
                    else                            //단어, 문장일 경우
                        item_id=showingWords.get(wordsCount).getId();

                    for(int i=0;i<savedInfos.size();i++){
                        if(AssembledData.getSavedInfos().get(i).getId()==item_id){
                            AssembledData.getSavedInfos().remove(i);
                        }
                    }
                    isSaved=false;
                }
            }
        });

        btn_complete.setOnClickListener(new View.OnClickListener() {             //완료되었을때 체크표시되는것.
            @Override
            public void onClick(View v) {
                if(!isLearned){              //학습 안되었을때 학습으로 버튼 바꾸는 부분
                    Log.d("networkSave", "!isLearned 동작");
                    btn_complete.setImageResource(COMPLETE_IMAGE);
                    networkSave(1);             //1이면 학습완료
                    StudyInfo addInfo=new StudyInfo();
                    addInfo.setType(type);
                    addInfo.setDate(new Date());
                    if(type==1 || type==2 || type==3){
                        addInfo.setId(content_item_cv.get(0).getId());
                        addInfo.setData(content_item_cv.get(0).getData());
                    }
                    else{                                     //단어, 문장일 경우
                        addInfo.setId(showingWords.get(wordsCount).getId());
                        addInfo.setData(showingWords.get(wordsCount).getData());
                    }
                    AssembledData.getLearnedInfos().add(addInfo);
                    isLearned=true;
                }
                else{                 // 학습 되어있을때 학습 안됨으로 버튼 바꾸는 부분

                    // 여기도 단어, 문장일때와 다른 경우를 구분해줘야한다.
                    Log.d("networkSave","isLearned 동작 동작");
                    btn_complete.setImageResource(R.drawable.ic_check_1);
                    networkSave(3);            //3이면 학습취소
                    int item_id;
                    if(type==1 || type==2 || type==3)
                        item_id=content_item_cv.get(0).getId();
                    else                            //단어, 문장일 경우
                        item_id=showingWords.get(wordsCount).getId();

                    for(int i=0;i<learnedInfos.size();i++) {
                        if(AssembledData.getLearnedInfos().get(i).getId()==item_id){
                            AssembledData.getLearnedInfos().remove(i);
                        }
                    }
                    isLearned=false;
                }
            }
        });

        btnRecord.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                activity.startRecord(0);
            }
        });

        btnImage.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentTransaction transaction = getChildFragmentManager().beginTransaction();
                transaction.replace(R.id.youtube_view,imageFragment).commit();
            }
        });

        btnVideo.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                youTubePlayerFragment.initialize(DeveloperKey.DEVELOPER_KEY, onInitializedListener);
                FragmentTransaction transaction = getChildFragmentManager().beginTransaction();
                transaction.replace(R.id.youtube_view, youTubePlayerFragment).commit();
            }
        });
    }

    public void setMode(int mode){                           //setView  HomeTalkFragment가 나타날때마다 설정해줘야함.
        this.mode=mode;
        if(mode==0){                                 // 개별 자음 말하기
            type=1;
            btnNext.setVisibility(View.GONE);
        }
        else if(mode==1){                                 // 개별 모음 말하기
            type=2;
            btnNext.setVisibility(View.GONE);
        }
        else if(mode==2){                          //개별 받침_설명
            type=3;
            btn_complete.setVisibility(View.VISIBLE);
            btn_save.setVisibility(View.VISIBLE);
            btnImage.setVisibility(View.VISIBLE);
            textView.setVisibility(View.INVISIBLE);
            btnRecord.setVisibility(View.INVISIBLE);
            btnNext.setText("연습 해보기");
        }
        else if(mode==3){                       //개별 받침_해보기
            type=3;
            btnImage.setVisibility(View.GONE);
            btn_save.setVisibility(View.GONE);
            btn_complete.setVisibility(View.GONE);
            btnNext.setText("설명 보기");

        }
        else if(mode ==4){                      //개별 문장 말하기
            Log.d("checkbutton","mode4 ");
            type=4;
            btnImage.setVisibility(View.GONE);
            btnNext.setText("다음문장");
            textView.setText("");
            Log.d("checkbutton", btnNext.getText().toString());
        }
        else{
            Log.d("checkbutton","mode5");
            type=5;//개별 단어 말하기
            btnImage.setVisibility(View.GONE);
            btnNext.setText("다음단어");
            textView.setText("");
            Log.d("checkbutton", btnNext.getText().toString());
        }
    }

    private void networkSave(final int what){                   //what ==0 이면 저장하기 , what ==1 이면 학습완료
        Log.d("networkSave","networkSave 동작");
        ItemId itemId=new ItemId();

        if(type==4 || type == 5)
            itemId.setItem_id(showingWords.get(wordsCount).getId());
        else
            itemId.setItem_id(content_item_cv.get(0).getId());

        Call<Void> voidCall;
        if(what==0)                                          //0 일때 저장 완료
            voidCall=networkService.saveSave(Token.getToken(), itemId);
        else if(what==1)                           //1일때 학습 완료
            voidCall=networkService.saveLearn(Token.getToken(), itemId);
        else if(what==2) {              //2일때 저장 취소
            voidCall=networkService.deleteSave(Token.getToken(),itemId.getItem_id());                 ///////////
            Log.d("networkSave", "2 동작");
        }
        else    {                //3일때 학습 취소
            voidCall=networkService.deleteLearn(Token.getToken(),itemId.getItem_id());               ///////////////
            Log.d("networkSave","3 동작");
        }
        voidCall.enqueue(new Callback<Void>() {
            @Override
            public void onResponse(Call<Void> call, Response<Void> response) {
                int statusCode = response.code();
                if(response.isSuccessful()){
                    if(what==0)
                        Log.d("MyTag", "성공! 저장하기 응답코드 : : " + statusCode);
                    else {
                        Log.d("MyTag", "성공! 학습완료 응답코드 : : " + statusCode);
                    }
                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
                }
                else{
                    Log.d("MyTag", "응답코드 : " + statusCode);
                }
            }
            @Override
            public void onFailure(Call<Void> call, Throwable t) {
                Log.d("MyTag","에러내용 : " + t.getMessage());
            }
        });
    }

    public void setBtnNext(){
        Log.d("setBtnNext","setBtnNext 호출됨");
        textView.setText("");
        if(mode==2){                //2 개별받침_설명에서
            setMode(3);               // 3 개별받침_해보기로 모드를 전환한다.
            textView_practivewords.setText(content_item_cv.get(1).getData());                    //해보기에 대한 글자를 넣어준다.
            videoId=content_item_cv.get(1).geturl();                //개별 받침_해보기에 해당하는 videoId값.
        }
        else if(mode==3){                            //3 개별받침_해보기 에서
            setMode(2);                            //2 개별받침_설명으로 전환한다
            textView_practivewords.setText(content_item_cv.get(0).getData());
            videoId=content_item_cv.get(0).geturl();                 //개별 받침_설명에 해당하는 videoId값.
        }
        else{                         //3 개별단어및문장 에서 next버튼을 누를때는 모드 변환이 없다.
            wordsCount++;
            if(wordsCount>=showingWords.size()){
                wordsCount=0;
            }

            checkSaveAndComplete(showingWords,1);

            Log.d("wordsCount ", ""+wordsCount);
            textView_practivewords.setText(showingWords.get(wordsCount).getData());     //해당하는 주제의 단어들의 data를 넣어준다.
            videoId=showingWords.get(wordsCount).geturl();
        }
        onInitializedListener= new YouTubePlayer.OnInitializedListener() {
            @Override
            public void onInitializationSuccess(YouTubePlayer.Provider provider,
                                                final YouTubePlayer player, boolean wasRestored) {
                if (!wasRestored)
                    player.cueVideo(videoId);
            }
            @Override
            public void onInitializationFailure(YouTubePlayer.Provider provider, YouTubeInitializationResult youTubeInitializationResult) {}
        };
        youTubePlayerFragment = YouTubePlayerSupportFragment.newInstance();
        youTubePlayerFragment.initialize(DeveloperKey.DEVELOPER_KEY, onInitializedListener);

        FragmentTransaction transaction = getChildFragmentManager().beginTransaction();
        transaction.replace(R.id.youtube_view, youTubePlayerFragment).addToBackStack(null).commit();
    }

    private void makeRandomSequence(){                                  //랜덤 배열을 만들어주는 함수.
        Log.d("makeRandom","makeRandomSequence() 들어옴");
        ArrayList<StudyInfo> learnedWordsOrSentences;
        if(type==4)
            learnedWordsOrSentences = AssembledData.getLearnedWords();
        else
            learnedWordsOrSentences = AssembledData.getLearnedSentences();

        ArrayList<CSdata> learnedAsTopic=new ArrayList<CSdata>();
        ArrayList<CSdata> notLearnedAsTopic=new ArrayList<CSdata>();
        showingWords=new ArrayList<CSdata>();
        Log.d("makeRandom", "learnedWordsOrSentences.size() : "+learnedWordsOrSentences.size());

        boolean checkLearned;
        Log.d("makeRandom", "content_item_cv.size() : "+content_item_cv.size());
        for(int i=0;i<content_item_cv.size();i++){
            checkLearned=false;
            Log.d("makeRandom","for문 안으로 들어옴");
            for(int j=0;j<learnedWordsOrSentences.size();j++){
                if(content_item_cv.get(i).getId()==learnedWordsOrSentences.get(j).getId()) {
                    learnedAsTopic.add(content_item_cv.get(i));
                    Log.d("makeRandom", content_item_cv.get(i).getData());
                    checkLearned=true;
                    break;
                }
            }
            if(checkLearned==false){
                notLearnedAsTopic.add(content_item_cv.get(i));
                Log.d("makeRandom", content_item_cv.get(i).getData());
            }
        }

        int random_notLearned;
        int random_learned;
        while(notLearnedAsTopic.size()!=0){
            Log.d("makeRandom","while notLearnedAsTopic 들어옴");
            random_notLearned=(int)(Math.random()*notLearnedAsTopic.size()-1 + 0);
            showingWords.add(notLearnedAsTopic.get(random_notLearned));
            notLearnedAsTopic.remove(random_notLearned);
        }
        while(learnedAsTopic.size()!=0){                              //사이즈가 0이 되지 않았다면
            Log.d("makeRandom","while learnedAsTopic 들어옴");
            random_learned=(int)(Math.random()*learnedAsTopic.size()-1 + 0);               //그 0부터 사이즈까지의 랜덤 값을 하나 만든다.
            showingWords.add(learnedAsTopic.get(random_learned));                 //새로만든 배열에 랜덤으로 뽑힌 부분을 집어넣고
            learnedAsTopic.remove(random_learned);                              // 기존에 만든 배열에서 랜덤한 부분은 삭제한다.
        }
    }

    private void checkSaveAndComplete(ArrayList<CSdata> csdatas,int what){
        isLearned=false;
        isSaved=false;
        int index;
        index = (what==0) ? 0 : wordsCount;
        Log.d("csdatas","csdatas.size : "+csdatas.size());
        for(int i=0;i<learnedInfos.size();i++){                                 //학습을 했던 단어인지 아닌지 체크.
            if(learnedInfos.get(i).getId()==csdatas.get(index).getId()){
                isLearned=true;
                break;
            }
        }
        if(isLearned==true)
            btn_complete.setImageResource(R.drawable.ic_check_2);
        else
            btn_complete.setImageResource(R.drawable.ic_check_1);

        for(int i=0;i<savedInfos.size();i++){                             //저장을 했던 단어인지 아닌지 체크.
            if(savedInfos.get(i).getId()==csdatas.get(0).getId()){
                isSaved=true;
                break;
            }
        }
        if(isSaved==true)
            btn_save.setImageResource(R.drawable.ic_heart_2);
        else
            btn_save.setImageResource(R.drawable.ic_heart_1);
    }


    public void getRecordText(String text){
        textView.setText(text);
    }

    private  void init(ViewGroup rootView){
        btnRecord=(Button)rootView.findViewById(R.id.btnRecord);
        btnNext=(Button)rootView.findViewById(R.id.btnNext);
        btn_complete=(ImageButton)rootView.findViewById(R.id.btn_complete);
        textView=(TextView)rootView.findViewById(R.id.textView);
        btn_save=(ImageButton)rootView.findViewById(R.id.btn_save);
        textView_practivewords=(TextView)rootView.findViewById(R.id.textView4);
        btnImage=(Button)rootView.findViewById(R.id.btnImage);
        btnVideo=(Button)rootView.findViewById(R.id.btnVideo);
        frameLayout=(FrameLayout)rootView.findViewById(R.id.youtube_view);
    }
}
