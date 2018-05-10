package com.brave.blank.erm.StoredExercise;

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
public class StoredExerciseCustomAdapter extends BaseAdapter {
    private ArrayList<StoredExerciseList> listViewItemList = new ArrayList<StoredExerciseList>();
    private LayoutInflater inflater = null;

    public StoredExerciseCustomAdapter(Context c, ArrayList<StoredExerciseList> arr){
        this.listViewItemList = arr;
        inflater = (LayoutInflater)c.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
    };
    public void setItemDatas(ArrayList<StoredExerciseList> exerciseDatas){
        this.listViewItemList = exerciseDatas;
        this.notifyDataSetChanged();
    }
    @Override
    public int getCount(){
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
            convertView = inflater.inflate(R.layout.storedexerciselist_item, parent, false);
        }

        TextView sectionTextView = (TextView) convertView.findViewById(R.id.section1);
        TextView dateTextView = (TextView) convertView.findViewById(R.id.date1);
        TextView sentenceTextView = (TextView) convertView.findViewById(R.id.sentence);

        StoredExerciseList storedExerciseList = listViewItemList.get(position);

        sectionTextView.setText(storedExerciseList.getSection());
        dateTextView.setText(storedExerciseList.getDate());
        sentenceTextView.setText(storedExerciseList.getExercise_sentence());
        return convertView;
    }
}
