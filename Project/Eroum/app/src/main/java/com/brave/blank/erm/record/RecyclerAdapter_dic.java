package com.brave.blank.erm.record;

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
 * Created by IT on 2016-07-18.
 */
public class RecyclerAdapter_dic extends RecyclerView.Adapter<RecyclerAdapter_dic.ViewHolder>{
    public View view;
    private Context context;
    private List<List_item_dictation> items;
    int item_layout;

    public void append(List_item_dictation list) {
        this.items.add(0, list);
        this.notifyDataSetChanged();
    }

    // 생성자
    public RecyclerAdapter_dic(List<List_item_dictation> items, Context context, int item_layout) {
        super();
        this.items=items;
        this.context=context;
        this.item_layout=item_layout;
    }

    public void setSource(List<List_item_dictation> items) {
        this.items = items;
        this.notifyDataSetChanged();
    }

    // 필수로 Generate 되어야 하는 메소드 1 : 새로운 뷰 생성
    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View v= LayoutInflater.from(parent.getContext()).inflate(R.layout.dictation_item, parent, false);
        return new ViewHolder(v);
    }

    // 필수로 Generate 되어야 하는 메소드 2 : ListView의 getView 부분을 담당하는 메소드
    @TargetApi(Build.VERSION_CODES.JELLY_BEAN)

    @Override
    public void onBindViewHolder(ViewHolder holder, int position) {
        final List_item_dictation item=items.get(position);


        // 이부분에서 setting을 다시 해줘야겠지 민주야


        holder.date.setText(item.getDate());
        holder.teacher_id.setText(String.valueOf(item.getTeacher_id()));
        holder.answer.setText(item.getAnswer());
        holder.submitanswer.setText(item.getQuestion());
        holder.answer_rate.setText(String.valueOf(item.getRate()));
        holder.playnum.setText(String.valueOf(item.getPlay_count()));
    }//dictation_date, teacher_id, dictation_answer, dictation_answer_rate, dictation_playnum;

    // 필수로 Generate 되어야 하는 메소드 3
    @Override
    public int getItemCount() {
        return this.items == null ? 0 : this.items.size();
    }

    public class ViewHolder extends RecyclerView.ViewHolder {
        //public View views;

        //필드추가하는거 잊지마라 민주야

        public TextView date;
        public TextView teacher_id;
        public TextView answer;
        public TextView answer_rate;
        public TextView playnum;
        public TextView submitanswer;

        public ViewHolder(View itemView) {

            super(itemView);

            //여기서 추가한 필드들 xml이랑 이어주는거 잊지마라
            date = (TextView) itemView.findViewById(R.id.dictation_date);
            teacher_id = (TextView)itemView.findViewById(R.id.d_teacher_id);
            answer = (TextView)itemView.findViewById(R.id.dictation_answer);
            submitanswer = (TextView)itemView.findViewById(R.id.submit_answer);
            answer_rate = (TextView)itemView.findViewById(R.id.dictation_answer_rate);
            playnum = (TextView)itemView.findViewById(R.id.dictation_playnum);
        }
    }
}