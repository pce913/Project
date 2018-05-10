package com.brave.blank.erm.SoundWaveVibration;
/**
 *  This is the sampler for the visualizer
 *  This collects the data the will be visualized
 *  @author Pontus Holmberg (EndLessMind)
 *  Email: the_mr_hb@hotmail.com
 **/

import android.media.AudioRecord;
import android.os.Vibrator;
import android.util.Log;

import com.brave.blank.erm.BackKeyController;

public class CSampler
{
    private static final int SAMPPERSEC = 44100;
    private static short[] buffer;
    private AudioRecord ar;
    private int audioEncoding = 2;
    private int buffersizebytes;
    private int buflen;
    private int channelConfiguration = 16;
    private int mSamplesRead;
    private Boolean m_bDead = Boolean.valueOf(false);
    private Boolean m_bDead2 = Boolean.valueOf(true);
    private Boolean m_bRun;
    private Boolean m_bSleep = Boolean.valueOf(false);
    private SoundTestFragment m_ma;
    private Thread recordingThread;
    private boolean hasRestartCalled=false;


    private static final int THRESHOLD=60;                         //진동을 울리는 dB의 임계값을 설정.

    public CSampler(SoundTestFragment paramMainActivity)
    {
        m_ma = paramMainActivity;
        m_bRun = Boolean.valueOf(false);
    }

    public Boolean GetDead2()
    {
        return m_bDead2;
    }

    public Boolean GetSleep()
    {
        return m_bSleep;
    }

    /**
     * Prepares to collect audiodata.
     * @throws Exception
     */
    public void Init() throws Exception
    {
        try {
            if (!m_bRun)
            {
                ar = new AudioRecord(1, 44100, channelConfiguration, audioEncoding, AudioRecord.getMinBufferSize(44100, channelConfiguration, audioEncoding));
                if (ar.getState() != 1)
                    return;
                System.out.println("State initialized");
            }
        } catch (Exception e) {
            Log.d("TE", e.getMessage());
            throw new Exception();
        }
        while (true)
        {
            buffersizebytes = AudioRecord.getMinBufferSize(44100, channelConfiguration, audioEncoding);
            buffer = new short[buffersizebytes];
            m_bRun = Boolean.valueOf(true);
            System.out.println("State unitialized!!!");
            return;
        }
    }

    /**
     * Restarts the thread
     */
    public void Restart()
    {
        hasRestartCalled=true;
        while (true)
        {
            if (m_bDead2.booleanValue())
            {
                m_bDead2 = Boolean.valueOf(false);
                if (m_bDead.booleanValue())
                {
                    m_bDead = Boolean.valueOf(false);
                    ar.stop();
                    ar.release();
                    try {
                        Init();
                    } catch (Exception e) {
                        return;
                    }
                    StartRecording();
                    StartSampling();
                }
                return;
            }
            try
            {
                Thread.sleep(1000L);
            }
            catch (InterruptedException localInterruptedException)
            {
                localInterruptedException.printStackTrace();
            }
        }
    }

    /**
     * Reads the data-bufferts
     */
    public void Sample()
    {
        mSamplesRead = ar.read(buffer, 0, buffersizebytes);                            //mSamplesRead에 지속적으로 녹음된 정보가 들어옴.
    }


    public void SetRun(Boolean paramBoolean)
    {
        m_bRun = paramBoolean;
        if (m_bRun.booleanValue())
            StartRecording();
        while (true)
        {
            StopRecording();
            return;
        }
    }

    public void SetSleeping(Boolean paramBoolean)
    {
        m_bSleep = paramBoolean;
    }


    public void StartRecording()
    {
        if (ar == null) {
            try {
                Init();
            } catch (Exception e) {
                e.printStackTrace();
            }
            StartRecording();
        } else {
            if(hasRestartCalled)
                ar = new AudioRecord(1, 44100, channelConfiguration, audioEncoding, AudioRecord.getMinBufferSize(44100, channelConfiguration, audioEncoding));

            ar.startRecording();                                                     //여기서 녹음 시작.
        }

    }

    /**
     * Collects audiodata and sends it back to the main activity
     */
    public void StartSampling()
    {
        recordingThread = new Thread()
        {
            public void run()
            {
                while (true)
                {
                    if (!m_bRun.booleanValue())
                    {
                        m_bDead = Boolean.valueOf(true);
                        m_bDead2 = Boolean.valueOf(true);
                        return;
                    }
                    Sample();                                     //여기서 계속 read()를 호출하여 녹음된 값을 불러옴.

                    //여기에서 mSqmplesRead를 이용하여 진동 코드를 넣으면 됨.

                    setVibration();

                    m_ma.setBuffer(CSampler.buffer);
                }
            }
        };
        recordingThread.start();
        BackKeyController.setRecordingThread(recordingThread);
    }

    public void StopRecording()
    {
        ar.stop();
    }

    public short[] getBuffer()
    {
        return buffer;
    }

    private void setVibration(){
        Vibrator mVibrator=SoundTestFragment.getVibrator();
        double sum = 0;
        for (short s : buffer) {
            sum += Math.abs(s);
        }

        double amplitude= Math.abs(sum / mSamplesRead);
        double dB=20*Math.log10(amplitude);
        Log.d("recording", ""+dB);
        if(dB>THRESHOLD){
            mVibrator.vibrate(500);
            mVibrator.cancel();
        }

    }

}
