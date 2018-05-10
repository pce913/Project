package com.smu.cs.fookey;

import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

/**
 * Created by LG on 2017-08-18.
 */

public class FoodDataHolder extends RecyclerView.ViewHolder{
    public ImageView image_food;
    public TextView text_category, text_date;
    public FoodDataHolder(View itemView) {
        super(itemView);
        image_food = (ImageView) itemView.findViewById(R.id.image_food);
        text_category = (TextView) itemView.findViewById(R.id.text_category);
        text_date = (TextView) itemView.findViewById(R.id.text_date);
    }
}
