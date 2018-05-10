package com.soyoung.butler.drag;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.DatePickerDialog;
import android.app.Dialog;
import android.content.ClipData;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.DragEvent;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.DragShadowBuilder;
import android.view.View.OnDragListener;
import android.view.View.OnTouchListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.soyoung.butler.R;
import com.soyoung.butler.application.ApplicationController;
import com.soyoung.butler.dialog.SaveDialog;
import com.soyoung.butler.journey_day.JourneyDayMain;
import com.soyoung.butler.main.MainActivity;
import com.soyoung.butler.network.NetworkService;
import com.soyoung.butler.person_dataset.PersonInfo;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.StringTokenizer;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

import static android.R.attr.y;

//http://www.vogella.com/tutorials/AndroidDragAndDrop/article.html
public class DragActivity extends Activity {
    /** Called when the activity is first created. */

    LinearLayout dayLayout1, dayLayout2, dayLayout3, dayLayout4, trashCan;
    List<String> day1List, day2List, day3List, day4List;
    List<String> mlist, mlist2;
    ArrayList<CityData> cityDatas;
    Button savebtn;
    boolean isCheck,isSave;
    NetworkService networkService;
    private TextView mDateDisplay;
    private TextView mDateDisplay2;
    private Button mPickDate;
    private Button mPickDate2;
    private int mYear;
    private int mMonth;
    private int mDay;
    public int cnt = 0;

    static final int DATE_DIALOG_ID = 0;
    final Calendar c = Calendar.getInstance();

