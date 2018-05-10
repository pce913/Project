package com.brave.blank.erm;

import android.app.Application;
import android.graphics.Typeface;
import android.text.style.TypefaceSpan;

/**
 * Created by IT on 2016-09-30.
 */
public class BaseActivity extends Application{

    @Override
    public void onCreate() {
        TypefaceUtil.overrideFont(getApplicationContext(), "SERIF", "fonts/mainfont.otf");

    }

}
