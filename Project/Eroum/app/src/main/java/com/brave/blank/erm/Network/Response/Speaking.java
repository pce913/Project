package com.brave.blank.erm.Network.Response;

import java.util.Date;

///**
// * Created by chanung on 2016-08-13.
// */
public class Speaking {
    int id;
    String question;
    Date start_date;
    Date end_date;
    int success_count;
    int challenge_count;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getQuestion() {
        return question;
    }

    public void setQuestion(String question) {
        this.question = question;
    }

    public Date getStart_date() {
        return start_date;
    }

    public void setStart_date(Date start_date) {
        this.start_date = start_date;
    }

    public Date getEnd_date() {
        return end_date;
    }

    public void setEnd_date(Date end_date) {
        this.end_date = end_date;
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