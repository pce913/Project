package com.brave.blank.erm.Consonant_Vowel;

/**
 * Created by jeonyongjin on 2016. 8. 13..
 */
public class CSdata {
    int id;
    String data;
    String url;
    int mode;
    String img_url;

    public String getImg_url(){return img_url;}
    public void setImg_url(String img_url){this.img_url=img_url;}
    public int getId() {
        return id;
    }
    public String getData(){
        return data;
    }
    public String geturl(){
        return url;
    }
    public void setId(int id){
        this.id = id;
    }
    public void setData(String data){
        this.data = data;
    }
    public void setUrl(String url){
        this.url = url;
    }
    public int getMode() {
        return mode;
    }
    public void setMode(int mode) {
        this.mode = mode;
    }
}