package com.soyoung.butler.select_spot;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.TextView;

import com.soyoung.butler.R;

import java.util.ArrayList;

/**
 * Created by user1 on 2017-01-04.
 */

public class RecyclerAdapter4 extends RecyclerView.Adapter<RecyclerAdapter4.ViewHoler> {
    static ArrayList<SelectedObject> alternative;
    Context context;
    static boolean[] count;
    public RecyclerAdapter4(ArrayList<SelectedObject> alternative,Context context){
        super();
        count = new boolean[alternative.size()];
        this.alternative = alternative;
        this.context = context;
        for (int i = 0; i < alternative.size(); i++) {
            count[i] = false;
        }
    }
    @Override
    public ViewHoler onCreateViewHolder(ViewGroup parent, int viewType) {
        return new RecyclerAdapter4.ViewHoler(LayoutInflater.from(parent.getContext()).inflate(R.layout.child,parent,false));
    }

    @Override
    public void onBindViewHolder(ViewHoler holder, int position) {
            holder.textView.setText(alternative.get(position).spot);
    }


    public void setAdapterItemList(ArrayList<SelectedObject> alternative) {
        this.alternative = alternative;
        notifyDataSetChanged();
    }

    @Override
    public int getItemCount() {
        return alternative.size();
    }

    public class ViewHoler extends RecyclerView.ViewHolder {
        CheckBox btn;
        TextView textView;
        public ViewHoler(View itemView) {
            super(itemView);
            btn = (CheckBox)itemView.findViewById(R.id.checkBox);
            textView = (TextView)itemView.findViewById(R.id.select_sight);
            btn.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
                @Override
                public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                    if (buttonView.getId() == R.id.checkBox) {
                        if (isChecked) {
                            btn.setBackgroundResource(R.drawable.selectedtravel_nocheck);
                            count[getPosition()] = true;
                        } else {
                            btn.setBackgroundResource(R.drawable.selectedtravel_check);
                            count[getPosition()] = false;
                        }
                    }
                }
            } );
        }

    }
    public static ArrayList<String> getCityNotChecked(){
        ArrayList<String> selectedObjects=new ArrayList<String>();
        for(int i=0;i<count.length;i++){
            if(count[i]==false){
                selectedObjects.add(alternative.get(i).city_sight_id);
            }
        }
        return selectedObjects;
    }
}
