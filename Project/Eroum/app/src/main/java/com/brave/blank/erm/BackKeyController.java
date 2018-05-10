package com.brave.blank.erm;

/**
 * Created by chanung on 2016-08-29.
 */
public class BackKeyController {
    private static boolean isHomeclassPractice;


    private static Thread recordingThread;


    public static boolean getIsHomeclassPractice() {
        return isHomeclassPractice;
    }

    public static void setIsHomeclassPractice(boolean isHomeclassPractice) {
        BackKeyController.isHomeclassPractice = isHomeclassPractice;
    }

    public static Thread getRecordingThread() {
        return recordingThread;
    }

    public static void setRecordingThread(Thread recordingThread) {
        BackKeyController.recordingThread = recordingThread;
    }
}
