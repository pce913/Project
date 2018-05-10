package com.brave.blank.erm.record;

/**
 * Created by IT on 2016-07-26.
 */
public class List_item_dictation {
//    String dictation_date, teacher_id, dictation_answer, dictation_answer_rate, dictation_playnum;
//
//    public String getDictation_date() {return dictation_date;}
//
//    public String getTeacher_id() {return teacher_id;}
//
//    public String getDictation_answer() {return dictation_answer;}
//
//    public String getDictation_answer_rate() {return dictation_answer_rate;}
//
//    public String getDictation_playnum() {return dictation_playnum;}
//
//    List_item_dictation(String dictation_date, String teacher_id, String dictation_answer, String dictation_answer_rate, String dictation_playnum) {
//        this.dictation_date = dictation_date;
//        this.teacher_id = teacher_id;
//        this.dictation_answer = dictation_answer;
//        this.dictation_answer_rate = dictation_answer_rate;
//        this.dictation_playnum = dictation_playnum;
//    }

    //위의 코드는 전형적인 c++형식의 코드 java에서는 getter setter를 사용하는게 좋아
    private String date;
    private String teacher_id;
    private String answer;
    private String question;
    private int rate;
    private int play_count;

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public String getTeacher_id() {
        return teacher_id;
    }

    public void setTeacher_id(String teacher_id) {
        this.teacher_id = teacher_id;
    }

    public String getAnswer() {
        return answer;
    }

    public void setAnswer(String answer) {
        this.answer = answer;
    }

    public String getQuestion() {
        return question;
    }

    public void setQuestion(String question) {
        this.question = question;
    }

    public int getRate() {
        return rate;
    }

    public void setRate(int rate) {
        this.rate = rate;
    }

    public int getPlay_count() {
        return play_count;
    }

    public void setPlay_count(int play_count) {
        this.play_count = play_count;
    }
}
