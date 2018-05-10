package com.soyoung.butler.drag;

/**
 * Created by baesangik on 2017. 1. 1..
 */

public class CityData {

    public String city;
    public String sight_image_url;
    public String spot;

    public CityData(){}

    public CityData(String imgUrl, String cityName) {
        this.sight_image_url = imgUrl;
        this.spot = cityName;
    }
}
