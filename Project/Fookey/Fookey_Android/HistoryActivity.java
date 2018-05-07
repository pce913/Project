package com.smu.cs.fookey;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class HistoryActivity extends AppCompatActivity {

    private List<FoodData> foodDataList = new ArrayList<>();
    private RecyclerView foodDataListView;
    private RecyclerView.LayoutManager foodListLayoutManager;
    private FoodListAdapter foodListAdapter;
    private DataBaseHandler dbHandler;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_history);

        dbHandler = DataBaseHandler.getInstance(this);
        foodDataListView = (RecyclerView)findViewById(R.id.list_result);

        initializationData();
        initializationListView();
    }

    private void initializationData() {

        List<FoodData> foodDatas = dbHandler.getDataList();
        //데이터 로드시 사진이 없다거나 하면 DB 에서 삭제하기
        for(FoodData data : foodDatas){
            File file = new File(data.getPath());
            if(file.exists()){
                this.foodDataList.add(data);
            }
            else{
                DataBaseHandler.getInstance(this).deleteData(data);
            }
        }
    }
    private void initializationListView() {
        foodListLayoutManager = new LinearLayoutManager(this);
        foodDataListView.setLayoutManager(foodListLayoutManager);
        if(foodDataList.size() != 0){
            foodListAdapter = new FoodListAdapter(foodDataList);
            foodDataListView.setAdapter(foodListAdapter);
        }
    }
}
