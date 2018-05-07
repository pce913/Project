package com.brave.blank.erm.FinalConsonant;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import com.brave.blank.erm.R;

import java.util.ArrayList;

/**
 * Created by jeonyongjin on 2016. 8. 7..
 */
public class FinalConsonantCustomAdapter extends BaseAdapter{
    private ArrayList<String> fc_list = new ArrayList<>();
    private LayoutInflater inflater = null;

    public FinalConsonantCustomAdapter(Context c, ArrayList<String> arr){
        this.fc_list = arr;
        inflater = (LayoutInflater)c.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
    }
    public void setItemDatas(ArrayList<String> arr){
        this.fc_list = arr;
        this.notifyDataSetChanged();
    }
    @Override
    public int getCount(){
        return fc_list.size();
    }
    @Override
    public Object getItem(int position) {
        return fc_list.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }
    @Override
    public View getView(int position, View convertView, ViewGroup parent){
        final int pos = position;
        final Context context = parent.getContext();

        LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        convertView = inflater.inflate(R.layout.simple1, parent, false);

        TextView categoryView = (TextView) convertView.findViewById(R.id.text1);

        String item = fc_list.get(position);

        categoryView.setText(item);
        return convertView;
    }
}
