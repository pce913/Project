package com.smu.cs.fookey;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.DisplayMetrics;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.Spinner;
import android.widget.TextView;

import com.github.mikephil.charting.charts.PieChart;
import com.github.mikephil.charting.data.PieData;
import com.github.mikephil.charting.data.PieDataSet;
import com.github.mikephil.charting.data.PieEntry;
import com.github.mikephil.charting.utils.ColorTemplate;

import java.io.File;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.StringTokenizer;

public class SpecificActivity extends AppCompatActivity implements AdapterView.OnItemSelectedListener {
    private ImageView image_food;
    private TextView text_foodName,text_foodCategory, text_foodCalorie, text_foodSafety;
    private TextView text_walkingTime, text_jumpRopeTime, text_bikeTime, text_fitnessTime, text_swimmingTime;
    private Spinner spinner_weight, spinner_walkingIntensity, spinner_jumpRopeIntensity, spinner_bikeIntensity, spinner_fitnessIntensity, spinner_swimmingIntensity;
    private PieChart chart_nutrient;
    private String imgPath;
    private List<String> description;
    private ArrayAdapter<CharSequence> adapter;
    private HashMap<String, String> walkdata, jumpRopedata, bikedata, fitnessdata, swimmingdata;
    private String walkingIntensity, ropeJumpIntensity, bikeIntensity, fitnessIntensity, swimmingIntesity;
    private int weight, walkingTime, jumpRopeTime, bikeTime, fitnessTime, swimmingTime;
    private double cal;
    private int width, height, flag;
    private DataBaseHandler dbHandler;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_specific);

        initData();

        setImage(imgPath);
        //if(description == null)
         //   Toast.makeText(this, "DES NULL", Toast.LENGTH_SHORT).show();
        //el/se
        //    Toast.makeText(this, "DES NOT NULL", Toast.LENGTH_SHORT).show();
        setText(description);
        setChart(description);
        setTable();
        if(flag == 1){
            dbHandler = DataBaseHandler.getInstance(this);
            SimpleDateFormat mformat = new SimpleDateFormat("yyyy-MM-dd", Locale.KOREA);
            Date date = new Date();
            dbHandler.insertData(new FoodData(description.get(0), imgPath, mformat.format(date)));
        }

        //History 를 통한 경우에는 데이터 추가 x Search 를 통한 경우에는 데이터 추가 o

        //dbHandler.insertData(new FoodData(description.getFood_name(), imgPath, mformat.format(date)));
        //Toast.makeText(this, mformat.format(date), Toast.LENGTH_SHORT).show();
    }

    private void initData(){


        image_food = (ImageView)findViewById(R.id.image_food);
        text_foodName = (TextView)findViewById(R.id.text_foodName);
        text_foodCategory = (TextView)findViewById(R.id.text_foodCategory);
        text_foodCalorie = (TextView)findViewById(R.id.text_foodCalorie);
        text_foodSafety = (TextView)findViewById(R.id.text_foodSafety);
        chart_nutrient = (PieChart)findViewById(R.id.chart_nutrient);

        text_walkingTime = (TextView)findViewById(R.id.text_walkingTime);
        text_jumpRopeTime = (TextView)findViewById(R.id.text_jumpRopeTime);
        text_bikeTime = (TextView)findViewById(R.id.text_bikeTime);
        text_fitnessTime = (TextView)findViewById(R.id.text_fitnessTime);
        text_swimmingTime = (TextView)findViewById(R.id.text_swimmingTime);

        spinner_weight = (Spinner)findViewById(R.id.spinner_weight);
        spinner_walkingIntensity = (Spinner)findViewById(R.id.spinner_walkingIntensity);
        spinner_jumpRopeIntensity = (Spinner)findViewById(R.id.spinner_jumpRopeIntensity);
        spinner_bikeIntensity = (Spinner)findViewById(R.id.spinner_bikeIntensity);
        spinner_fitnessIntensity = (Spinner)findViewById(R.id.spinner_fitnessIntensity);
        spinner_swimmingIntensity = (Spinner)findViewById(R.id.spinner_swimmingIntensity);

        walkdata = new HashMap<>();
        jumpRopedata = new HashMap<>();
        bikedata = new HashMap<>();
        fitnessdata = new HashMap<>();
        swimmingdata = new HashMap<>();

        walkdata.put("For walking", "2.0");
        walkdata.put("Slightly faster", "3.8");
        walkdata.put("Fast", "4.0");
        walkdata.put("Presto", "6.5");

        jumpRopedata.put("Slowly", "8.0");
        jumpRopedata.put("Usually", "10.0");
        jumpRopedata.put("Quickly", "12.0");

        bikedata.put("Lightly", "6.0");
        bikedata.put("Usually", "8.0");
        bikedata.put("Fast", "10.0");

        fitnessdata.put("Lightly", "3.85");
        fitnessdata.put("Usually", "5.5");
        fitnessdata.put("Hard", "8.25");

        swimmingdata.put("Slowly", "8.0");
        swimmingdata.put("Usually", "9.0");
        swimmingdata.put("Quickly", "11.0");

        Intent intent = getIntent();
        description = (List<String>) intent.getSerializableExtra("description");
        imgPath = intent.getStringExtra("path");
        flag  = intent.getIntExtra("flag", 0);

        DisplayMetrics dm = getApplicationContext().getResources().getDisplayMetrics();
        width = dm.widthPixels;
        height = dm.heightPixels;
    }
    private void setImage(String Path){
        //Log.i("PATH", Path);
        File imgFile = new  File(Path);
        if(imgFile.exists()) {
            BitmapFactory.Options opt = new BitmapFactory.Options();
            opt.inPreferredConfig = Bitmap.Config.RGB_565;
            opt.inSampleSize = 1;
            opt.inPurgeable = true;
            Bitmap src = BitmapFactory.decodeFile(imgFile.getAbsolutePath(), opt);
            Bitmap resize = Bitmap.createScaledBitmap(src, opt.outWidth, opt.outHeight, true);

            image_food.setImageBitmap(resize);
            image_food.getLayoutParams().height = image_food.getLayoutParams().width = width;
            image_food.setRotation(90);
        }
    }
    private void setText(List<String> textData){
        text_foodName.setText(textData.get(0));
        text_foodCategory.setText(textData.get(1));
        text_foodCalorie.setText(textData.get(2));
        text_foodSafety.setText("Nutrition Safety: " + textData.get(3));
    }
    private void setTableText(){
        text_walkingTime.setText(walkingTime + "min");
        text_jumpRopeTime.setText(jumpRopeTime + "min");
        text_bikeTime.setText(bikeTime + "min");
        text_fitnessTime.setText(fitnessTime + "min");
        text_swimmingTime.setText(swimmingTime + "min");
    }
    private void setTable(){   //테이블 셋팅을 하는 부분.
        StringTokenizer st = new StringTokenizer(description.get(2), " ");
        String calText = st.nextToken();
        st = new StringTokenizer(calText, "k");
        cal = Double.parseDouble(st.nextToken());

        adapter = ArrayAdapter.createFromResource(this, R.array.weightArray, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner_weight.setAdapter(adapter);

        adapter = ArrayAdapter.createFromResource(this, R.array.walkingArray, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner_walkingIntensity.setAdapter(adapter);

        adapter = ArrayAdapter.createFromResource(this, R.array.jumpRopeArray, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner_jumpRopeIntensity.setAdapter(adapter);

        adapter = ArrayAdapter.createFromResource(this, R.array.bikeArray, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner_bikeIntensity.setAdapter(adapter);

        adapter = ArrayAdapter.createFromResource(this, R.array.fitnessArray, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner_fitnessIntensity.setAdapter(adapter);

        adapter = ArrayAdapter.createFromResource(this, R.array.swimmingArray, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner_swimmingIntensity.setAdapter(adapter);

        spinner_weight.setOnItemSelectedListener(this);
        spinner_walkingIntensity.setOnItemSelectedListener(this);
        spinner_jumpRopeIntensity.setOnItemSelectedListener(this);
        spinner_bikeIntensity.setOnItemSelectedListener(this);
        spinner_fitnessIntensity.setOnItemSelectedListener(this);
        spinner_swimmingIntensity.setOnItemSelectedListener(this);

        //내가 추가한 부분
        weight = Integer.parseInt(spinner_weight.getAdapter().getItem(0).toString());
        walkingIntensity = spinner_walkingIntensity.getAdapter().getItem(0).toString();
        walkingTime = getEventTime(Double.parseDouble(walkdata.get(walkingIntensity)));
        ropeJumpIntensity = spinner_jumpRopeIntensity.getAdapter().getItem(0).toString();
        jumpRopeTime = getEventTime(Double.parseDouble(jumpRopedata.get(ropeJumpIntensity)));
        bikeIntensity = spinner_bikeIntensity.getAdapter().getItem(0).toString();
        bikeTime = getEventTime(Double.parseDouble(bikedata.get(bikeIntensity)));
        fitnessIntensity = spinner_fitnessIntensity.getAdapter().getItem(0).toString();
        fitnessTime = getEventTime(Double.parseDouble(fitnessdata.get(fitnessIntensity)));
        swimmingIntesity = spinner_swimmingIntensity.getAdapter().getItem(0).toString();
        swimmingTime = getEventTime(Double.parseDouble(swimmingdata.get(swimmingIntesity)));
        setTableText();
        //여기에 setTableText() 를 넣어줘야 할 것 같다.
    }
    private void setChart(List<String> chartData){
        ArrayList<PieEntry> entries = new ArrayList<>();
        entries.add(new PieEntry(Float.parseFloat(chartData.get(4)), "Carbohydrate"));
        entries.add(new PieEntry(Float.parseFloat(chartData.get(5)), "Protein"));
        entries.add(new PieEntry(Float.parseFloat(chartData.get(6)), "Fat"));


        PieDataSet dataSet = new PieDataSet(entries, "");
        dataSet.setSliceSpace(1f);
        dataSet.setValueTextSize(10f);
        dataSet.setColors(ColorTemplate.JOYFUL_COLORS);
        PieData data = new PieData(dataSet);

        chart_nutrient.setData(data);
        chart_nutrient.setDrawSliceText(false);
        chart_nutrient.animateY(1000);
        chart_nutrient.invalidate();

        chart_nutrient.getLayoutParams().height = width * 3 / 4;
        chart_nutrient.getLayoutParams().width = width * 3 / 4;

    }
    public int getEventTime(double intensity){
        return (int) Math.round(cal / ((3.5) * (1.0 / 200) * intensity * weight));
    }
    @Override
    public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {    //아이템을 선택했을때 호출되는 콜백함수
        switch (parent.getId()){
            case R.id.spinner_weight:
                weight = Integer.parseInt(spinner_weight.getAdapter().getItem(position).toString());
                walkingTime = getEventTime(Double.parseDouble(walkdata.get(walkingIntensity)));
                jumpRopeTime = getEventTime(Double.parseDouble(jumpRopedata.get(ropeJumpIntensity)));
                bikeTime = getEventTime(Double.parseDouble(bikedata.get(bikeIntensity)));
                fitnessTime = getEventTime(Double.parseDouble(fitnessdata.get(fitnessIntensity)));
                swimmingTime = getEventTime(Double.parseDouble(swimmingdata.get(swimmingIntesity)));
                break;
            case R.id.spinner_walkingIntensity:
                walkingIntensity = spinner_walkingIntensity.getAdapter().getItem(position).toString();
                walkingTime = getEventTime(Double.parseDouble(walkdata.get(walkingIntensity)));
                break;
            case R.id.spinner_jumpRopeIntensity:
                ropeJumpIntensity = spinner_jumpRopeIntensity.getAdapter().getItem(position).toString();
                jumpRopeTime = getEventTime(Double.parseDouble(jumpRopedata.get(ropeJumpIntensity)));
                break;
            case R.id.spinner_bikeIntensity:
                bikeIntensity = spinner_bikeIntensity.getAdapter().getItem(position).toString();
                bikeTime = getEventTime(Double.parseDouble(bikedata.get(bikeIntensity)));
                break;
            case R.id.spinner_fitnessIntensity:
                fitnessIntensity = spinner_fitnessIntensity.getAdapter().getItem(position).toString();
                fitnessTime = getEventTime(Double.parseDouble(fitnessdata.get(fitnessIntensity)));
                break;
            case R.id.spinner_swimmingIntensity:
                swimmingIntesity = spinner_swimmingIntensity.getAdapter().getItem(position).toString();
                swimmingTime = getEventTime(Double.parseDouble(swimmingdata.get(swimmingIntesity)));
                break;
            default:
                break;
        }
        setTableText();
    }

    @Override
    public void onNothingSelected(AdapterView<?> parent) {
    }
}
