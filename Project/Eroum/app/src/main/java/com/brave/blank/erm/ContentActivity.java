package com.brave.blank.erm;

import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

import com.brave.blank.erm.Dictation.DictationFragment;
import com.brave.blank.erm.Homeclass.HomeclassDictationFragment;
import com.brave.blank.erm.Homeclass.HomeclassSpeakingFragment;
import com.brave.blank.erm.MyPage.MypageFragment;
import com.brave.blank.erm.Network.ApplicationController;
import com.brave.blank.erm.Network.NetworkService;
import com.brave.blank.erm.Pronunciation.PronunciationFragment;
import com.brave.blank.erm.SpeechRecognition.AudioWriterPCM;
import com.brave.blank.erm.SpeechRecognition.NaverRecognizer;
import com.naver.speech.clientapi.SpeechConfig;

import java.lang.ref.WeakReference;

/**
 * Created by jeonyongjin on 2016. 8. 7..
 */
public class ContentActivity extends AppCompatActivity {

    static NoiseTestFragment noiseTestFragment;
    HomeclassSpeakingFragment homeclassSpeakingFragment;
    HomeclassDictationFragment homeclassDictationFragment;
    DictationFragment dictationFragment;
    PronunciationFragment pronunciationFragment;
    MypageFragment mypageFragment;
    BaseFragment baseFragment;

    boolean isMypage;
    TextView toolbar_title;

    private static final String CLIENT_ID = "HaRGzTahV1Xs9mtmBpdR"; // "내 애플리케이션"에서 Client ID를 확인해서 이곳에 적어주세요.
    private static final SpeechConfig SPEECH_CONFIG = SpeechConfig.OPENAPI_KR; // or SpeechConfig.OPENAPI_EN
    private RecognitionHandler handler;
    private NaverRecognizer naverRecognizer;

    private String mResult;
    private AudioWriterPCM writer;

    private boolean isRunning;

    private NetworkService networkService;

    private void initNetworkService() {
        // TODO: 13. ApplicationController 객체를 이용하여 NetworkService 가져오기
        networkService = ApplicationController.getInstance().getNetworkService();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_content);

