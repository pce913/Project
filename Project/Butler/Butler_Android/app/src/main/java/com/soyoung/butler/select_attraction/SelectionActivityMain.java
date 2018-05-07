package com.soyoung.butler.select_attraction;

import android.content.Intent;
import android.content.SharedPreferences;
import android.media.Image;
import android.os.Bundle;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.Toolbar;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

import com.bumptech.glide.Glide;
import com.soyoung.butler.R;
import com.soyoung.butler.application.ApplicationController;
import com.soyoung.butler.attraction.AlternativesCityID;
import com.soyoung.butler.attraction.AttractionResult;
import com.soyoung.butler.attraction.AttractionSend;
import com.soyoung.butler.loginfo.LoginInfo;
import com.soyoung.butler.network.NetworkService;
import com.soyoung.butler.person_dataset.PersonInfo;
import com.soyoung.butler.select_spot.SelectSpotMain;

import java.util.ArrayList;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class SelectionActivityMain extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener {
    TextView username, useremail;
    ImageButton nextBtn;
    ImageView userImage;
    NetworkService service;
    RecyclerView recyclerView;
    RecyclerAdapter2 recyclerAdapter;
    RecyclerView.LayoutManager layoutManager;
    String keyword;
    String user_id;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_selection_main);
        initNavi();
        recyclerView = (RecyclerView)findViewById(R.id.recycler2);
        recyclerView.setHasFixedSize(true);
        nextBtn = (ImageButton) findViewById(R.id.nextBtn2);

        Intent intent = getIntent();
        AttractionSend sender = new AttractionSend();
        keyword = intent.getExtras().getString("user");
        sender.keyword = keyword;
        sender.selecting_type = "2";
        try {
            sender.user_id = PersonInfo.getInstance().user_id;
            //Toast.makeText(getApplicationContext(),sender.user_id,Toast.LENGTH_SHORT).show();
        } catch (Exception e) {
            e.printStackTrace();
        }
        Call<ArrayList<AttractionResult>> mainResultCall=service.requestAttraction(sender);
        mainResultCall.enqueue(new Callback<ArrayList<AttractionResult>>() {
            @Override
            public void onResponse(Call<ArrayList<AttractionResult>> call, Response<ArrayList<AttractionResult>> response) {
                ArrayList<AttractionResult> list = response.body();
                layoutManager = new LinearLayoutManager(getApplicationContext());
                recyclerView.setLayoutManager(layoutManager);
                recyclerAdapter = new RecyclerAdapter2(list, getApplicationContext());
                recyclerAdapter.setAdapterItemList(list);
                recyclerView.setAdapter(recyclerAdapter);
            }

            @Override
            public void onFailure(Call<ArrayList<AttractionResult>> call, Throwable t) {

            }
        });
        nextBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                AlternativesCityID alternativesCityID = null;
                try {
                    alternativesCityID = AlternativesCityID.getInstance();
                    alternativesCityID.user_id = PersonInfo.getInstance().user_id;
                 //   Toast.makeText(getApplicationContext(), alternativesCityID.user_id, Toast.LENGTH_SHORT).show();
                } catch (Exception e) {
                    e.printStackTrace();
                }
                alternativesCityID.alternatives_city_sight_id = RecyclerAdapter2.getCityID();
                //Toast.makeText(getApplicationContext(), (CharSequence) alternativesCityID.alternatives_city_sight_id,Toast.LENGTH_SHORT).show();
                Call<AlternativesCityID> alternativesCityIDCall = service.requestAlternative(alternativesCityID);
                alternativesCityIDCall.enqueue(new Callback<AlternativesCityID>() {
                    @Override
                    public void onResponse(Call<AlternativesCityID> call, Response<AlternativesCityID> response) {
                        Intent intent =  new Intent(getApplicationContext(), SelectSpotMain.class);
                        intent.putExtra("user",keyword);
                        startActivity(intent);
                    }

                    @Override
                    public void onFailure(Call<AlternativesCityID> call, Throwable t) {

                    }
                });


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
        service = ApplicationController.getInstance().getNetworkService();
        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);
        View headerView = navigationView.getHeaderView(0);

        username = (TextView)headerView.findViewById(R.id.person_name4);
        useremail = (TextView)headerView.findViewById(R.id.person_email4);
        userImage = (ImageView)headerView.findViewById(R.id.person_image4);
        try {
            PersonInfo person = PersonInfo.getInstance();
            username.setText(person.getName());
            useremail.setText(person.getEmail());
            Glide.with(getApplicationContext()).load(person.getImage()).into(userImage);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
