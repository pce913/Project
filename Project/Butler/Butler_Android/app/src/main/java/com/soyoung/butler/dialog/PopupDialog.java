package com.soyoung.butler.dialog;

import android.app.Dialog;
import android.content.Context;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.soyoung.butler.R;
import com.soyoung.butler.network.NetworkService;

/**
 * Created by Chan on 2017-01-06.
 */
public class PopupDialog extends Dialog{
    // PopupDialog popupDialog;
    TextView popupTextView;
    Button buttonOk;
    NetworkService service;
    public PopupDialog(Context context) {
        super(context);
        //  getWindow().requestFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.dialog_popup);
        popupTextView = (TextView)findViewById(R.id.popupTextView);
        buttonOk = (Button)findViewById(R.id.buttonOk);

        buttonOk.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                PopupDialog.this.dismiss();
            }
        });
    }
    public void setText(String popupText){
        popupTextView.setText(popupText);
    }

}