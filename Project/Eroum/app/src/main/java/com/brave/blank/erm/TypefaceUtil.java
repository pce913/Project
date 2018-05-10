package com.brave.blank.erm;

import android.content.Context;
import android.graphics.Typeface;

import java.lang.reflect.Field;

/**
 * Created by IT on 2016-09-30.
 */
public class TypefaceUtil {

    public static void overrideFont(Context context, String defalutFontNameToOverride, String customFontFileNameInAssets) {
        try {
            final Typeface customFontTypeface = Typeface.createFromAsset(context.getAssets(), customFontFileNameInAssets);

            final Field defaultFontTypefaceField = Typeface.class.getDeclaredField(defalutFontNameToOverride);
            defaultFontTypefaceField.setAccessible(true);
            defaultFontTypefaceField.set(null, customFontTypeface);
        } catch (Exception e) {

        }
    }
}

