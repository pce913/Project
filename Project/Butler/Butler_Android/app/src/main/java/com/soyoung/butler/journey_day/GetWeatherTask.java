package com.soyoung.butler.journey_day;

import android.os.AsyncTask;
import android.widget.ImageView;
import android.widget.TextView;

import com.soyoung.butler.R;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

/**
 * Created by user1 on 2017-01-02.
 */

public class GetWeatherTask extends AsyncTask<String, Void, Weather_Object> {
    private TextView textView,textView2;
    private ImageView imageView, backgroundimg;
    public GetWeatherTask(TextView textView,ImageView imageView, ImageView backgroundimg) {
        this.textView = textView;
        this.imageView = imageView;
        this.backgroundimg = backgroundimg;
    }

    protected Weather_Object doInBackground(String... strings) {
        Weather_Object weather = new Weather_Object();
        try {
            URL url = new URL(strings[0]);
            HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();

            InputStream stream = new BufferedInputStream(urlConnection.getInputStream());
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(stream));
            StringBuilder builder = new StringBuilder();

            String inputString;
            while ((inputString = bufferedReader.readLine()) != null) {
                builder.append(inputString);
            }

            JSONObject topLevel = new JSONObject(builder.toString());
            JSONObject main = topLevel.getJSONObject("main");
            weather.temperature = String.valueOf(main.getDouble("temp"));
            JSONArray weatherInfo = topLevel.getJSONArray("weather");
            weather.situation = weatherInfo.getJSONObject(0).getString("description");
            urlConnection.disconnect();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return weather;
    }

    protected void onPostExecute(Weather_Object temp) {
        String str = String.format("%.1f˚C", (Double.parseDouble(temp.temperature) - 32) / 1.8);
        textView.setText(str);

        if (temp.situation.equals("clear sky")) {
            imageView.setImageResource(R.drawable.trip_route_sunny);
            backgroundimg.setImageResource(R.drawable.trip_route_weather_background_sunny);
        }
        else if (temp.situation.equals("few clouds") && temp.situation.equals("scattered clouds")) {
            imageView.setImageResource(R.drawable.trip_route_cloud);
            backgroundimg.setImageResource(R.drawable.trip_route_weather_background_cloud);
        }
        else if (temp.situation.equals("snow")) {
            imageView.setImageResource(R.drawable.trip_route_snow);
            backgroundimg.setImageResource(R.drawable.trip_route_weather_background_snow);
        }
        else {
            imageView.setImageResource(R.drawable.trip_route_rainy);
            backgroundimg.setImageResource(R.drawable.trip_route_weather_background_rainy);
        }
    }
}