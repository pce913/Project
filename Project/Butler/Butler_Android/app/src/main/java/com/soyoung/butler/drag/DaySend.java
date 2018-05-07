package com.soyoung.butler.drag;

import java.util.ArrayList;

/**
 * Created by Soyoung on 17. 1. 4..
 */
public class DaySend {
    String user_id;
    String start_date;
    String end_date;
    public ArrayList<ArrayList<String>> schedule;

    public DaySend(){
        schedule = new ArrayList<ArrayList<String>>();
    }

}
