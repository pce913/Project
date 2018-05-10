package com.soyoung.butler.journey_day;

/**
 * Created by Soyoung on 17. 1. 2..
 */
public class MapData {
    String recommend_spot;
    String latitude;
    String longitude;

    public MapData(){}

    public MapData(String recommend_spot, String latitude, String longitude) {
        this.recommend_spot = recommend_spot;
        this.latitude = latitude;
        this.longitude = longitude;
    }
}
