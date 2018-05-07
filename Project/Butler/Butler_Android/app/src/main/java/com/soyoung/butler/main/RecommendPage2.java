package com.soyoung.butler.main;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.ImageView;

import com.soyoung.butler.R;

public class RecommendPage2 extends AppCompatActivity {
    String check;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recommend_page2);
        ImageView img = (ImageView)findViewById(R.id.image_asset2);
        Intent intent = getIntent();
        check = intent.getExtras().getString("pages");
        if(check.equals("1")){
            img.setImageResource(R.drawable.mainla_1);
        }else if(check.equals("2")){
            img.setImageResource(R.drawable.mainla_2);
        }else{
            img.setImageResource(R.drawable.mainla_3);
        }
    }

}
