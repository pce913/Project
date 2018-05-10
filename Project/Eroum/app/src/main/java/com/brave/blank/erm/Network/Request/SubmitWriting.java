package com.brave.blank.erm.Network.Request;

/**
 * Created by chanung on 2016-08-13.
 */
public class SubmitWriting {
    private boolean type;
    private  int homework_id;
    private  int rate;
    private   int play_count;
    private    String answer;

    public boolean isType() {
        return type;
    }

    public void setType(boolean type) {
        this.type = type;
    }

    public int getHomework_id() {
        return homework_id;
    }

    public void setHomework_id(int homework_id) {
        this.homework_id = homework_id;
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

    public String getAnswer() {
        return answer;
    }

    public void setAnswer(String answer) {
        this.answer = answer;
    }
}
