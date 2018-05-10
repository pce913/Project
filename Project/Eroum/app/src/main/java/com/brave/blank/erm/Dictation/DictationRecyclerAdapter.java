package com.brave.blank.erm.Dictation;

import android.annotation.TargetApi;
import android.content.Context;
import android.os.Build;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.brave.blank.erm.R;

import java.util.List;

/**
 * Created by jeonyongjin on 2016. 8. 7..
 */
public class DictationRecyclerAdapter extends  RecyclerView.Adapter<DictationRecyclerAdapter.ViewHolder>{
public View view;
private Context context;
private List<DictationList> dictationitems;
        int item_layout;

public void append(DictationList dictationList){
        this.dictationitems.add(0,dictationList);
        this.notifyDataSetChanged();
        }

public DictationRecyclerAdapter(List<DictationList> dictationitem, Context context, int item_layout){
        super();
        this.dictationitems = dictationitem;
        this.context = context;
        this.item_layout = item_layout;
        }

public void setSource(List<DictationList> dictationitem){
        this.dictationitems = dictationitem;
        this.notifyDataSetChanged();
        }
@Override
public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View v= LayoutInflater.from(parent.getContext()).inflate(R.layout.dictation_item, parent, false);
        return new ViewHolder(v);
        }
@TargetApi(Build.VERSION_CODES.JELLY_BEAN)
@Override
public void onBindViewHolder(ViewHolder holder, int position){
final DictationList dictationList = dictationitems.get(position);

        holder.date.setText(dictationList.getDictation_date());
        holder.teacher_id.setText(dictationList.getTeacher_id());
        holder.dictation_answer.setText(dictationList.getDictation_answer());
        holder.submit_answer.setText(dictationList.getSubmit_answer());
        holder.answer_rate.setText(dictationList.getDictation_answer_rate());
        holder.playnum.setText(dictationList.getDictation_playnum());
        }

@Override
public int getItemCount() {
        return this.dictationitems == null? 0:this.dictationitems.size();
        }

public class ViewHolder extends RecyclerView.ViewHolder {
    //public View views;
    public TextView date;
    public TextView teacher_id;
    public TextView dictation_answer;
    public TextView submit_answer;
    public TextView answer_rate;
    public TextView playnum;

    public ViewHolder(View itemView) {
        super(itemView);

        //views = itemView.findViewById(R.id.cardview);
        date = (TextView) itemView.findViewById(R.id.dictation_date);
        teacher_id = (TextView)itemView.findViewById(R.id.d_teacher_id);
        dictation_answer = (TextView)itemView.findViewById(R.id.dictation_answer);
        submit_answer = (TextView) itemView.findViewById(R.id.submit_answer);
        answer_rate = (TextView)itemView.findViewById(R.id.dictation_answer_rate);
        playnum = (TextView)itemView.findViewById(R.id.dictation_playnum);
    }
}
}
