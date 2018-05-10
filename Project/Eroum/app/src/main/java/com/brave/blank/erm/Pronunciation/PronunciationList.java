package com.brave.blank.erm.Pronunciation;

/**
 * Created by jeonyongjin on 2016. 8. 7..
 */
public class PronunciationList {
    String pronunciation_date;
    String teacher_id;
    String pronunciation_answer;
    int pronunciation_answer_rate;
    int pronunciation_playnum;


    public void setPronunciation_date(String dictation_date) {
        this.pronunciation_date = String.valueOf(dictation_date);
    }

    public void setp_Teacher_id(String teacher_id) {
        this.teacher_id = teacher_id;
    }

    public void setPronunciation_answer(String dictation_answer) {
        this.pronunciation_answer = dictation_answer;
    }

    public void setPronunciation_answer_rate(int dictation_answer_rate) {
        this.pronunciation_answer_rate = dictation_answer_rate;
    }

    public void setPronunciation_playnum(int dictation_playnum) {
        this.pronunciation_playnum = dictation_playnum;
    }

    public String getPronunciation_date() {return pronunciation_date;}

    public String getp_Teacher_id() {return " "+teacher_id;}

    public String getPronunciation_answer() {return pronunciation_answer;}

    public String getPronunciation_answer_rate() {return String.valueOf(pronunciation_answer_rate);}

    public String getPronunciation_playnum() {return String.valueOf(pronunciation_playnum);}
}
