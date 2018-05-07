package com.smu.cs.fookey;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;

import java.io.Serializable;
import java.util.List;

/**
 * Created by LG on 2017-08-18.
 */

public class IntentHandler {
    public static void mainToSearch(Context context){
        Intent intent = new Intent(context, SearchActivity.class);
        context.startActivity(intent);
    }
    public static void mainToHistory(Context context){
        Intent intent = new Intent(context, HistoryActivity.class);
        context.startActivity(intent);
    }
    public static void historyToSpecific(Context context, List<String> description, String path){
        Intent intent = new Intent(context, SpecificActivity.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        intent.putExtra("description", (Serializable) description);
        intent.putExtra("path", path);
        intent.putExtra("flag", 0);
        context.startActivity(intent);
    }
    public static void SearchToResult(Context context, String imgUri){
        Intent intent = new Intent(context, ResultActivity.class);
        intent.putExtra("imgUri", imgUri);
        context.startActivity(intent);
    }
    public static void ResultToSpecific(Context context, List<String> description, String path){
        Intent intent = new Intent(context, SpecificActivity.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        intent.putExtra("description", (Serializable) description);
        intent.putExtra("path", path);
        intent.putExtra("flag", 1);
        context.startActivity(intent);
    }
}