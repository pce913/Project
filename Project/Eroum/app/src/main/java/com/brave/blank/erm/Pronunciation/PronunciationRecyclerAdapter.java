package com.brave.blank.erm.Pronunciation;

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
public class PronunciationRecyclerAdapter  extends RecyclerView.Adapter<PronunciationRecyclerAdapter.ViewHolder>{
    public View view;
    private Context context;
    private List<PronunciationList> pronunciationListitems;
    int item_layout;

    public void append(PronunciationList pronunciationList){
        this.pronunciationListitems.add(0,pronunciationList);
        this.notifyDataSetChanged();
    }

    public PronunciationRecyclerAdapter(List<PronunciationList> pronunciationitem, Context context, int item_layout){
        super();
        this.pronunciationListitems = pronunciationitem;
        this.context = context;
        this.item_layout = item_layout;
    }

    public void setSource(List<PronunciationList> pronunciationitem){
        this.pronunciationListitems = pronunciationitem;
        this.notifyDataSetChanged();
    }
    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View v= LayoutInflater.from(parent.getContext()).inflate(R.layout.pronunciationlist_item, parent, false);
        return new ViewHolder(v);
    }
    @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
    @Override
    public void onBindViewHolder(ViewHolder holder, int position){
        final PronunciationList pronunciationList = pronunciationListitems.get(position);

        holder.date.setText(pronunciationList.getPronunciation_date());
        holder.teacher_id.setText(pronunciationList.getp_Teacher_id());
        holder.pronunciation_answer.setText(pronunciationList.getPronunciation_answer());
        holder.answer_rate.setText(pronunciationList.getPronunciation_answer_rate());
        holder.playnum.setText(pronunciationList.getPronunciation_playnum());
    }

    @Override
    public int getItemCount() {
        return this.pronunciationListitems == null? 0:this.pronunciationListitems.size();
    }

    public class ViewHolder extends RecyclerView.ViewHolder {
        //public View views;
        public TextView date;
        public TextView teacher_id;
        public TextView pronunciation_answer;
        public TextView answer_rate;
        public TextView playnum;

        public ViewHolder(View itemView) {
            super(itemView);

            //views = itemView.findViewById(R.id.cardview);
            date = (TextView) itemView.findViewById(R.id.pronunciation_date);
            teacher_id = (TextView)itemView.findViewById(R.id.p_teacher_id);
            pronunciation_answer = (TextView)itemView.findViewById(R.id.pronunciation_answer);
            answer_rate = (TextView)itemView.findViewById(R.id.pronunciation_answer_rate);
            playnum = (TextView)itemView.findViewById(R.id.pronunciation_playnum);
        }
    }
}
