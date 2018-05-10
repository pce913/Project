package com.soyoung.butler.attraction;

import java.util.ArrayList;

/**
 * Created by user1 on 2017-01-03.
 */

public class EssentailCityID {
    public ArrayList<String> essentials_city_sight_id;
    public String user_id;

    private static EssentailCityID instance = null;
    private EssentailCityID(){}
    public static EssentailCityID getInstance() throws Exception{
        if(instance == null)
            instance = new EssentailCityID();

        return instance;
    }
    public void setEssentialCityID(ArrayList<String> essentials_city_sight_id){
        this.essentials_city_sight_id = essentials_city_sight_id;
    }

    public ArrayList<String> getEssentials_city_sight_id(){
        return essentials_city_sight_id;
    }
}
