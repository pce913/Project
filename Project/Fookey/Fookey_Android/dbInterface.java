package com.smu.cs.fookey;

import java.util.List;

/**
 * Created by LG on 2017-08-18.
 */

public interface dbInterface {
    void insertData(FoodData data);
    void deleteData(FoodData data);
    List<FoodData> getDataList();
}
