package com.brave.blank.erm.Homeclass;

/**
 * Created by jeonyongjin on 2016. 7. 30..
 */
public class HomeclassList {
    private int id;
    private String date;
    private String section;
    private String confirmsubmit;
    private String contentsentence;
    private String question;

    public void setId(int id){
        this.id = id;
    }
    public void setDate(String date){
        this.date = date;
    }
    public void setSection(int index){
        if(index == 1){
            this.section = "받아쓰기";
        }
        else if(index == 0){
            this.section = "말해보기";
        }
    }
    public void setQuestion(String question){
        this.question = question;
    }
    public void setButtonText(boolean flag){
        if(!flag){
            this.confirmsubmit = "미제출";
        }
        else if(flag){
            this.confirmsubmit = "제출완료";
        }
    }
    public int getId(){
        return this.id;
    }
    public String getDate(){
        return this.date;
    }
    public String getsection(){
        return this.section;
    }
    public String getConfirmsubmit(){
        return this.confirmsubmit;
    }
    public String getQuestion(){return this.question;}
}
