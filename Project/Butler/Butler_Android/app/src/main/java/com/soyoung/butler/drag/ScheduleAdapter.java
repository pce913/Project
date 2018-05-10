package com.soyoung.butler.drag;

import android.content.ClipData;
import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.bumptech.glide.Glide;
import com.soyoung.butler.R;

import java.util.List;

/**
 * Created by baesangik on 2017. 1. 3..
 */

public class ScheduleAdapter extends RecyclerView.Adapter<ScheduleAdapter.ViewHolder> {

    private Context context;
    public View view;



    List<CityData> cityDatas;


    public ScheduleAdapter(List<CityData> cityDatas, Context context){
        super();

        this.cityDatas = cityDatas;
        this.context = context;
    }


    public void setSource(List<CityData> cityDatas) {
        this.cityDatas = cityDatas;
        this.notifyDataSetChanged();
    }

    public void setRemove(){
        this.cityDatas = null;
        this.notifyDataSetChanged();
    }

    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View v = LayoutInflater.from(parent.getContext()).inflate(R.layout.grid_item, parent, false);
        ViewHolder viewHolder = new ViewHolder(v);
        return viewHolder;
    }

    @Override
    public void onBindViewHolder(ViewHolder holder, final int position) {

        //해당 position의 카드 객체 대입
        CityData cityData =  cityDatas.get(position);


        holder.cityTextView.setText(cityData.spot);

//        holder.nick.setText(positionBoardData.getUser_nick());
        Glide.with(holder.cityImageView.getContext()).load(cityData.sight_image_url).into(holder.cityImageView);

        holder.view.setTag(cityData.spot);

        holder.view.setOnTouchListener(new MyTouchListener());


    }

    @Override
    public int getItemCount() {
        return cityDatas.size();
    }

    class ViewHolder extends RecyclerView.ViewHolder{
        public View view;
        public TextView cityTextView;
        public ImageView cityImageView;


        public ViewHolder(View itemView)  {
            super(itemView);

            view = (View) itemView.findViewById(R.id.item);
            cityTextView = (TextView) itemView.findViewById(R.id.grid_name);
            cityImageView = (ImageView) itemView.findViewById(R.id.grid_image);


        }
    }

    private final class MyTouchListener implements View.OnTouchListener {


        public boolean onTouch(View view, MotionEvent motionEvent) {
            if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {

                ClipData data = ClipData.newPlainText("", "");

                View.DragShadowBuilder shadowBuilder = new View.DragShadowBuilder(
                        view);
                view.startDrag(data, shadowBuilder, view, 0);
                view.setVisibility(View.INVISIBLE);

                return true;
            } else {
                return false;
            }
        }
    }

}
