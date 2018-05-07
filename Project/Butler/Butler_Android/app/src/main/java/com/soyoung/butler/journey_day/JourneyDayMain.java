package com.soyoung.butler.journey_day;

import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
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
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.bumptech.glide.Glide;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.MapFragment;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.gms.maps.model.PolylineOptions;
import com.soyoung.butler.R;
import com.soyoung.butler.application.ApplicationController;
import com.soyoung.butler.drag.OneDayResultPutter;
import com.soyoung.butler.loginfo.LoginInfo;
import com.soyoung.butler.network.NetworkService;
import com.soyoung.butler.person_dataset.PersonInfo;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.TimeZone;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class JourneyDayMain extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener, OnMapReadyCallback {
    OneDayResultPutter result;
    TextView username, useremail,temperature,temperature_time,temperature_city;
    ImageView userImage,temperature_image, backgroundimg;
    NetworkService service;
    LinearLayout dayLayout1;
    ArrayList<String> mlist, day1List;
    public String day;
    LatLng NEWYORK;
    private GoogleMap googleMap;
    String units = "imperial";
    String APP_ID = "810eec4576703282b3365c384ce1fc07";
    double lat = 40.7, lon = -74.23;
    String url = String.format("http://api.openweathermap.org/data/2.5/weather?lat=%f&lon=%f&units=%s&appid=%s",
            lat, lon, units, APP_ID);
    Boolean flag;
    Handler handler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);

            getTime();
            this.sendEmptyMessageDelayed(0, 1000);
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_journey_day_main);
        service = ApplicationController.getInstance().getNetworkService();
        initNavi();
        initView();
        new GetWeatherTask(temperature,temperature_image, backgroundimg).execute(url);
        handler.sendEmptyMessage(0);

        MapFragment mapFragment = (MapFragment) getFragmentManager()
                .findFragmentById(R.id.map);


        mapFragment.getMapAsync(this);

        dayLayout1 = (LinearLayout) findViewById(R.id.firstLine_3);
        TextView text = (TextView)findViewById(R.id.textView);
        Intent intent = getIntent();
        String[] myStrings = intent.getStringArrayExtra("strings");

        result = OneDayResultPutter.getInstance();
        if(result.results == null)
            flag = true;
        else
            flag = false;

        ArrayList<String> dayList = new ArrayList<>();
        day = intent.getExtras().getString("days");
        for(int i = 0; i < myStrings.length;i++){
            dayList.add(myStrings[i]);
        }
        addCityFromList(dayList,dayLayout1);
        text.setText(day+"일차");
    }

    private  void addCityFromList(ArrayList<String> listFromServer, LinearLayout container){

        for(int i = 0 ; i < listFromServer.size(); i++){

            View layout2 = LayoutInflater.from(this).inflate(R.layout.new_test_layout2, container, false);

            TextView tv = (TextView) layout2.findViewById(R.id.city_name_tv2);

            tv.setText(listFromServer.get(i));

            ImageView imageview = new ImageView(this);
            imageview.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, 2, 1));
            imageview.setBackgroundColor(Color.BLACK);

            layout2.setTag(listFromServer.get(i));

            container.addView(imageview);
            container.addView(layout2);

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

        username = (TextView)headerView.findViewById(R.id.person_name3);
        useremail = (TextView)headerView.findViewById(R.id.person_email3);
        userImage = (ImageView)headerView.findViewById(R.id.person_image3);

        try {
            PersonInfo person = PersonInfo.getInstance();
            username.setText(person.getName());
            useremail.setText(person.getEmail());
            Glide.with(getApplicationContext()).load(person.getImage()).into(userImage);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public void initView(){
        temperature = (TextView)findViewById(R.id.temperature);
        temperature_city = (TextView)findViewById(R.id.temperature_city);
        temperature_time = (TextView)findViewById(R.id.temperature_time);
        temperature_image = (ImageView)findViewById(R.id.temperature_image);
        backgroundimg = (ImageView)findViewById(R.id.backgroundimg);
    }

    @Override
    public void onMapReady(final GoogleMap map) {
        googleMap = map;

        JourneyDaySend sender = new JourneyDaySend();
        try {sender.user_id = PersonInfo.getInstance().user_id;} catch (Exception e) {e.printStackTrace();}
        sender.day = day;
        if(flag == true) {
            Call<List<MapData>> mapResultCall = service.requestMap(sender);
            mapResultCall.enqueue(new Callback<List<MapData>>() {
                @Override
                public void onResponse(Call<List<MapData>> call, Response<List<MapData>> response) {
                    List<MapData> new_list = response.body();
                    for (int i = 0; i < new_list.size(); i++) {
                        Log.e("위도값은 ", String.valueOf(new_list.get(i).latitude));
                        Log.e("경도값은 ", String.valueOf(new_list.get(i).longitude));
                    }

                    NEWYORK = new LatLng(Double.parseDouble(new_list.get(0).latitude), Double.parseDouble(new_list.get(0).longitude));
                    googleMap.moveCamera(CameraUpdateFactory.newLatLng(NEWYORK));
                    googleMap.animateCamera(CameraUpdateFactory.zoomTo(10));
                    MarkerOptions marker = new MarkerOptions();
                    for (int i = 0; i < new_list.size(); i++) {
                        marker.position(new LatLng(Double.parseDouble(new_list.get(i).latitude), Double.parseDouble(new_list.get(i).longitude)))
                                .title(new_list.get(i).recommend_spot);
                        googleMap.addMarker(marker).showInfoWindow(); // 마커추가,화면에출력
                    }

                    for (int i = 0; i < new_list.size() - 1; i++) {
                        map.addPolyline(new PolylineOptions().
                                add(new LatLng(Double.parseDouble(new_list.get(i).latitude), Double.parseDouble(new_list.get(i).longitude)),
                                        new LatLng(Double.parseDouble(new_list.get(i + 1).latitude), Double.parseDouble(new_list.get(i + 1).longitude)
                                        ))
                                .width(6)
                                .color(Color.RED));
                    }

                }

                @Override
                public void onFailure(Call<List<MapData>> call, Throwable t) {

                }
            });
        }else{
            NEWYORK = new LatLng(Double.parseDouble(result.results.get(0).latitude), Double.parseDouble(result.results.get(0).longitude));
            googleMap.moveCamera(CameraUpdateFactory.newLatLng(NEWYORK));
            googleMap.animateCamera(CameraUpdateFactory.zoomTo(10));
            MarkerOptions marker = new MarkerOptions();
            for (int i = 0; i < result.results.size(); i++) {
                marker.position(new LatLng(Double.parseDouble(result.results.get(i).latitude),
                        Double.parseDouble(result.results.get(i).longitude)))
                        .title(result.results.get(i).spot);
                googleMap.addMarker(marker).showInfoWindow(); // 마커추가,화면에출력
            }

            for (int i = 0; i < result.results.size() - 1; i++) {
                map.addPolyline(new PolylineOptions().
                        add(new LatLng(Double.parseDouble(result.results.get(i).latitude), Double.parseDouble(result.results.get(i).longitude)),
                                new LatLng(Double.parseDouble(result.results.get(i + 1).latitude), Double.parseDouble(result.results.get(i + 1).longitude)
                                ))
                        .width(6)
                        .color(Color.RED));
            }

        }

    }

    private void getTime() {
        TimeZone tz;
        Date date = new Date();
        DateFormat dateFormat = new SimpleDateFormat("hh:mm");

        tz = TimeZone.getTimeZone("America/New_York");
        dateFormat.setTimeZone(tz);

        ((TextView)(findViewById(R.id.temperature_time))).setText(dateFormat.format(date));
    }
}
