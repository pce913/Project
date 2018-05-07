package com.soyoung.butler.main;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.design.widget.NavigationView;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentStatePagerAdapter;
import android.support.v4.view.GravityCompat;
import android.support.v4.view.ViewPager;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.MenuItem;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;

import com.bumptech.glide.Glide;
import com.soyoung.butler.R;
import com.soyoung.butler.application.ApplicationController;
import com.soyoung.butler.attraction.AttractionMainView;
import com.soyoung.butler.loginfo.LoginInfo;
import com.soyoung.butler.network.NetworkService;
import com.soyoung.butler.person_dataset.PersonInfo;

import java.util.List;

import me.relex.circleindicator.CircleIndicator;

public class MainActivity extends AppCompatActivity implements NavigationView.OnNavigationItemSelectedListener, RadioGroup.OnCheckedChangeListener {
    private ViewPager mViewPager,mViewPager2;
    private PagerAdapter mPagerAdapter;
    private CustomPagerAdapter mPagerAdapter2;
    NetworkService service;
    CircleIndicator indicator,indicator2;
    TextView username, useremail;
    ImageView userImage;
    Button btn;
    EditText search;
    private int mPageNumber;
    List<List_item> new_list;
    RadioGroup group;
    RadioButton option1,option2,option3,option4;
    public int id;
    InputMethodManager imm;
    PersonInfo person = null;
    String theme = "전체";
    @Nullable
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
        initNavi();
        setViewPager();
        Toast.makeText(getApplicationContext(),person.user_id,Toast.LENGTH_SHORT).show();
        imm = (InputMethodManager)getSystemService(INPUT_METHOD_SERVICE);

        group.setOnCheckedChangeListener(this);
        id = group.getCheckedRadioButtonId();

        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String search_word = search.getText().toString();
                Intent intent = new Intent(getBaseContext(), AttractionMainView.class);
                intent.putExtra("user",search_word);
                intent.putExtra("theme",theme);
                startActivity(intent);
            }
        });


    }

    public void linearOnClick(View v) {
        imm.hideSoftInputFromWindow(search.getWindowToken(), 0);
    }

    private class PagerAdapter extends FragmentStatePagerAdapter {

        public PagerAdapter(FragmentManager fm) {
            super(fm);
        }
        @Override
        public Fragment getItem(int position) {
            // 해당하는 page의 Fragment를 생성합니다.
            return PageFragment.create(position);
        }

        @Override
        public int getCount() {
            return 3;  // 총 5개의 page를 보여줍니다.
        }

    }
    private class CustomPagerAdapter extends FragmentStatePagerAdapter {

        public CustomPagerAdapter(FragmentManager fm) {
            super(fm);
        }
        @Override
        public Fragment getItem(int position) {
            // 해당하는 page의 Fragment를 생성합니다.
            return PageFragment2.create(position);
        }

        @Override
        public int getCount() {
            return 3;  // 총 5개의 page를 보여줍니다.
        }

    }

    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
    }


    @SuppressWarnings("StatementWithEmptyBody")
    @Override
    public boolean onNavigationItemSelected(MenuItem item) {
        // Handle navigation view item clicks here.
        int id = item.getItemId();

        if (id == R.id.edit_profile) {
            // Handle the camera action
        } else if (id == R.id.travel_schedule) {

        } else if (id == R.id.write_drawer) {

        } else if (id == R.id.notice) {

        }else if(id == R.id.feedback){

        }else if(id==R.id.nav_share){
            SharedPreferences setting;
            SharedPreferences.Editor editor;
            setting = getSharedPreferences("setting", MODE_PRIVATE);
            editor = setting.edit();
            editor.clear();
            editor.commit();
            Intent intent = new Intent(getApplicationContext(), LoginInfo.class);
            startActivity(intent);
            finish();
        }

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);
        return true;
    }

    public void initView(){

        btn = (Button)findViewById(R.id.searchBtn);
        search = (EditText)findViewById(R.id.city);
        group = (RadioGroup)findViewById(R.id.radioGroup1);
        option1 = (RadioButton)findViewById(R.id.ch1);
        option2 = (RadioButton)findViewById(R.id.ch2);
        option3 = (RadioButton)findViewById(R.id.ch3);
        option4 = (RadioButton)findViewById(R.id.ch4);
        mViewPager = (ViewPager) findViewById(R.id.pager);
        indicator = (CircleIndicator)findViewById(R.id.indicator);
        mViewPager2 = (ViewPager) findViewById(R.id.pager2);
        indicator2 = (CircleIndicator)findViewById(R.id.indicator2);


    }
    public void initNavi(){
        service = ApplicationController.getInstance().getNetworkService();
        NavigationView nav = (NavigationView) findViewById(R.id.nav_view);
        View headerView = nav.getHeaderView(0);

        username = (TextView)headerView.findViewById(R.id.person_name);
        useremail = (TextView)headerView.findViewById(R.id.person_email);
        userImage = (ImageView)headerView.findViewById(R.id.imageView);

        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        //toolbar.set
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.setDrawerListener(toggle);
        toggle.syncState();

        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);
        try {
            person = PersonInfo.getInstance();
            username.setText(person.getName());
            useremail.setText(person.getEmail());
            Glide.with(getApplicationContext()).load(person.getImage()).into(userImage);

        } catch (Exception e) {
            e.printStackTrace();
        }

    }
    public void setViewPager(){
        mPagerAdapter = new PagerAdapter(getSupportFragmentManager());
        mViewPager.setAdapter(mPagerAdapter);
        indicator.setViewPager(mViewPager);

        mPagerAdapter2 = new CustomPagerAdapter(getSupportFragmentManager());
        mViewPager2.setAdapter(mPagerAdapter2);
        indicator2.setViewPager(mViewPager2);
    }

    public void onCheckedChanged(RadioGroup group, int checkedId) {

        switch (checkedId) {
            case R.id.ch1:
            {
                theme = "전체";
                option1.setBackgroundResource(R.drawable.main_button_checked_a);
                option2.setBackgroundResource(R.drawable.main_button_unchecked_b);
                option3.setBackgroundResource(R.drawable.main_button_unchecked_c);
                option4.setBackgroundResource(R.drawable.main_button_unchecked_d);
            }
            break;
            case R.id.ch2:
            {
                theme = "유적지";
                option2.setBackgroundResource(R.drawable.main_button_checked_b);
                option1.setBackgroundResource(R.drawable.main_button_unchecked_a);
                option3.setBackgroundResource(R.drawable.main_button_unchecked_c);
                option4.setBackgroundResource(R.drawable.main_button_unchecked_d);

            }
            break;
            case R.id.ch3:
            {
                theme = "도심";
                option3.setBackgroundResource(R.drawable.main_button_checked_c);
                option1.setBackgroundResource(R.drawable.main_button_unchecked_a);
                option2.setBackgroundResource(R.drawable.main_button_unchecked_b);
                option4.setBackgroundResource(R.drawable.main_button_unchecked_d);

            }
            break;
            case R.id.ch4:
            {
                theme = "휴식";
                option4.setBackgroundResource(R.drawable.main_button_checked_d);
                option1.setBackgroundResource(R.drawable.main_button_unchecked_a);
                option2.setBackgroundResource(R.drawable.main_button_unchecked_b);
                option3.setBackgroundResource(R.drawable.main_button_unchecked_c);
            }
            break;
            default:
                break;
        }
    }

}
