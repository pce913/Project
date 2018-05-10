package com.brave.blank.erm;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;

import com.brave.blank.erm.Mainpage.MainpageFragment;
import com.brave.blank.erm.MyPage.MypageFragment;

/**
 * Created by chanung on 2016-07-28.
 */
public class ToolbarActivity extends AppCompatActivity {

    MypageFragment mypageFragment;
    MainpageFragment mainpageFragment;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_toolbar);

        // Set a toolbar to  replace to action bar
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolBar);
        setSupportActionBar(toolbar);

        //  getSupportActionBar().setIcon(R.mipmap.ic_launcher);                  //MainpageFragment일때는 이거
        //  getSupportActionBar().setDisplayHomeAsUpEnabled(true);                 // 다른 Fragment 일때는 이거
        getSupportActionBar().setDisplayShowTitleEnabled(false);
        changeToolbar(0);

        mainpageFragment = new MainpageFragment();
        mypageFragment = new MypageFragment();

//        getSupportFragmentManager().beginTransaction().add(R.id.container,homeTalkFragment).commit();
        //getSupportFragmentManager().beginTransaction().add(R.id.container,speakingRecordFragment).commit();
        getSupportFragmentManager().beginTransaction().add(R.id.container, mainpageFragment).commit();         //mainpageFragment

/////////////////////////////////////////////////////////////////////////////////////

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.global, menu);
        return super.onCreateOptionsMenu(menu);
    }
    MenuItem item1=null;
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                onBackPressed();
                return true;

            case R.id.action_settings:
                item1=item;
                MypageFragment.setMypageItem(item1,0);
                item.setVisible(false);

                Intent intent = new Intent(getApplicationContext(),ContentActivity.class);
                intent.putExtra("class","MypageFragment.class");
                startActivity(intent);
                changeToolbar(1);
//                item.setVisible(false);
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
}