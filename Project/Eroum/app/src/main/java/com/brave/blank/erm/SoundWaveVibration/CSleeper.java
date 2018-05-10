package com.brave.blank.erm.SoundWaveVibration;

/**
 * Created by jeonyongjin on 2016. 8. 4..
 */

/**
 *  This is the sleeper for the visualizer
 *  This allows the sampler to collect data before running.
 *  @author Pontus Holmberg (EndLessMind)
 *  Email: the_mr_hb@hotmail.com
 **/
public class CSleeper
        implements Runnable
{
    private Boolean done = Boolean.valueOf(false);
    private SoundTestFragment m_ma;
    private CSampler m_sampler;

    public CSleeper(SoundTestFragment paramMainActivity, CSampler paramCSampler)
    {
        m_ma = paramMainActivity;
        m_sampler = paramCSampler;
    }

    public void run()
    {
        try {
            m_sampler.Init();
        } catch (Exception e) {
            e.printStackTrace();
        }
        while (true)
            try
            {
                Thread.sleep(1000L);
                System.out.println("Tick");
                continue;
            }
            catch (InterruptedException localInterruptedException)
            {
                localInterruptedException.printStackTrace();
            }
    }
}