    RecyclerView.Adapter cityListAdapter;
    RecyclerView recyclerView;
    List<String> templist;
    String user_id;
    SaveDialog saveDialog;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_drag);
        networkService = ApplicationController.getInstance().getNetworkService();

        savebtn = (Button)findViewById(R.id.savebtn);
        mDateDisplay = (TextView)findViewById(R.id.txt);
        mDateDisplay2 = (TextView)findViewById(R.id.txt2);
        mPickDate = (Button)findViewById(R.id.btn);
        mPickDate2 = (Button)findViewById(R.id.btn2);
        isCheck = false;
        mPickDate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                cnt = 0;
                showDialog(DATE_DIALOG_ID);
            }
        });

        mPickDate2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(isCheck == true) {
                    cnt = 1;
                    showDialog(DATE_DIALOG_ID);
                }
                else
                    Toast.makeText(getApplicationContext(),"출발 날짜를 입력하세요!",Toast.LENGTH_SHORT).show();
            }
        });

        saveDialog = new SaveDialog(this);
        saveDialog.setOnDismissListener(new DialogInterface.OnDismissListener() {
            @Override
            public void onDismiss(DialogInterface dialog) {
                if(saveDialog.isSave()){
                    try {
                        PersonInfo person = PersonInfo.getInstance();
                        user_id = person.user_id;
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
//                Toast.makeText(getApplicationContext(),)
                    String dayStart = (String) mDateDisplay.getText();
                    String dayEnd = (String) mDateDisplay2.getText();
                    //TODO 널처리해줘야댐 빈값입력

                    final DaySend daySend = new DaySend();
                    daySend.start_date = dayStart;
                    Log.e("start",daySend.start_date);
                    daySend.end_date = dayEnd;
                    Log.e("end",daySend.end_date);
                    ArrayList<String> temp1 = new ArrayList<String>(day1List.size());
                    ArrayList<String> temp2 = new ArrayList<String>(day2List.size());
                    ArrayList<String> temp3 = new ArrayList<String>(day3List.size());
                    ArrayList<String> temp4 = new ArrayList<String>(day4List.size());


                    //if(day1List.size() != 0 && day2List.size() != 0 && day3List.size() != 0 && day4List.size() != 0) {

                    // 첫째날
                    for (int i = 0; i < day1List.size(); i++) {
                        temp1.add(day1List.get(i));
                    }
                    // 2
                    for (int i = 0; i < day2List.size(); i++) {
                        temp2.add(day2List.get(i));
                    }
                    //3
                    for (int i = 0; i < day3List.size(); i++) {
                        temp3.add(day3List.get(i));
                    }
                    //4
                    for (int i = 0; i < day4List.size(); i++) {
                        temp4.add(day4List.get(i));
                    }
                    //}

                    daySend.schedule.add(temp1);
                    daySend.schedule.add(temp2);
                    daySend.schedule.add(temp3);
                    daySend.schedule.add(temp4);
                    daySend.user_id = user_id;

                    final Call<DaySend> dayCall = networkService.sendDay(daySend);
                    dayCall.enqueue(new Callback<DaySend>() {
                        @Override
                        public void onResponse(Call<DaySend> call, Response<DaySend> response) {
                            Toast.makeText(getApplicationContext(), "저장 완료", Toast.LENGTH_SHORT);
                            Intent intent = new Intent(getApplicationContext(),MainActivity.class);
                            intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP);
                            startActivity(intent);
                        }

                        @Override
                        public void onFailure(Call<DaySend> call, Throwable t) {
                            Toast.makeText(getApplicationContext(), "에러", Toast.LENGTH_SHORT);
                        }
                    });

                }
            }
        });

        mYear = c.get(Calendar.YEAR);
        mMonth = c.get(Calendar.MONTH);
        mDay = c.get(Calendar.DAY_OF_MONTH);


        //아래 리싸이클러뷰
        recyclerView = (RecyclerView) findViewById(R.id.recyclerViewDot);
        recyclerView.setHasFixedSize(true);
        LinearLayoutManager layoutManager = new LinearLayoutManager(this);
        layoutManager.setOrientation(LinearLayoutManager.HORIZONTAL);
        recyclerView.setLayoutManager(layoutManager);

        //각각의 날짜별 데이터받을 그릇들
        day1List = new ArrayList<>();
        day2List = new ArrayList<>();
        day3List = new ArrayList<>();
        day4List = new ArrayList<>();

        Intent intent = getIntent();
        String[] day1Strings = intent.getStringArrayExtra("string1");
        String[] day2Strings = intent.getStringArrayExtra("string2");
        String[] day3Strings = intent.getStringArrayExtra("string3");


        for (int i = 0; i < day1Strings.length; i++) {
            day1List.add(day1Strings[i]);
        }
        for (int i = 0; i < day2Strings.length; i++) {
            day2List.add(day2Strings[i]);
        }
        for (int i = 0; i < day3Strings.length; i++) {
            day3List.add(day3Strings[i]);
        }



        //드래그 받는 레이아웃들
        //TODO 해야할것들 뭐냐면 여기 밑에 한줄이랑
        dayLayout1 = (LinearLayout) findViewById(R.id.firstLine);
        dayLayout1.setTag("day1");
        dayLayout1.setOnDragListener(new MyDragListener());

        //레이아웃 터치리스너!
        dayLayout1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                OneDaySend oneDaySend = new OneDaySend();
                Intent intent = new Intent(DragActivity.this, JourneyDayMain.class);
                String[] myStrings = new String[day1List.size()];
                for(int i = 0 ; i< day1List.size(); i++) {
                    Log.e("myString", day1List.get(i));
                    myStrings[i] = day1List.get(i);
                    oneDaySend.spot.add(day1List.get(i));
                }
                ClickTheDateCommunication(oneDaySend,"1",myStrings);
                //startActivity(intent);
            }
        });

        //테스트용1 TODO 이거 넘겨야되요.
        addCityFromList(day1List, dayLayout1);

        dayLayout2 = (LinearLayout)findViewById(R.id.secondLine);
        dayLayout2.setTag("day2");
        dayLayout2.setOnDragListener(new MyDragListener());

        dayLayout2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(DragActivity.this, JourneyDayMain.class);
                OneDaySend oneDaySend = new OneDaySend();
                String[] myStrings = new String[day2List.size()];
                for (int i = 0; i < day2List.size(); i++) {  //장소이름으로 보내기
                    Log.e("myString", day2List.get(i));
                    myStrings[i] = day2List.get(i);
                    oneDaySend.spot.add(day2List.get(i));
                }
                ClickTheDateCommunication(oneDaySend,"2",myStrings);


            }
        });

        //테스트용2
        addCityFromList(day2List, dayLayout2);

        dayLayout3 = (LinearLayout) findViewById(R.id.thirdLine);
        dayLayout3.setTag("day3");
        dayLayout3.setOnDragListener(new MyDragListener());

        dayLayout3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(DragActivity.this, JourneyDayMain.class);
                OneDaySend oneDaySend = new OneDaySend();
                String[] myStrings = new String[day3List.size()];
                for (int i = 0; i < day3List.size(); i++) {  //장소이름으로 보내기
                    Log.e("myString", day3List.get(i));
                    myStrings[i] = day3List.get(i);
                    oneDaySend.spot.add(day3List.get(i));
                }
                ClickTheDateCommunication(oneDaySend,"3",myStrings);

            }
        });
        addCityFromList(day3List, dayLayout3);

        dayLayout4 = (LinearLayout) findViewById(R.id.fourthLine);
        dayLayout4.setTag("day4");
        dayLayout4.setOnDragListener(new MyDragListener());

        dayLayout4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(DragActivity.this, JourneyDayMain.class);
                OneDaySend oneDaySend = new OneDaySend();
                String[] myStrings = new String[day4List.size()];
                for (int i = 0; i < day4List.size(); i++) {  //장소이름으로 보내기
                    Log.e("myString", day4List.get(i));
                    myStrings[i] = day4List.get(i);
                    oneDaySend.spot.add(day4List.get(i));
                }
                ClickTheDateCommunication(oneDaySend,"4",myStrings);

            }
        });

        trashCan = (LinearLayout) findViewById(R.id.trashCan);
        trashCan.setTag("trash");
        trashCan.setOnDragListener(new MyDragListener());

        //리싸이클러뷰 "모야"
        recyclerView.setTag("moya");
        recyclerView.setOnDragListener(new MyDragListener());

        //final CityListAdapter cityListAdapter = new CityListAdapter(cityDatas, getApplicationContext());

        //테스트용 임시데이터로 뉴욕을 넣어놓고 통신을 해보았다.
        final CityData tempData = new CityData();
        tempData.city = "뉴욕";

        Call<List<CityData>> soyoungCall = networkService.requestSubspot(tempData);
        soyoungCall.enqueue(new Callback<List<CityData>>() {
            @Override
            public void onResponse(Call<List<CityData>> call, Response<List<CityData>> response) {
                if (response.isSuccessful()) {
                    List<CityData> temp = response.body();

                    cityListAdapter = new ScheduleAdapter(temp, getApplicationContext());
                    recyclerView.setAdapter(cityListAdapter);

                }
            }

            @Override
            public void onFailure(Call<List<CityData>> call, Throwable t) {

            }
        });


        savebtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                saveDialog.show();
            }
        });


    }



    private  void addCityFromList(List<String> listFromServer, LinearLayout container){

        for(int i = 0 ; i < listFromServer.size(); i++){

            View layout2 = LayoutInflater.from(this).inflate(R.layout.new_test_layout, container, false);

            TextView tv = (TextView) layout2.findViewById(R.id.city_name_tv);

            tv.setText(listFromServer.get(i));

            ImageView imageview = new ImageView(this);
            imageview.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, 2, 1));
            imageview.setBackgroundColor(Color.WHITE);

            layout2.setTag(listFromServer.get(i));

            //TODO 터치리스너 -> 여행당일페이지에선 여기 제외(드래그니까)
            layout2.setOnTouchListener(new MyTouchListener());

            container.addView(imageview);
            container.addView(layout2);

        }

    }
    //데이리스트초기화용용
    private  void addCityFromList(List<String> listFromServer, LinearLayout container, List<String> daylist){

        for(int i = 0 ; i < listFromServer.size(); i++){

            View layout2 = LayoutInflater.from(this).inflate(R.layout.new_test_layout, container, false);

            TextView tv = (TextView) layout2.findViewById(R.id.city_name_tv);

            tv.setText(listFromServer.get(i));

            ImageView imageview = new ImageView(this);
            imageview.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, 2, 1));
            imageview.setBackgroundColor(Color.WHITE);

            layout2.setTag(listFromServer.get(i));
            layout2.setOnTouchListener(new MyTouchListener());


            container.addView(imageview);
            container.addView(layout2);


            daylist.add(listFromServer.get(i));

        }

    }

    private final class MyTouchListener implements OnTouchListener {


        public boolean onTouch(View view, MotionEvent motionEvent) {
            if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {

                ClipData data = ClipData.newPlainText("", "");

                DragShadowBuilder shadowBuilder = new DragShadowBuilder(
                        view);
                view.startDrag(data, shadowBuilder, view, 0);
                view.setVisibility(View.INVISIBLE);

                return true;
            } else {
                return false;
            }
        }
    }

    class MyDragListener implements OnDragListener {
        Drawable enterShape = getResources().getDrawable(
                R.drawable.shape_droptarget);
        Drawable normalShape = getResources().getDrawable(R.drawable.shape);

        @Override
        public boolean onDrag(View v, DragEvent event) {
            int action = event.getAction();
            switch (event.getAction()) {
                case DragEvent.ACTION_DRAG_STARTED:
                    // do nothing
                    break;
                case DragEvent.ACTION_DRAG_ENTERED:
                    v.setBackgroundDrawable(enterShape);
                    break;
                case DragEvent.ACTION_DRAG_EXITED:
                    v.setBackgroundDrawable(normalShape);
                    Log.d("들어왓어요", "어디가");
                    break;
                case DragEvent.ACTION_DROP:



                    String tempName = (String) v.getTag();
                    //1. 이전에 있던 뷰에서 삭제
                    View view = (View) event.getLocalState();

                    if( tempName == "moya") {
                        view.setVisibility(View.VISIBLE);
                        return true;
                    }
                    //이벤트가 일어난 곳의 좌표
                    float X = event.getX();
                    float Y = event.getY();

                    String tempTag2 = (String)view.getTag();
                    Log.d("하하", "X " + (int) X + "Y " + (int) Y);
                    ViewGroup owner = (ViewGroup) view.getParent();
                    String tempTag = (String) owner.getTag();
                    Log.d("상익", String.valueOf(tempTag2));
                    Log.d("오호", String.valueOf(day1List));

                    if(tempTag == "day1"){
                        day1List.remove(view.getTag());
                        Log.d("오호2", String.valueOf(day1List));
                    } else if (tempTag == "day2"){
                        day2List.remove(view.getTag());
                    } else if (tempTag == "day3"){
                        day3List.remove(view.getTag());
                    } else if (tempTag == "day4"){
                        day4List.remove(view.getTag());
                    }


                    //옆에있는 선도 대려가세요! TODO 수정필요 정확하지않아 에러발생가능
                    int sangik = ((ViewGroup) view.getParent()).indexOfChild(view);
                    owner.removeView(view);

                    String tempT = (String) owner.getTag();
                    if(tempT !="moya") {
                        if(owner.getChildCount() >= 3){
                            owner.removeViewAt(sangik-1);
                        }
                    }


                    LinearLayout container = (LinearLayout) v;
                    String popo = (String) container.getTag();
                    //2. 이동한 새로운 컨테이너에 추가


                    //위치파악
                    String myback = calculatePosition(container, X);

                    if(popo == "day1"){

                        if(myback == "없다"){
                            day1List.add((String) view.getTag());
                        } else {
                            int tempIndex = day1List.indexOf(myback);
                            day1List.add(tempIndex, (String) view.getTag());
                        }

                        container.removeViewsInLayout(1,container.getChildCount()-1);

                        addCityFromList(day1List, container);

                    } else if (popo == "day2"){
                        if(myback == "없다"){
                            day2List.add((String) view.getTag());
                        } else {
                            int tempIndex = day2List.indexOf(myback);
                            day2List.add(tempIndex, (String) view.getTag());
                        }

                        container.removeViewsInLayout(1,container.getChildCount()-1);
                        addCityFromList(day2List, container);

                    } else if (popo == "day3"){
                        if(myback == "없다"){
                            day3List.add((String) view.getTag());
                        } else {
                            int tempIndex = day3List.indexOf(myback);
                            day3List.add(tempIndex, (String) view.getTag());
                        }
                        container.removeViewsInLayout(1,container.getChildCount()-1);

                        addCityFromList(day3List, container);

                    } else if (popo == "day4"){
                        if(myback == "없다"){
                            day4List.add((String) view.getTag());
                        } else {
                            int tempIndex = day4List.indexOf(myback);
                            day4List.add(tempIndex, (String) view.getTag());
                        }

                        container.removeViewsInLayout(1,container.getChildCount()-1);

                        addCityFromList(day4List, container);

                    } else if( popo == "trash"){
                        Log.d("최종1일리스트", String.valueOf(day1List));
                        Log.d("최종2일리스트", String.valueOf(day2List));
                        Log.d("최종3일리스트", String.valueOf(day3List));
                        Log.d("최종4일리스트", String.valueOf(day4List));
                        view.setVisibility(View.VISIBLE);
                        break;
                    } else {

                        view.setVisibility(View.VISIBLE);
                        return true;
                    }


                    view.setVisibility(View.VISIBLE);


                    Log.d("최종1일리스트", String.valueOf(day1List));
                    Log.d("최종2일리스트", String.valueOf(day2List));
                    Log.d("최종3일리스트", String.valueOf(day3List));
                    Log.d("최종4일리스트", String.valueOf(day4List));


                    break;
                case DragEvent.ACTION_DRAG_ENDED:
                    v.setBackgroundDrawable(normalShape);
                default:
                    break;
            }
            return true;
        }

        public String calculatePosition(LinearLayout container, float X){

            Log.d("왜 갯수몇갠데", String.valueOf(container.getChildCount()));
            for(int i = 0; i< container.getChildCount(); i++){
                if(container.getChildAt(i).getTag() != null){
                    Log.d("자식들의 좌표값", String.valueOf(container.getChildAt(i).getX()));
                    float temp =  container.getChildAt(i).getX();
                    if(X < temp) {

                        return (String) container.getChildAt(i).getTag();
                    }
                }
            }
            return "없다";
        }
    }

    private void updateDisplay(int year,int month,int day)
    {
        mDateDisplay.setText(new StringBuilder()
                .append(year).append("/")
                .append(month + 1).append("/")
                .append(day));

        //여행 시작     // 여행 끝
        Log.d("mDateDisplay : ",mDateDisplay.getText().toString());
        Log.d("mDateDisplay : ",mDateDisplay2.getText().toString());
        Log.d("equal",""+mDateDisplay.getText().toString().equals("여행 끝"));
        if(!(mDateDisplay.getText().toString().equals("여행 시작")) && !(mDateDisplay2.getText().toString().equals("여행 끝"))){
            Log.d("equal","들어왔니");
            String[] dateSplitArray=mDateDisplay2.getText().toString().split("/");
            int[] endday=new int[3];
            for(int i=0;i<dateSplitArray.length;i++){
                endday[i]=Integer.parseInt(dateSplitArray[i]);
            }
            Log.d("dayday",""+year);
            Log.d("dayday",""+month);
            Log.d("dayday",""+day);
            Log.d("dayday","end: "+endday[0]*1000+endday[1]*10+endday[2]);
            Log.d("dayday",""+year*1000+month*10+day);
            if((endday[0]*1000+endday[1]*10+endday[2]) - (year*1000+month*10+day) < 0){
                Log.d("equal","들어왔니2");
                Toast.makeText(getApplicationContext(), "출국일 이후의 날짜만 선택해주세요!", Toast.LENGTH_SHORT).show();;
                mDateDisplay.setText("여행 시작");
                mDateDisplay2.setText("여행 끝");
            }

        }
    }

    private void updateDisplay2(int year,int month,int day)
    {
        mDateDisplay2.setText(new StringBuilder()
                .append(year).append("/")
                .append(month + 1).append("/")
                .append(day));

        //여행 시작     // 여행 끝
        if(!mDateDisplay.getText().toString().equals("여행 시작") && !mDateDisplay2.getText().toString().equals("여행 끝")){
            String[] dateSplitArray=mDateDisplay.getText().toString().split("/");
            int[] startday=new int[3];
            for(int i=0;i<dateSplitArray.length;i++){
                startday[i]=Integer.parseInt(dateSplitArray[i]);
            }
            Log.d("dayday",""+year);
            Log.d("dayday",""+month);
            Log.d("dayday",""+day);
            Log.d("dayday","start: "+startday[0]*1000+startday[1]*10+startday[2]);
            Log.d("dayday",""+year*1000+month*10+day);
            if((year*1000+month*10+day)-(startday[0]*1000+startday[1]*10+startday[2]) < 0){
                Toast.makeText(getApplicationContext(), "출국일 이후의 날짜만 선택해주세요!", Toast.LENGTH_SHORT).show();;
                mDateDisplay.setText("여행 시작");
                mDateDisplay2.setText("여행 끝");
            }

        }
    }

    private DatePickerDialog.OnDateSetListener mDateSetListener =
            new DatePickerDialog.OnDateSetListener() {

                @Override
                public void onDateSet(DatePicker view, int year, int monthOfYear,
                                      int dayOfMonth) {
//                    // TODO Auto-generated method stub
//                    Log.d("year","year mYear : "+year+mYear);                  // year 2017
//                    Log.d("month","monthOfYear mMonth : "+monthOfYear+" "+mMonth);           // month 0
//                    Log.d("day","dayOfMonth mDay : "+dayOfMonth+" "+mDay);        //dayOfMonth =  현재 클릭한 날짜  mDay = 바로 직전에 클릭한 날짜
//                    int rmYear=mYear*1000;
//                    int rmMonth=mMonth*10;
//                    int selectDay=rmYear+rmMonth+mDay;
//                    Log.d("view : ",view.toString());
//
//                    if (mYear > year) {
//                        Toast.makeText(getApplicationContext(), "출국일 이후의 날짜만 선택해주세요!", Toast.LENGTH_SHORT).show();
//                        return;
//                    }
//                    else if (mYear == year) {
//                        if (mMonth > monthOfYear) {
//                            Toast.makeText(getApplicationContext(), "출국일 이후의 날짜만 선택해주세요!", Toast.LENGTH_SHORT);
//                            return;
//                        }
//                        else if (mMonth == monthOfYear) {
//                            if (mDay >= dayOfMonth) {
//                                Toast.makeText(getApplicationContext(), "출국일 이후의 날짜만 선택해주세요!", Toast.LENGTH_SHORT);
//                                return;
//                            }
//                        }
//                    }

//                    mYear = year;
//                    mMonth = monthOfYear;
//                    mDay = dayOfMonth;

                    if(cnt == 0) {
                        updateDisplay(year,monthOfYear,dayOfMonth);
                        isCheck = true;
                    }
                    else
                        updateDisplay2(year,monthOfYear,dayOfMonth);

                }
            };

    @Override
    protected Dialog onCreateDialog(int id)
    {
        switch(id)
        {
            case DATE_DIALOG_ID:
                return new DatePickerDialog(this, AlertDialog.THEME_DEVICE_DEFAULT_DARK, mDateSetListener, mYear, mMonth, mDay);
        }
        return null;
    }

    public void ClickTheDateCommunication(OneDaySend oneDaySend, final String day, final String[] myStrings){
        Call<ArrayList<OneDayResult>> jiwongKo = networkService.requestLocation(oneDaySend);
        jiwongKo.enqueue(new Callback<ArrayList<OneDayResult>>() {
            @Override
            public void onResponse(Call<ArrayList<OneDayResult>> call, Response<ArrayList<OneDayResult>> response) {
                ArrayList<OneDayResult> list_item = response.body();
                OneDayResultPutter result = OneDayResultPutter.getInstance();
                result.results = list_item;
                Intent intent = new Intent(getApplicationContext(),JourneyDayMain.class);
                intent.putExtra("days",day);
                intent.putExtra("strings", myStrings);
                startActivity(intent);
            }

            @Override
            public void onFailure(Call<ArrayList<OneDayResult>> call, Throwable t) {

            }
        });
    }

}