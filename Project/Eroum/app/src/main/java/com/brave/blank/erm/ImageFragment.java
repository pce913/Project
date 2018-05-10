package com.brave.blank.erm;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import com.bumptech.glide.Glide;

/**
 * Created by chanung on 2016-08-06.
 */
public class ImageFragment extends Fragment {
    ImageView imageView11;
    String img;
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
        ViewGroup rootView= (ViewGroup)inflater.inflate(R.layout.fragment_image,container,false);
        imageView11=(ImageView)rootView.findViewById(R.id.imageView11);
        Glide.with(this).load("http://188.166.181.182:9305/study/item/image?img=" + img).into(imageView11);
      //  Glide.with(this).load("http://188.166.181.182:9305/study/item/image?img=ㄱ.png").into(imageView11);
        String image=img;
        return rootView;
    }
    public void getImageUrl(String img){
        this.img=img;
    }
}
