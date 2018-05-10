package com.brave.blank.erm.Network.Request;

/**
 * Created by chanung on 2016-08-07.
 */
public class Login {                     // 로그인 Request
    private String user;
    private String password;

    public String getUser() {
        return user;
    }

    public void setUser(String user) {
        this.user = user;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }
}
