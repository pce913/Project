package com.brave.blank.erm.Dictation;

/**
 * Created by jeonyongjin on 2016. 8. 7..
 */
public class DictationList {
    String dictation_date;
    String teacher_id;
    String dictation_answer;
    int dictation_answer_rate;
    int dictation_playnum;
    String submit_answer;

    public void setDictation_date(String dictation_date) {
        this.dictation_date = String.valueOf(dictation_date);
    }
    public void setTeacher_id(String teacher_id) {
        this.teacher_id = teacher_id;
    }

    public void setDictation_answer(String dictation_answer) {
        this.dictation_answer = dictation_answer;
    }

    public void setDictation_answer_rate(int dictation_answer_rate) {
        this.dictation_answer_rate = dictation_answer_rate;
    }

    public void setDictation_playnum(int dictation_playnum) {
        this.dictation_playnum = dictation_playnum;
    }

    public void setSubmit_answer(String submit_answer){
        this.submit_answer = submit_answer;
    }

    public String getDictation_date() {return dictation_date;}

    public String getTeacher_id() {return " "+teacher_id;}

    public String getDictation_answer() {return dictation_answer;}

    public String getDictation_answer_rate() {return String.valueOf(dictation_answer_rate);}

    public String getDictation_playnum() {return String.valueOf(dictation_playnum);}

    public String getSubmit_answer() {return submit_answer;}
}
