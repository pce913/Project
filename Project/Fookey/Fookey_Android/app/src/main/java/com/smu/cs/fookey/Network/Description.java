package com.smu.cs.fookey.Network;

import com.smu.cs.fookey.SearchActivity;

import java.io.Serializable;
import java.util.List;

/**
 * Created by Chan on 2017-08-23.
 */
public class Description implements Serializable{
    List<String> food_info;

    public List<String> getFood_info() {
        return food_info;
    }

    public void setFood_info(List<String> food_info) {
        this.food_info = food_info;
    }

    public Description(List<String> food_info) {

        this.food_info = food_info;
    }
}