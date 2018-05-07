package com.brave.blank.erm.Network;

/**
 * Created by chanung on 2016-08-07.
 */
public class Token {
    private static String token;

    public static void setToken(String _token){
        token=_token;
    }

    public static String getToken() {
        return token;
    }

}
