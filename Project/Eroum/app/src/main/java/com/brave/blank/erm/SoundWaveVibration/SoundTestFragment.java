package com.brave.blank.erm.SoundWaveVibration;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Vibrator;
import android.util.Log;
import android.view.Display;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.brave.blank.erm.AssembledData;
import com.brave.blank.erm.BaseFragment;
import com.brave.blank.erm.R;
import com.brave.blank.erm.ToolbarActivity;

/**
 * Created by chanung on 2016-08-10.
 */
public class SoundTestFragment extends BaseFragment {
    private CDrawer.CDrawThread mDrawThread;
    private CDrawer mdrawer;

    private View.OnClickListener listener;
    private Boolean m_bStart = Boolean.valueOf(false);
    private Boolean recording;
    private CSampler sampler;
    private static Vibrator mVibrator;

    TextView textInfo;

    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        ViewGroup rootView= (ViewGroup)inflater.inflate(R.layout.fragment_sound_test, container, false);
        mdrawer = (CDrawer) rootView.findViewById(R.id.drawer);
        textInfo=(TextView) rootView.findViewById(R.id.textInfo);
        textInfo.setText("스스로 내는 소리를 눈으로 확인해보세요!\n" +
                "입 모양을 바꿔가며 호흡을 내뱉으면 다양한\n"+
        "소리를 만들 수 있어요.");

        mVibrator = (Vibrator) getActivity().getSystemService(Context.VIBRATOR_SERVICE);

        m_bStart = Boolean.valueOf(false);
        while (true)
        {
            recording = Boolean.valueOf(false);
            run();
            System.out.println("mDrawThread NOT NULL");
            System.out.println("recorder NOT NULL");
            break;
        }
        rootView.setFocusableInTouchMode(true);
        rootView.requestFocus();
        rootView.setOnKeyListener(new View.OnKeyListener(){
            @Override
            public boolean onKey(View v,int keyCode, KeyEvent event) {
                if (keyCode == KeyEvent.KEYCODE_BACK) {
                    if(AssembledData.flag == 5) {
                        Log.d("keyname", "backkey");
                        Intent intentMain = new Intent(getActivity(), ToolbarActivity.class);
                        intentMain.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                        intentMain.addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
                        startActivity(intentMain);
                        getActivity().finish();
                        return true;
                    }
                    else {
                        AssembledData.flag=5;
                        return false;
                    }
                }
                else
                    return false;
            }
        });
        return rootView;
    }

    @Override
    public void onPause()
    {
        System.out.println("onpause");
        sampler.SetRun(Boolean.valueOf(false));
        mDrawThread.setRun(Boolean.valueOf(false));
        sampler.SetSleeping(Boolean.valueOf(true));
        mDrawThread.SetSleeping(Boolean.valueOf(true));
        Boolean.valueOf(false);
        super.onPause();
    }
    /**
     * Resters the visualizer when the app restarts
     */
   // @Override
    protected void onRestart()
    {
        m_bStart = Boolean.valueOf(true);
        System.out.println("onRestart");
      //  super.onRestart();
    }
    /**
     * Resume the visualizer when the app resumes
     */
    @Override
    public void onResume()
    {
        System.out.println("onresume");
        int i = 0;
        while (true)
        {
            if ((sampler.GetDead2().booleanValue()) && (mdrawer.GetDead2().booleanValue()))
            {
                System.out.println(sampler.GetDead2() + ", " + mdrawer.GetDead2());
                sampler.Restart();
                if (!m_bStart.booleanValue())
                    mdrawer.Restart(Boolean.valueOf(true));
                sampler.SetSleeping(Boolean.valueOf(false));
                mDrawThread.SetSleeping(Boolean.valueOf(false));
                m_bStart = Boolean.valueOf(false);
                super.onResume();
                return;
            }
            try
            {
                Thread.sleep(500L);
                System.out.println("Hang on..");
                i++;
                if (!sampler.GetDead2().booleanValue())
                    System.out.println("sampler not DEAD!!!");
                if (!mdrawer.GetDead2().booleanValue())
                {
                    System.out.println("mDrawer not DeAD!!");
                    mdrawer.SetRun(Boolean.valueOf(false));
                }
                if (i <= 4)
                    continue;
                mDrawThread.SetDead2(Boolean.valueOf(true));
            }
            catch (InterruptedException localInterruptedException)
            {
                localInterruptedException.printStackTrace();
            }
        }
    }
    @Override
    public void onStart()
    {
        System.out.println("onstart");
        super.onStart();
    }

    @Override
    public void onStop()
    {
        System.out.println("onstop");
        super.onStop();
    }

    @Override
    public void onDestroy() {
        //Cancel vibration when the application is about to close
        if (mVibrator != null)
            mVibrator.cancel();
        super.onDestroy();
    }

    public void setBuffer(short[] paramArrayOfShort)
    {
        mDrawThread = mdrawer.getThread();
        mDrawThread.setBuffer(paramArrayOfShort);
    }

    /**
     * Called by OnCreate to get everything up and running
     */
    public void run()
    {
        try
        {
            if (mDrawThread == null)
            {
                mDrawThread = mdrawer.getThread();
            }
            if (sampler == null)
                sampler = new CSampler(this);
          //  Context localContext = getActivity().getApplicationContext();
            Display localDisplay = getActivity().getWindowManager().getDefaultDisplay();
          //  Toast localToast = Toast.makeText(localContext, "Please make some noise..", Toast.LENGTH_LONG);
           // localToast.setGravity(48, 0, localDisplay.getHeight() / 8);
           // localToast.show();
            mdrawer.setOnClickListener(listener);
            if (sampler != null){
                sampler.Init();
                sampler.StartRecording();
                sampler.StartSampling();
            }
        } catch (NullPointerException e) {
            Log.e("Main_Run", "NullPointer: " + e.getMessage());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static Vibrator getVibrator(){
        return mVibrator;
    }
}
