package com.soyoung.butler.drag;

import java.util.ArrayList;

/**
 * Created by user1 on 2017-01-06.
 */

public class OneDayResultPutter{
    public ArrayList<OneDayResult> results;
    private static OneDayResultPutter instance = null;
    private OneDayResultPutter(){}

    public static OneDayResultPutter getInstance(){
        if(instance == null)
            instance = new OneDayResultPutter();
        return instance;
    }
}
