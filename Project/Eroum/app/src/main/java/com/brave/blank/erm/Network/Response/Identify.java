package com.brave.blank.erm.Network.Response;

/**
 * Created by chanung on 2016-08-07.
 */
public class Identify {                       //로그인 후 Response
    private boolean result;
    private String token;
    private String teacher;
    private static String name;                      //name 받아오면 풀어주기.

    public boolean isResult() {
        return result;
    }

    public void setTeacher(String teacher){this.teacher = teacher;}

    public String getTeacher(){return teacher;}

    public void setResult(boolean result) {
        this.result = result;
    }

    public String getToken() {
        return token;
    }

    public void setToken(String token) {
        this.token = token;
    }

    public static String getName() {
        return name;
    }

    public static void setName(String name) {
        Identify.name = name;
    }
}
