package com.soyoung.butler.recommend_path;

import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.Bundle;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.bumptech.glide.Glide;
import com.soyoung.butler.R;
import com.soyoung.butler.application.ApplicationController;
import com.soyoung.butler.drag.DragActivity;
import com.soyoung.butler.loginfo.LoginInfo;
import com.soyoung.butler.network.NetworkService;
import com.soyoung.butler.person_dataset.PersonInfo;

import java.util.ArrayList;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class RecommandPathMain extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener {
    NetworkService service;
    LinearLayout dayLayout1, dayLayout2, dayLayout3;
    ArrayList<String> day1List, day2List, day3List;
    ArrayList<ArrayList<String>> recommend_path;
    TextView username, useremail;
    ImageView userImage;
    String user_id;
    ImageButton btn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recommand_path_main);
        initNavi();
        btn = (ImageButton)findViewById(R.id.nextBtn3);
        day1List = new ArrayList<>();
        day2List = new ArrayList<>();
        day3List = new ArrayList<>();

        dayLayout1 = (LinearLayout)findViewById(R.id.firstLine_2);
        dayLayout2 = (LinearLayout)findViewById(R.id.secondLine_2);
        dayLayout3 = (LinearLayout)findViewById(R.id.thirdLine_2);


        dayLayout1.setTag("day1");
        dayLayout2.setTag("day2");
        dayLayout3.setTag("day3");


        service = ApplicationController.getInstance().getNetworkService();
        try {
            user_id = PersonInfo.getInstance().user_id;
        } catch (Exception e) {
            e.printStackTrace();
        }

        final Call<ArrayList<ArrayList<String>>> recommend = service.getRecommend(user_id);
        recommend.enqueue(new Callback<ArrayList<ArrayList<String>>>() {
            @Override
            public void onResponse(Call<ArrayList<ArrayList<String>>> call, Response<ArrayList<ArrayList<String>>> response) {
                recommend_path = response.body();

                addCityFromList(recommend_path.get(0),dayLayout1,day1List);
                addCityFromList(recommend_path.get(1),dayLayout2,day2List);
                addCityFromList(recommend_path.get(2),dayLayout3,day3List);
            }

            @Override
            public void onFailure(Call<ArrayList<ArrayList<String>>> call, Throwable t) {

            }
        });
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), DragActivity.class);
                String[] myStrings1 = new String[day1List.size()];
                String[] myStrings2 = new String[day2List.size()];
                String[] myStrings3 = new String[day3List.size()];
                for (int i = 0; i < day1List.size(); i++) {
                    myStrings1[i] = day1List.get(i);
                }
                for (int i = 0; i < day2List.size(); i++) {
                    myStrings2[i] = day2List.get(i);
                }
                for (int i = 0; i < day3List.size(); i++) {
                    myStrings3[i] = day3List.get(i);
                }
              //  Log.d("지웅", String.valueOf(myStrings1[0]));
                intent.putExtra("string1",myStrings1);
                intent.putExtra("string2",myStrings2);
                intent.putExtra("string3",myStrings3);
                startActivity(intent);
            }
        });
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

    public void initNavi(){
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.setDrawerListener(toggle);
        toggle.syncState();

        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        View headerView = navigationView.getHeaderView(0);
        navigationView.setNavigationItemSelectedListener(this);
        username = (TextView)headerView.findViewById(R.id.person_name6);
        useremail = (TextView)headerView.findViewById(R.id.person_email6);
        userImage = (ImageView)headerView.findViewById(R.id.person_image6);

        try {
            PersonInfo person = PersonInfo.getInstance();
            Log.e("person ID",person.getUser_id());
            username.setText(person.getName());
            useremail.setText(person.getEmail());
            this.user_id = person.user_id;

            Glide.with(getApplicationContext()).load(person.getImage()).into(userImage);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    private  void addCityFromList(ArrayList<String> listFromServer, LinearLayout container, ArrayList<String> daylist){

        for(int i = 0 ; i < listFromServer.size(); i++){
            View layout2 = LayoutInflater.from(this).inflate(R.layout.new_test_layout, container, false);
            TextView tv = (TextView) layout2.findViewById(R.id.city_name_tv);
            tv.setText(listFromServer.get(i));

            ImageView imageview = new ImageView(this);
            imageview.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, 2, 1));
            imageview.setBackgroundColor(Color.WHITE);
            layout2.setTag(listFromServer.get(i));

            container.addView(imageview);
            container.addView(layout2);
            daylist.add(listFromServer.get(i));

        }

    }
}
