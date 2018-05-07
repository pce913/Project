package com.soyoung.butler.attraction;

import java.util.ArrayList;

/**
 * Created by user1 on 2017-01-03.
 */

public class AlternativesCityID {
    public ArrayList<String> alternatives_city_sight_id;
    public String user_id;

    private static AlternativesCityID instance = null;
    private AlternativesCityID(){}
    public static AlternativesCityID getInstance() throws Exception{
        if(instance == null)
            instance = new AlternativesCityID();

        return instance;
    }
    public void setAlternativeCityID(ArrayList<String> alternatives_city_sight_id) {
        this.alternatives_city_sight_id = alternatives_city_sight_id;
    }
}
