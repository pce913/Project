package com.brave.blank.erm.Network.Response;

import java.util.Date;

/**
 * Created by chanung on 2016-08-08.
 */
public class StudyInfo {
    private int id;
    private int type;
    private String data;
    private String url;               // v0.4.6 이후 수정되었음 url 넘겨주지 않음.
    private Date date;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
    }

    public String getData() {
        return data;
    }

    public void setData(String data) {
        this.data = data;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public String getUrl(){ return url;}

    public void setUrl(String url){this.url = url;}
}
