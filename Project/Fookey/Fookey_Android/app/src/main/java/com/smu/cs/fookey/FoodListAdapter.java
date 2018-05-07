package com.smu.cs.fookey;

import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AlertDialog;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import com.smu.cs.fookey.Network.NetworkApi;

import java.io.File;
import java.util.List;
import java.util.StringTokenizer;

/**
 * Created by LG on 2017-08-18.
 */

public class FoodListAdapter extends RecyclerView.Adapter<FoodDataHolder> {
    private List<FoodData> dataList;
    private List<String> description;
    private NetworkApi networkApi;
    private void initNetworkApi(){networkApi=NetworkApi.getNetworkApi(); }
    public FoodListAdapter(List<FoodData> dataList) {
        this.dataList = dataList;
        initNetworkApi();
    }
    private ProgressDialog progDialog;

    private _Thread networkThread;
    private Context mContext;
    private String path;
    @Override
    public FoodDataHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.list_item, parent, false);
        mContext = view.getContext();
        final FoodDataHolder holder = new FoodDataHolder(view);
        view.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // 서버에서 받던지 내부 DB로 구성하든지 받긴 해야함
                final int position = holder.getAdapterPosition();
                String food_Name = dataList.get(position).getFood_name();
                // -> 이거로 network api사용해서 정보 가져옴? 내장 db가 나을 듯 한데...
                path = dataList.get(position).getPath();
                doNetworkOperation(v.getContext(), food_Name);
            }
        });
        view.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(final View v) {
                final int position = holder.getAdapterPosition();
                final String path = dataList.get(position).getPath();
                final String food_Name = dataList.get(position).getFood_name();
                final String date = dataList.get(position).getDate();
                AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(v.getContext());
                // AlertDialog 셋팅
                alertDialogBuilder
                        .setMessage("삭제하시겠습니까?")
                        .setCancelable(false)
                        .setPositiveButton("예",
                                new DialogInterface.OnClickListener() {
                                    public void onClick(DialogInterface dialog, int id) {
                                        // 프로그램을 종료한다
                                        DataBaseHandler.getInstance(v.getContext()).deleteData(new FoodData(position, food_Name, path, date));
                                        dialog.dismiss();
                                    }
                                })
                        .setNegativeButton("아니오",
                                new DialogInterface.OnClickListener() {
                                    public void onClick(
                                            DialogInterface dialog, int id) {
                                        // 다이얼로그를 취소한다
                                        dialog.cancel();
                                    }
                                });

                // 다이얼로그 생성
                AlertDialog alertDialog = alertDialogBuilder.create();
                // 다이얼로그 보여주기
                alertDialog.show();
                return false;
            }
        });
        return holder;
    }

    private void doNetworkOperation(Context context, final String foodName){
        progDialog = new ProgressDialog(context);

        progDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
        progDialog.setMessage("please wait....");
        networkThread = new _Thread(foodName);
        networkThread.start();
    }
    @Override
    public void onBindViewHolder(FoodDataHolder holder, int position) {

        FoodData foodData = dataList.get(position);
        holder.image_food.setImageResource(R.drawable.logo);
        File imgFile = new File(foodData.getPath());
        if (imgFile.exists()) {


            BitmapFactory.Options opt = new BitmapFactory.Options();
            opt.inPreferredConfig = Bitmap.Config.RGB_565;
            opt.inSampleSize = 1;
            opt.inPurgeable = true;
            Bitmap src = BitmapFactory.decodeFile(imgFile.getAbsolutePath(), opt);
            Bitmap resize = Bitmap.createScaledBitmap(src, opt.outWidth, opt.outHeight, true);

            holder.image_food.setImageBitmap(resize);
            holder.image_food.setRotation(90);
        }
        holder.text_category.setText(foodData.getFood_name());
        holder.text_date.setText(foodData.getDate());
    }
    @Override
    public int getItemCount() {
        return (dataList.size() > 0) ? dataList.size() : 0;
    }



    class _Thread extends Thread{
        private String foodName;
        public _Thread(String foodName){
            this.foodName = foodName;
        }
        @Override
        public void run() {
            super.run();
                //TODO : 시간이 걸리는 처리 삽입
            description = networkApi.sendSubAnswer(foodName);

            progDialog.dismiss();
            IntentHandler.historyToSpecific(mContext, description, path);
        }
    }
}
