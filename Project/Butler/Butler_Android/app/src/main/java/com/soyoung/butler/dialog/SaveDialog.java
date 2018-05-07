package com.soyoung.butler.dialog;

import android.app.Dialog;
import android.content.Context;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.soyoung.butler.R;

/**
 * Created by Chan on 2017-01-06.
 */
public class SaveDialog extends Dialog{
    // PopupDialog popupDialog;
    TextView popupTextView;
    Button buttonSave,buttonCancel;
    boolean save;
    public SaveDialog(Context context) {
        super(context);
        //  getWindow().requestFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.dialog_save);
        popupTextView = (TextView)findViewById(R.id.popupTextView);
        buttonSave = (Button)findViewById(R.id.buttonSave);
        buttonCancel = (Button)findViewById(R.id.buttonCancel);

        buttonSave.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                save=true;
                SaveDialog.this.dismiss();
            }
        });
        buttonCancel.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                save=false;
                SaveDialog.this.dismiss();
            }
        });
    }
    public void setText(String popupText){
        popupTextView.setText(popupText);
    }

    public boolean isSave(){
        return save;
    }


}