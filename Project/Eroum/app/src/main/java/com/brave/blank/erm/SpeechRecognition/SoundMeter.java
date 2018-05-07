package com.brave.blank.erm.SpeechRecognition;

import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;

/**
 * Created by chanung on 2016-07-28.
 */
public class SoundMeter {
    private AudioRecord ar = null;
    private int minSize;

    public void start() {
        minSize= AudioRecord.getMinBufferSize(44100, AudioFormat.CHANNEL_IN_MONO, AudioFormat.ENCODING_PCM_16BIT);
        ar = new AudioRecord(MediaRecorder.AudioSource.MIC, 44100,AudioFormat.CHANNEL_IN_MONO, AudioFormat.ENCODING_PCM_16BIT,minSize);
        ar.startRecording();
    }

    public void stop() {
        if (ar != null) {
            ar.stop();
        }
    }


    public double getAmplitude() {

        short[] buffer = new short[minSize];
        int bufferSize = ar.read(buffer, 0, minSize);
        double sum = 0;
        for (short s : buffer) {
            sum += Math.abs(s);
        }
        return Math.abs(sum / bufferSize);
    }
}
