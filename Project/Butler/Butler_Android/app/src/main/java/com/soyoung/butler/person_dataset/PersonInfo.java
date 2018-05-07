package com.soyoung.butler.person_dataset;

/**
 * Created by user1 on 2016-12-29.
 */

public class PersonInfo {
    private String email = "";
    private String name = "";
    private String image = "";
    public String user_id = "";

    private static PersonInfo instance = null;

    private PersonInfo(){}
    public static PersonInfo getInstance() throws Exception{
        if(instance == null)
            instance = new PersonInfo();

        return instance;
    }
    public void setPersonInfo(String email,String name,String image,String user_id){
        this.email = email;
        this.name = name;
        this.image = image;
        this.user_id = user_id;
    }

    public String getEmail(){
        return email;
    }
    public String getName(){
        return name;
    }
    public String getImage(){
        return image;
    }
    public String getUser_id(){return user_id;}

}