        // Set a toolbar to  replace to action bar
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolBar);
        toolbar_title = (TextView)findViewById(R.id.toolbar_title);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayShowTitleEnabled(false);
        changeToolbar(1);


        homeclassDictationFragment = new HomeclassDictationFragment();
        homeclassSpeakingFragment = new HomeclassSpeakingFragment();
        dictationFragment = new DictationFragment();
        pronunciationFragment = new PronunciationFragment();

        noiseTestFragment = new NoiseTestFragment();
        mypageFragment = new MypageFragment();


        Bundle bundle = new Bundle();

        initNetworkService();

        if (savedInstanceState == null) {
            Intent intent = getIntent();
            String data = intent.getStringExtra("class");
            int homework_id = intent.getIntExtra("homework_id",0);

            if (data.equals("SoundTestFragment.class")) {
                bundle.putString("fragment_name", "SoundTestFragment.class");
                noiseTestFragment.setArguments(bundle);
                getSupportFragmentManager().beginTransaction().add(R.id.container, noiseTestFragment).commit();
            } else if (data.equals("Consonant_VowelFragment.class")) {
                bundle.putString("fragment_name", "Consonant_VowelFragment.class");
                noiseTestFragment.setArguments(bundle);
                getSupportFragmentManager().beginTransaction().add(R.id.container, noiseTestFragment).commit();
            } else if (data.equals("FinalConsonantFragment.class")) {
                bundle.putString("fragment_name", "FinalConsonantFragment.class");
                noiseTestFragment.setArguments(bundle);
                getSupportFragmentManager().beginTransaction().add(R.id.container, noiseTestFragment).commit();
            } else if (data.equals("SayingwordsFragment.class")) {
                bundle.putString("fragment_name", "SayingwordsFragment.class");
                noiseTestFragment.setArguments(bundle);
                getSupportFragmentManager().beginTransaction().add(R.id.container, noiseTestFragment).commit();
            } else if (data.equals("SayingsentenceFragment.class")) {
                bundle.putString("fragment_name", "SayingsentenceFragment.class");
                noiseTestFragment.setArguments(bundle);
                getSupportFragmentManager().beginTransaction().add(R.id.container, noiseTestFragment).commit();
            } else if (data.equals("MypageFragment.class")) {
                changeToolbar(1);
                isMypage = true;
                getSupportFragmentManager().beginTransaction().replace(R.id.container, mypageFragment).commit();
            }
            else if (data.equals("HomeclassDictationFragment.class")) {
                bundle.putInt("homework_id", homework_id);
                Log.d("홈워크 아이디 있냐없냐 나와라1 :", String.valueOf(homework_id));
                homeclassDictationFragment.setArguments(bundle);
                getSupportFragmentManager().beginTransaction().add(R.id.container,homeclassDictationFragment).commit();
            }
            else if (data.equals("HomeclassSpeakingFragment.class")){
                bundle.putInt("homework_id", homework_id);
                Log.d("홈워크 아이디 있냐없냐 나와라2 :", String.valueOf(homework_id));
                homeclassSpeakingFragment.setArguments(bundle);
                getSupportFragmentManager().beginTransaction().add(R.id.container,homeclassSpeakingFragment).commit();
            }
            else if (data.equals("DictationFragment.class")){
                bundle.putInt("homework_id", homework_id);
                Log.d("홈워크 아이디 있냐없냐 나와라3 :", String.valueOf(homework_id));
                dictationFragment.setArguments(bundle);
                getSupportFragmentManager().beginTransaction().add(R.id.container,dictationFragment).commit();
            }
            else if (data.equals("PronunciationFragment.class")){
                bundle.putInt("homework_id", homework_id);
                Log.d("홈워크 아이디 있냐없냐 나와라4 :", String.valueOf(homework_id));
                pronunciationFragment.setArguments(bundle);
                getSupportFragmentManager().beginTransaction().add(R.id.container,pronunciationFragment).commit();
            }

        }
        handler = new RecognitionHandler(this);
        naverRecognizer = new NaverRecognizer(this, handler, CLIENT_ID, SPEECH_CONFIG);

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        if (isMypage == true) {
            getMenuInflater().inflate(R.menu.global, menu);
            menu.findItem(R.id.action_settings).setVisible(false);
            toolbar_title.setText("마이 페이지");
            return super.onCreateOptionsMenu(menu);
        } else {
            getMenuInflater().inflate(R.menu.global, menu);
            return super.onCreateOptionsMenu(menu);
        }

    }


    MenuItem item1=null;
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                Log.d("backkey", "ContentActivity 백키 작동");
                if(BackKeyController.getIsHomeclassPractice()){
                    // getSupportFragmentManager().beginTransaction().replace(R.id.container,new MainpageFragment()).addToBackStack(null).commit();   //과제제출 후 부터 Mainpage는
                    Intent intent = new Intent(getApplicationContext(), ToolbarActivity.class);
                    intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);               //모든 activity 스택을 지우는 플래그
                    startActivity(intent);

                    BackKeyController.setIsHomeclassPractice(false);                                                                        //  ContentActivity에 쌓인다.
                    Log.d("backkey", "BackKeyController.getIsHomeclassPractice() 의 if문 안으로 들어옴.");
                    changeToolbar(0);
                    return true;
                }

                if(BackKeyController.getRecordingThread()!=null){                  //소리내기에서 뒤로가기 버튼을 눌렀을때 스레드 죽이기.
                    BackKeyController.getRecordingThread().interrupt();
                    BackKeyController.setRecordingThread(null);
                }

                onBackPressed();
                if(MypageFragment.getMypageItem()!=null)
                    item1=MypageFragment.getMypageItem();

                if(item1!=null)
                    item1.setVisible(true);
                return true;

            case R.id.action_settings:
                Log.d("backkey", "ContentActivity 홈버튼 작동");
                isMypage = true;
                item1=item;
                MypageFragment.setMypageItem(item1,1);
                item.setVisible(false);
                getSupportFragmentManager().beginTransaction().replace(R.id.container, mypageFragment).addToBackStack(null).commit();
                return true;
        }
        return super.onOptionsItemSelected(item);
    }

    public void changeToolbar(int mode) {
        if (mode == 0) {
            getSupportActionBar().setIcon(R.drawable.ic_main_home);
            getSupportActionBar().setDisplayHomeAsUpEnabled(false);
        } else if (mode == 1) {
            getSupportActionBar().setIcon(null);
            getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        }
    }

    // Handle speech recognition Messages.
    private void handleMessage(Message msg) {

        //  homeTalkFragment2=(HomeTalkFragment)getSupportFragmentManager().findFragmentById(R.id.container);
        switch (msg.what) {
            case R.id.clientReady:
                // Now an user can speak.

                baseFragment.getRecordText("");

                writer = new AudioWriterPCM(
                        Environment.getExternalStorageDirectory().getAbsolutePath() + "/NaverSpeechTest");
                writer.open("Test");
                break;

            case R.id.audioRecording:
                writer.write((short[]) msg.obj);
                break;

            case R.id.partialResult:
                // Extract obj property typed with String.
                mResult = (String) (msg.obj);

                baseFragment.getRecordText(mResult);
                break;

            case R.id.finalResult:                                          //이 부분에서 HomeclassSpeakingFragment에서 비교코드를 실행시켜야 한다.
                // Extract obj property typed with String array.
                // The first element is recognition result for speech.
                String[] results = (String[]) msg.obj;
                mResult = results[0];
                baseFragment.getRecordText(mResult);

                if (baseFragment instanceof HomeclassSpeakingFragment) {
                    HomeclassSpeakingFragment.setAnswer();
                }
                break;

            case R.id.recognitionError:
                if (writer != null) {
                    writer.close();
                }

                mResult = "Error code : " + msg.obj.toString();
                baseFragment.getRecordText(mResult);
                // Toast.makeText(getApplication(),CLIENT_ID,Toast.LENGTH_LONG).show();
                //  btnRecord.setText(R.string.str_start);
                //  btnRecord.setEnabled(true);
                isRunning = false;
                break;

            case R.id.clientInactive:
                if (writer != null) {
                    writer.close();
                }

                //  btnRecord.setText(R.string.str_start);
                //      btnRecord.setEnabled(true);
                isRunning = false;
                break;
        }
    }

    public void startRecord(int what) {
        // homeTalkFragment2=(HomeTalkFragment)getSupportFragmentManager().findFragmentById(R.id.container);

        if (what == 0) {
            baseFragment = (HomeTalkFragment) getSupportFragmentManager().findFragmentById(R.id.container);
        } else {
            baseFragment = (HomeclassSpeakingFragment) getSupportFragmentManager().findFragmentById(R.id.container);
        }

        if (!isRunning) {
            // Start button is pushed when SpeechRecognizer's state is inactive.
            // Run SpeechRecongizer by calling recognize().
            mResult = "";
            baseFragment.getRecordText("준비중");
            // btnStart.setText(R.string.str_listening);
            isRunning = true;

            naverRecognizer.recognize();
        } else {
            // This flow is occurred by pushing start button again
            // when SpeechRecognizer is running.
            // Because it means that a user wants to cancel speech
            // recognition commonly, so call stop().
            //  btnStart.setEnabled(false);

            naverRecognizer.getSpeechRecognizer().stop();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        // initialize() must be called on resume time.

        //HomeTalkFragment homeTalkFragment=(HomeTalkFragment)getSupportFragmentManager().findFragmentById(R.id.container);
        naverRecognizer.getSpeechRecognizer().initialize();

        mResult = "";
        //  homeTalkFragment.getRecordText("");
        //  btnStart.setText(R.string.str_start);
        //  btnStart.setEnabled(true);
    }

    @Override
    protected void onPause() {
        super.onPause();
        // release() must be called on pause time.
        naverRecognizer.getSpeechRecognizer().stopImmediately();
        naverRecognizer.getSpeechRecognizer().release();
        isRunning = false;
    }

    // Declare handler for handling SpeechRecognizer thread's Messages.
    static class RecognitionHandler extends Handler {
        private final WeakReference<ContentActivity> mActivity;

        RecognitionHandler(ContentActivity activity) {
            mActivity = new WeakReference<ContentActivity>(activity);
        }

        @Override
        public void handleMessage(Message msg) {
            ContentActivity activity = mActivity.get();
            if (activity != null) {
                activity.handleMessage(msg);
            }
        }
    }


}