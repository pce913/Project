package com.soyoung.butler.attraction;

import android.content.Context;
import android.content.Intent;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.ImageButton;
import android.widget.TextView;

import com.bumptech.glide.Glide;
import com.soyoung.butler.R;
import com.soyoung.butler.detail.DetailMain;

import java.util.ArrayList;

/**
 * Created by Soyoung on 17. 1. 1..
 */
public class RecyclerAdapter  extends RecyclerView.Adapter<RecyclerAdapter.ViewHoler> {
    EssentailCityID essential;
    static ArrayList<AttractionResult> adapterItemList;
    static boolean[] count;
    Context context;


    public RecyclerAdapter(ArrayList<AttractionResult> adapterItemList, Context context) {
        super();
        this.adapterItemList = adapterItemList;
        this.context = context;
        count = new boolean[adapterItemList.size()];

        for (int i = 0; i < adapterItemList.size(); i++) {
            count[i] = false;
        }
    }

    public void setAdapterItemList(ArrayList<AttractionResult> adapterItemList) {
        this.adapterItemList = adapterItemList;
        notifyDataSetChanged();
    }

    @Override
    public ViewHoler onCreateViewHolder(ViewGroup parent, int viewType) {
        Log.i("MyTag", "onCreateViewHolder");
        return new ViewHoler(LayoutInflater.from(parent.getContext()).inflate(R.layout.recycler_child,parent,false));
    }

    @Override
    public void onBindViewHolder(ViewHoler holder, final int position) {
        Log.i("MyTag", "onBindViewHolder, position : " + adapterItemList.get(0).sentence);
        try {
            essential = EssentailCityID.getInstance();
        } catch (Exception e) {
            e.printStackTrace();
        }
        Glide.with(context).load(adapterItemList.get(position).sight_image_url).into(holder.ibtn1);
        if (count[position]) {
    //        essential.essentials_city_sight_id[position] = adapterItemList.get(position).city_sight_id;
            holder.ibtn2.setBackgroundResource(R.drawable.aftercheck);
        }
        else {
      //      essential.essentials_city_sight_id[position] = "";
            holder.ibtn2.setBackgroundResource(R.drawable.beforecheck);
        }
        holder.textView.setText(adapterItemList.get(position).sentence);
        holder.textView2.setText(adapterItemList.get(position).spot);
        holder.ibtn1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(context, DetailMain.class);
                intent.putExtra("city_id",adapterItemList.get(position).city_sight_id);
                //Log.d("city_id : ",adapterItemList.get(position).city_sight_id);
                intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                context.startActivity(intent);
            }
        });
    }

    @Override
    public int getItemCount() {
        return adapterItemList.size();
    }

    public class ViewHoler extends RecyclerView.ViewHolder {
        TextView textView,textView2;
        ImageButton ibtn1;
        CheckBox ibtn2;

        public ViewHoler(final View itemView) {
            super(itemView);
            textView = (TextView) itemView.findViewById(R.id.description);
            textView2 = (TextView) itemView.findViewById(R.id.spot);
            ibtn1 = (ImageButton) itemView.findViewById(R.id.imageButton1);
            ibtn2 = (CheckBox) itemView.findViewById(R.id.imageButton2);
            ibtn2.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
                @Override
                public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                    if (buttonView.getId() == R.id.imageButton2) {
                        if (isChecked) {
                            count[getPosition()] = true;
                            ibtn2.setBackgroundResource(R.drawable.aftercheck);
                        } else {
                            count[getPosition()] = false;
                            ibtn2.setBackgroundResource(R.drawable.beforecheck);
                        }
                    }
                }
            } );

        }

        public void setTextView(String data) {
            textView.setText(data);
        }

    }
    public static ArrayList<String> getCityID(){
        ArrayList<String> essential_send=new ArrayList<String>();
        for(int i=0;i<count.length;i++){
            if(count[i]==true){
                essential_send.add(adapterItemList.get(i).city_sight_id);
            }
        }
        return essential_send;
    }

}
