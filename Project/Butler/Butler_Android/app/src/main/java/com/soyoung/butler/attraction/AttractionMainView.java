package com.soyoung.butler.attraction;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

import com.bumptech.glide.Glide;
import com.soyoung.butler.R;
import com.soyoung.butler.application.ApplicationController;
import com.soyoung.butler.loginfo.LoginInfo;
import com.soyoung.butler.network.NetworkService;
import com.soyoung.butler.person_dataset.PersonInfo;
import com.soyoung.butler.select_attraction.SelectionActivityMain;

import java.util.ArrayList;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class AttractionMainView extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener {
    ImageButton nextBtn;
    NetworkService service;
    ImageView img;
    TextView username, useremail;
    ImageView userImage;
    RecyclerView recyclerView;
    RecyclerAdapter recyclerAdapter;
    RecyclerView.LayoutManager layoutManager;
    String user_id;
    public String keyword;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_attraction_main_view);
        initNavi();
        service = ApplicationController.getInstance().getNetworkService();
        recyclerView = (RecyclerView)findViewById(R.id.recycler);
        recyclerView.setHasFixedSize(true);
        CommunicateServer();
        nextBtn = (ImageButton) findViewById(R.id.nextBtn);
        nextBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                EssentailCityID essential = null;
                try {essential = EssentailCityID.getInstance();} catch (Exception e) {e.printStackTrace();}
                    essential.user_id = user_id;
                    essential.essentials_city_sight_id = RecyclerAdapter.getCityID();
                    Call<EssentailCityID> essentailCityIDCall = service.requestEssential(essential);
                    essentailCityIDCall.enqueue(new Callback<EssentailCityID>() {
                        @Override
                        public void onResponse(Call<EssentailCityID> call, Response<EssentailCityID> response) {
                            Intent intent = new Intent(getApplication(),SelectionActivityMain.class);
                            intent.putExtra("user",keyword);
                            startActivity(intent);
                        }
                        @Override
                        public void onFailure(Call<EssentailCityID> call, Throwable t) {

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

        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        View headerView = navigationView.getHeaderView(0);
        navigationView.setNavigationItemSelectedListener(this);
        username = (TextView)headerView.findViewById(R.id.person_name2);
        useremail = (TextView)headerView.findViewById(R.id.person_email2);
        userImage = (ImageView)headerView.findViewById(R.id.person_image2);

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

      public void CommunicateServer(){
          Intent intent = getIntent();
          AttractionSend sender = new AttractionSend();
          keyword = intent.getExtras().getString("user");
          String theme = intent.getExtras().getString("theme");
          sender.keyword = keyword;
          sender.theme = theme;
          sender.selecting_type = "1";
          Call<ArrayList<AttractionResult>> mainResultCall=service.requestAttraction(sender);
          mainResultCall.enqueue(new Callback<ArrayList<AttractionResult>>() {
              @Override
              public void onResponse(Call<ArrayList<AttractionResult>> call, Response<ArrayList<AttractionResult>> response) {
                  ArrayList<AttractionResult> list = response.body();
                  layoutManager = new LinearLayoutManager(getApplicationContext());
                  recyclerView.setLayoutManager(layoutManager);
                  recyclerAdapter = new RecyclerAdapter(list, getApplicationContext());
                  recyclerAdapter.setAdapterItemList(list);
                  recyclerView.setAdapter(recyclerAdapter);
              }

              @Override
              public void onFailure(Call<ArrayList<AttractionResult>> call, Throwable t) {

              }
          });

      }
}
