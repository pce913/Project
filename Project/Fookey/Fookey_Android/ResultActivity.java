package com.smu.cs.fookey;

import android.app.ProgressDialog;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.smu.cs.fookey.Network.NetworkApi;

import java.io.File;
import java.util.List;

public class ResultActivity extends AppCompatActivity implements View.OnClickListener{
    private ImageView image_result;
    private TextView resultText;
    private Button yesBtn, noBtn;
    private String imgPath;
    private Context mContext;
    private boolean flag;
    private List<String> res = null;
    private List<String> description = null;
    private int width, height;

    private NetworkApi networkApi;
    private void initNetworkApi(){networkApi=NetworkApi.getNetworkApi(); }

    private ProgressDialog progDialog;
    private Handler confirmHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {

            resultText.setText(res.get(0));
        }
    };

    private _Thread networkThread;

    private final String SEND_IMAGE = "sendImage";
    private final String SEND_MAIN_ANSWER = "sendMainAnswer";
    private final String SEND_SUB_ANSWER = "sendSubAnswer";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_result);
        initData();
        initDialog();
        initNetworkApi();

        setImage(imgPath);
        doNetworkOperation(SEND_IMAGE);

        yesBtn.setOnClickListener(this);
        noBtn.setOnClickListener(this);
    }
    private void initDialog(){
        progDialog = new ProgressDialog( this );

        progDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
        progDialog.setMessage("please wait....");
    }
    private void initData(){
        flag = false;
        mContext = getApplicationContext();
        imgPath = getIntent().getStringExtra("imgUri");
        image_result = (ImageView)findViewById(R.id.image_result);
        resultText = (TextView)findViewById(R.id.text_result);
        yesBtn = (Button)findViewById(R.id.btn_yes);
        noBtn = (Button)findViewById(R.id.btn_no);

        DisplayMetrics dm = getApplicationContext().getResources().getDisplayMetrics();
        width = dm.widthPixels;
        height = dm.heightPixels;
    }
    private void doNetworkOperation(String opt){
        progDialog.show();
        networkThread = new _Thread(opt);
        networkThread.start();
    }
    private void setImage(String Path){
        Log.i("PATH", Path);
        File imgFile = new  File(Path);
        if(imgFile.exists()){

            BitmapFactory.Options opt = new BitmapFactory.Options();
            opt.inPreferredConfig = Bitmap.Config.RGB_565;
            opt.inSampleSize = 1;
            opt.inPurgeable = true;
            Bitmap src = BitmapFactory.decodeFile(imgFile.getAbsolutePath(), opt);
            Bitmap resize = Bitmap.createScaledBitmap(src, opt.outWidth, opt.outHeight, true);

            image_result.setImageBitmap(resize);
            image_result.getLayoutParams().height = image_result.getLayoutParams().width = width;
            image_result.setRotation(90);
        }
    }
    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.btn_yes:
                Log.i("TEST", flag + " :" + res.get(0));
                if(!flag) {
                    flag = true;
                    doNetworkOperation(SEND_MAIN_ANSWER);
                }
                else{
                    doNetworkOperation(SEND_SUB_ANSWER);
                }
                break;
            case R.id.btn_no:
                res.remove(0);
                resultText.setText(res.get(0));
                break;
            default:
                break;
        }
    }
    class _Thread extends Thread{
        private String status;
        public _Thread(String name) {
            super(name);
            status = name;
        }
        @Override
        public void run() {
            super.run();
            //Message message = new Message();
            if(status == SEND_IMAGE){
                //TODO : 시간이 걸리는 처리 삽입
                res = networkApi.sendImage(mContext, imgPath);
                confirmHandler.sendEmptyMessage(0);
            }
            else if(status == SEND_MAIN_ANSWER){
                //TODO : 시간이 걸리는 처리 삽입
                res = networkApi.sendMainAnswer(res.get(0));
                confirmHandler.sendEmptyMessage(0);
            }
            else if(status == SEND_SUB_ANSWER){
                //TODO : 시간이 걸리는 처리 삽입
                description = networkApi.sendSubAnswer(res.get(0));
                Log.w("TTTTTTTT", res.get(0));
                //Description description = new Description(res.get(0), "한식 > 밥류", "313kcal / 1공기 (210g)", "안전식품", new Nutrient(91, 8, 1));
                finish();
                IntentHandler.ResultToSpecific(mContext, description, imgPath);
            }
            progDialog.dismiss();
        }
    }
}