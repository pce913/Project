package com.brave.blank.erm.Network.Response;

import java.util.Date;

/**
 * Created by chanung on 2016-08-07.
 */
public class Homework {
    private int homework_id;
    private int id;
  //  private int status;   //boolean을 int로 바꿔줌
    private Date end_date;
    private Date start_date;
    private int type;    //boolean을 int로 바꿔줌
    private String question;
    private String url;

    public void setId(int id) {
        this.id = id;
    }

//    public void setStatus(int status) {
//        this.status = status;
//    }

    public void setQuestion(String question) {
        this.question = question;
    }

    public void setStart_date(Date start_date) {
        this.start_date = start_date;
    }

    public void setUrl(String url){ this.url = url;}

    public void setType(int type) {
        this.type = type;
    }

    public int getId() {
        return id;
    }

    public Date getStart_date() {
        return start_date;
    }

    public int getType(){return type;}

//   public int getStatus(){
//        return status;
//    }

    public String getQuestion() {
        return question;
    }

    public String getUrl(){ return url; }

    public Date getEnd_date() {
        return end_date;
    }

    public void setEnd_date(Date end_date) {
        this.end_date = end_date;
    }

    public int getHomework_id() {
        return homework_id;
    }

    public void setHomework_id(int homework_id) {
        this.homework_id = homework_id;
    }
}