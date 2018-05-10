package com.soyoung.butler.drag;

import android.content.ClipData;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.bumptech.glide.Glide;
import com.soyoung.butler.R;

import java.util.List;

/**
 * Created by baesangik on 2017. 1. 1..
 */

public class CityListAdapter extends BaseAdapter {
    List<CityData> cityDatas = null;
    LayoutInflater layoutInflater = null;
    Context ctx;

    public CityListAdapter(List<CityData> cityDatas, Context ctx) {
        this.cityDatas = cityDatas;
        this.ctx = ctx;
        layoutInflater = (LayoutInflater) ctx.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
    }

    @Override
    public int getCount() {
        return cityDatas != null ? cityDatas.size() : 0;
    }

    @Override
    public Object getItem(int position) {
        return(cityDatas != null && (position >= 0 && position < cityDatas.size()) ? cityDatas.get(position) : null);
    }

    @Override
    public long getItemId(int position) {
        return (cityDatas != null && (position >= 0 && position < cityDatas.size()) ? position : 0);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        ViewHolder viewHolder = new ViewHolder();

        if (convertView == null) {
            convertView = layoutInflater.inflate(R.layout.grid_item, parent, false);
            viewHolder.img_item = (ImageView)convertView.findViewById(R.id.grid_image);
            viewHolder.city_name = (TextView)convertView.findViewById(R.id.grid_name);

            convertView.setTag(viewHolder);// 태그달아주기
        }
        else {
            viewHolder = (ViewHolder)convertView.getTag(); //태그달린거 불러오기

        }

        CityData itemData_temp =  cityDatas.get(position);

        viewHolder.city_name.setText(itemData_temp.spot);

        //이미지 아직안함 Glide
        Glide.with(viewHolder.img_item.getContext()).load(itemData_temp.sight_image_url).into(viewHolder.img_item);

        convertView.setOnTouchListener(new MyTouchListener());
        return convertView;
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

    public class ViewHolder {

        ImageView img_item;
        TextView city_name;

    }
}
