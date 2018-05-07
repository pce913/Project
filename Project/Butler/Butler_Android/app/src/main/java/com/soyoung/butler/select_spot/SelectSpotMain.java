package com.soyoung.butler.select_spot;

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
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.bumptech.glide.Glide;
import com.soyoung.butler.R;
import com.soyoung.butler.application.ApplicationController;
import com.soyoung.butler.attraction.AlternativesCityID;
import com.soyoung.butler.attraction.AttractionMainView;
import com.soyoung.butler.attraction.EssentailCityID;
import com.soyoung.butler.loginfo.LoginInfo;
import com.soyoung.butler.network.NetworkService;
import com.soyoung.butler.person_dataset.PersonInfo;
import com.soyoung.butler.recommend_path.RecommandPathMain;
import com.soyoung.butler.select_attraction.SelectionActivityMain;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class SelectSpotMain extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener {
    TextView username, useremail;
    ImageView userImage;
    String user_id;
    String keyword;
    SelectResult result;
    NetworkService service;
    Button next;
    ImageView btn1,btn2;
    RecyclerView recyclerView3,recyclerView4;
    RecyclerAdapter3 recyclerAdapter3;
    RecyclerAdapter4 recyclerAdapter4;
    RecyclerView.LayoutManager layoutManager,layoutManager2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_select_spot_main);
        recyclerView3 = (RecyclerView)findViewById(R.id.recycler_top);
        recyclerView3.setHasFixedSize(true);
        recyclerView4 = (RecyclerView)findViewById(R.id.recycler_bottom);
        recyclerView4.setHasFixedSize(true);
        next = (Button)findViewById(R.id.next);
        btn1 = (ImageButton)findViewById(R.id.button2);
        btn2 = (ImageButton)findViewById(R.id.button_test);
        Intent intent = getIntent();
        keyword = intent.getExtras().getString("user");
        initNavi();
        SelectSend send = new SelectSend();
        service = ApplicationController.getInstance().getNetworkService();
        try {
            send.user_id = PersonInfo.getInstance().user_id;
        } catch (Exception e) {
            e.printStackTrace();
        }
        Call<SelectResult>  selectResultCall = service.requestSelectResult(send);
        selectResultCall.enqueue(new Callback<SelectResult>() {
            @Override
            public void onResponse(Call<SelectResult> call, Response<SelectResult> response) {
                if(response.isSuccessful()){
                layoutManager = new LinearLayoutManager(getApplicationContext());
                layoutManager2 = new LinearLayoutManager(getApplicationContext());
                result = response.body();

                recyclerView3.setLayoutManager(layoutManager);
                recyclerAdapter3 = new RecyclerAdapter3(result.essentials, getApplicationContext());
                recyclerAdapter3.setAdapterItemList(result.essentials);
                recyclerView3.setAdapter(recyclerAdapter3);

                recyclerView4.setLayoutManager(layoutManager2);
                recyclerAdapter4 = new RecyclerAdapter4(result.alternatives, getApplicationContext());
                recyclerAdapter4.setAdapterItemList(result.alternatives);
                recyclerView4.setAdapter(recyclerAdapter4);
                }
                else{
                    Toast.makeText(getApplicationContext(),"not successful",Toast.LENGTH_SHORT).show();
                }
            }
            @Override
            public void onFailure(Call<SelectResult> call, Throwable t) {
                Toast.makeText(getApplicationContext(),"Failure",Toast.LENGTH_SHORT).show();
            }
        });

        next.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                AlternativesCityID alternativesCityID = null;
                EssentailCityID essentailCityID = null;
                try {
                    alternativesCityID = AlternativesCityID.getInstance();
                    alternativesCityID.user_id = PersonInfo.getInstance().user_id;
                    essentailCityID = EssentailCityID.getInstance();
                    essentailCityID.user_id = PersonInfo.getInstance().user_id;

                } catch (Exception e) {
                    e.printStackTrace();
                }
                essentailCityID.essentials_city_sight_id = RecyclerAdapter3.getCityNotChecked();
//                Log.d("essentials", String.valueOf(essentailCityID.essentials_city_sight_id));
//                Log.d("essentials id",essentailCityID.user_id);
                //Toast.makeText(getApplicationContext(),essentailCityID.essentials_city_sight_id.get(0),Toast.LENGTH_SHORT).show();
                Call<EssentailCityID> essentailCityIDCall = service.requestEssential(essentailCityID);
                essentailCityIDCall.enqueue(new Callback<EssentailCityID>() {
                    @Override
                    public void onResponse(Call<EssentailCityID> call, Response<EssentailCityID> response) {

                    }

                    @Override
                    public void onFailure(Call<EssentailCityID> call, Throwable t) {

                    }
                });

                alternativesCityID.alternatives_city_sight_id = RecyclerAdapter4.getCityNotChecked();
//                Log.d("alternatives", String.valueOf(alternativesCityID.alternatives_city_sight_id));
//                Log.d("alternatives id",alternativesCityID.user_id);
                Call<AlternativesCityID> alternativesCityIDCall = service.requestAlternative(alternativesCityID);
                alternativesCityIDCall.enqueue(new Callback<AlternativesCityID>() {

                    @Override
                    public void onResponse(Call<AlternativesCityID> call, Response<AlternativesCityID> response) {

                    }

                    @Override
                    public void onFailure(Call<AlternativesCityID> call, Throwable t) {

                    }
                });

                startActivity(new Intent(getApplicationContext(), RecommandPathMain.class));
            }
        });
        btn1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                AlternativesCityID alternativesCityID = null;
                try {
                    alternativesCityID.user_id = PersonInfo.getInstance().user_id;
                    alternativesCityID.alternatives_city_sight_id = RecyclerAdapter4.getCityNotChecked();
                } catch (Exception e) {
                    e.printStackTrace();
                }
                    Intent intent = new Intent(getApplicationContext(), SelectionActivityMain.class);
                    intent.putExtra("user",keyword);
                    startActivity(intent);
            }
        });

        btn2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                EssentailCityID essentailCityID = null;
                try {
                    essentailCityID.user_id = PersonInfo.getInstance().user_id;
                    essentailCityID.essentials_city_sight_id = RecyclerAdapter3.getCityNotChecked();
                } catch (Exception e) {
                    e.printStackTrace();
                }
                Intent intent = new Intent(getApplicationContext(), AttractionMainView.class);
                intent.putExtra("user",keyword);
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
        username = (TextView)headerView.findViewById(R.id.person_name5);
        useremail = (TextView)headerView.findViewById(R.id.person_email5);
        userImage = (ImageView)headerView.findViewById(R.id.person_image5);

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

}
