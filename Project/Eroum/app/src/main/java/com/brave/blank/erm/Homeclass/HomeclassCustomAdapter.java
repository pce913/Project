package com.brave.blank.erm.Homeclass;

import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import com.brave.blank.erm.R;

import java.util.ArrayList;

/**
 * Created by jeonyongjin on 2016. 7. 29..
 */
public class HomeclassCustomAdapter extends BaseAdapter {
    private ArrayList<HomeclassList> listViewItemList = new ArrayList<HomeclassList>();
    private LayoutInflater inflater = null;
    TextView confirmTextView;

    public HomeclassCustomAdapter(Context c, ArrayList<HomeclassList> arr) {
        this.listViewItemList = arr;
        inflater = (LayoutInflater) c.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
    }

    ;

    public void setItemDatas(ArrayList<HomeclassList> itemDatas) {
        this.listViewItemList = itemDatas;
        this.notifyDataSetChanged();
    }

    @Override
    public int getCount() {
        return listViewItemList.size();
    }

    @Override
    public Object getItem(int position) {
        return listViewItemList.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }


    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        final int pos = position;
        final Context context = parent.getContext();

        if (convertView == null) {
            LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            convertView = inflater.inflate(R.layout.homeclasslist_item, parent, false);
        }

        TextView dateTextView = (TextView) convertView.findViewById(R.id.date);
        TextView sectionTextView = (TextView) convertView.findViewById(R.id.section);
        confirmTextView = (TextView) convertView.findViewById(R.id.confirm);
        TextView questionTextView = (TextView) convertView.findViewById(R.id.question);
//        Button confirmButton = (Button) convertView.findViewById(R.id.confirm);

        HomeclassList homeclassList = listViewItemList.get(position);

        dateTextView.setText(homeclassList.getDate());
        sectionTextView.setText(homeclassList.getsection());
        confirmTextView.setText(homeclassList.getConfirmsubmit());
        confirmTextView.setTextColor(Color.TRANSPARENT);

        if (homeclassList.getConfirmsubmit() == "미제출") {
            confirmTextView.setBackgroundResource(R.drawable.ic_submit_x);
            questionTextView.setText("과제를 제출해주세요");
        } else {
            confirmTextView.setBackgroundResource(R.drawable.ic_submit_o);
            questionTextView.setText(homeclassList.getQuestion());
        }
        return convertView;
    }
}
