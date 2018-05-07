package com.smu.cs.fookey;

import android.content.Context;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{
    private ImageView image_logo;
    private Button btn_search, btn_history;
    private int width, height;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setData();
        setImage();
    }
    private void setData(){
        image_logo = (ImageView) findViewById(R.id.image_logo);
        btn_search = (Button) findViewById(R.id.btn_search);
        btn_history = (Button) findViewById(R.id.btn_history);
        btn_search.setOnClickListener(this);
        btn_history.setOnClickListener(this);

        DisplayMetrics dm = getApplicationContext().getResources().getDisplayMetrics();
        width = dm.widthPixels;
        height = dm.heightPixels;
    }
    private void setImage(){
        image_logo.setScaleType(ImageView.ScaleType.CENTER_CROP);
    }
    @Override
    public void onClick(View v) {
        switch(v.getId()){
            case R.id.btn_search:
                IntentHandler.mainToSearch(this);
                break;
            case R.id.btn_history:
                IntentHandler.mainToHistory(this);
                break;
            default:
        }
    }
}
