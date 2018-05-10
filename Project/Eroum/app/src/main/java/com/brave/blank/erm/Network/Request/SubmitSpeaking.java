package com.brave.blank.erm.Network.Request;

/**
 * Created by chanung on 2016-08-13.
 */
public class SubmitSpeaking {
    private boolean type;
    private  int homework_id;
    private  int success_count;
    private  int challenge_count;

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

    public int getSuccess_count() {
        return success_count;
    }

    public void setSuccess_count(int success_count) {
        this.success_count = success_count;
    }

    public int getChallenge_count() {
        return challenge_count;
    }

    public void setChallenge_count(int challenge_count) {
        this.challenge_count = challenge_count;
    }
}
