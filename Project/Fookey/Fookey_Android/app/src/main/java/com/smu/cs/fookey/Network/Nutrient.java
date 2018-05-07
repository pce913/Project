package com.smu.cs.fookey.Network;

import java.io.Serializable;

/**
 * Created by Chan on 2017-08-31.
 */

public class Nutrient implements Serializable {
    private int carbohydrate;
    private int protein;
    private int fat;

    public Nutrient(int carbohydrate, int protein, int fat) {
        this.carbohydrate = carbohydrate;
        this.protein = protein;
        this.fat = fat;
    }

    public int getCarbohydrate() {
        return carbohydrate;
    }

    public void setCarbohydrate(int carbohydrate) {
        this.carbohydrate = carbohydrate;
    }

    public int getProtein() {
        return protein;
    }

    public void setProtein(int protein) {
        this.protein = protein;
    }

    public int getFat() {
        return fat;
    }

    public void setFat(int fat) {
        this.fat = fat;
    }
}