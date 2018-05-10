package com.brave.blank.erm;

import android.util.Log;

import com.brave.blank.erm.Network.Response.Homework;
import com.brave.blank.erm.Network.Response.Identify;
import com.brave.blank.erm.Network.Response.Speaking;
import com.brave.blank.erm.Network.Response.StudyInfo;
import com.brave.blank.erm.Network.Response.Topic;
import com.brave.blank.erm.Network.Response.Writing;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by chanung on 2016-08-14.
 */
public class AssembledData {
    private static List<Topic> topics;
    private static List<StudyInfo> learnedInfos;                            //학습한 정보
    private static List<StudyInfo> savedInfos;
    private static List<Homework> homeworks;

    private static List<Writing> writings;
    private static List<Speaking> speakings;

    private static ArrayList<Topic> wordTopics=new ArrayList<Topic>();
    private static ArrayList<Topic> sentenceTopics=new ArrayList<Topic>();
    private static boolean firstWordTopics=true;
    private static boolean firstSentenceTopics=true;

    private static boolean firsthomework=true;

    private static boolean firstNotyetHomework=true;
    private static boolean firstDoneHomework=true;

    private static boolean firstWritings = true;
    private static boolean firstSpeaking = true;

    public static int flag = 5;
    ////////////////////////////////////////////
    private static ArrayList<StudyInfo> learnedConsonant=new ArrayList<StudyInfo>();
    private static ArrayList<StudyInfo> learnedVowel=new ArrayList<StudyInfo>();
    private static ArrayList<StudyInfo> learnedWords=new ArrayList<StudyInfo>();
    private static ArrayList<StudyInfo> learnedSentences=new ArrayList<StudyInfo>();
    private static ArrayList<StudyInfo> learnedFinalConsonant=new ArrayList<StudyInfo>();
    private static boolean firstLearnedConsonant=true;
    private static boolean firstLearnedVowel=true;
    private static boolean firstLearnedWords=true;
    private static boolean firstLearnedSentences=true;
    private static boolean firstLearnedFinalConsonant=true;
    /////////////////////////////////////////////////
    private static ArrayList<StudyInfo> savedConsonant=new ArrayList<StudyInfo>();
    private static ArrayList<StudyInfo> savedVowel=new ArrayList<StudyInfo>();
    private static ArrayList<StudyInfo> savedWords=new ArrayList<StudyInfo>();
    private static ArrayList<StudyInfo> savedSentences=new ArrayList<StudyInfo>();
    private static ArrayList<StudyInfo> savedFinalConsonant=new ArrayList<StudyInfo>();
    private static boolean firstSavedConsonant=true;
    private static boolean firstSavedVowel=true;
    private static boolean firstSavedWords=true;
    private static boolean firstSavedSentences=true;
    private static boolean firstSavedFinalConsonant=true;
    /////////////////////////////////////////////////
    private static ArrayList<Homework> homeworknotyet = new ArrayList<Homework>();
    private static ArrayList<Homework> homeworkdone = new ArrayList<Homework>();
    /////////////////////////////////////////////////
    private static ArrayList<Writing> writingArrayList = new ArrayList<>();
    private static ArrayList<Speaking> speakingArrayList = new ArrayList<>();
    /////////////////////////////////////////////////
    private static Identify identify=new Identify();


    public static void setIdentifies(Identify identify1){
        identify.setName(identify1.getName());
        identify.setTeacher(identify1.getTeacher());
    }
    public static Identify getIdentify(){
        return identify;
    }

    public static void setHomeworks(List<Homework> homeworks) {
        if(firsthomework ==true) {
            AssembledData.homeworks = homeworks;
            firsthomework = false;
        }
        else {
            for (int i = 0; i < homeworks.size(); i++) {
                AssembledData.homeworks.add(homeworks.get(i));
            }
        }
    }
    public static List<Homework> getHomeworks() {
        return homeworks;
    }

    public static ArrayList<Homework> getHomeworkNotyet(){
        if(homeworks!=null && firstNotyetHomework==true) {//이게 여러번 실행됨.
            Log.d("notyet실행되니",String.valueOf(AssembledData.homeworknotyet.size()));
            for(int i=0;i<homeworks.size();i++){
                if(homeworks.get(i).getEnd_date() == null) {                  //1 단어에 대한 주제목록
                    homeworknotyet.add(homeworks.get(i));

                }
            }
            firstNotyetHomework=false;
            for(int i=0;i<homeworknotyet.size();i++){
                Log.d("id값 추적", String.valueOf(homeworknotyet.get(i).getHomework_id()));
            }
        }
        return homeworknotyet;
    }
    public static ArrayList<Homework> getHomeworkdone(){
        if(homeworks!=null && firstDoneHomework==true) {                                     //이게 여러번 실행됨.
            for(int i=0;i<homeworks.size();i++){
                if(homeworks.get(i).getEnd_date() != null){
                    homeworkdone.add(homeworks.get(i));
//                    Log.d("id값 추적", String.valueOf(homeworkdone.get(i).getHomework_id()));
                }
            }
            for(int i=0;i<homeworkdone.size();i++){
            }
            firstDoneHomework=false;
        }
        return homeworkdone;
    }

    public static List<Topic> getTopics() {
        return topics;
    }

    public static void setTopics(List<Topic> topics) {
        AssembledData.topics = topics;
    }

    public static List<StudyInfo> getLearnedInfos() {
        return learnedInfos;
    }

    public static void setLearnedInfos(List<StudyInfo> learnedInfos) {
        AssembledData.learnedInfos = learnedInfos;
    }

    public static List<StudyInfo> getSavedInfos() {
        return savedInfos;
    }

    public static void setSavedInfos(List<StudyInfo> savedInfos) {
        AssembledData.savedInfos = savedInfos;
    }


    public static void setWordTopics(List<Topic> _wordTopics){
        wordTopics=(ArrayList)_wordTopics;
    }

    public static void setSentenceTopics(List<Topic> _sentenceTopics){
        sentenceTopics=(ArrayList)_sentenceTopics;
    }
    public static ArrayList<Topic> getWordTopics(){
//
//        if(topics!=null && firstWordTopics==true) {                                     //이게 여러번 실행됨.
//            Log.d("getWordTopics", "이거 몇번실행?");
//            for(int i=0;i< topics.size();i++){
//                if(topics.get(i).getType()==1) {                  //1 단어에 대한 주제목록
//                    wordTopics.add(topics.get(i));
//                    Log.d("wordtopics", String.valueOf(wordTopics.size()));
//                }
//            }
//            firstWordTopics=false;
//        }
//        Log.d("getWordTopics", "topics.size() : " + topics.size());
        return wordTopics;
    }
    //
    public static ArrayList<Topic> getSentenceTopics(){
//        if(topics!=null && firstSentenceTopics==true) {
//            Log.d("getsentenceTopics", "이거 몇번실행?");
//            for(int i=0;i< topics.size();i++){
//                if((topics.get(i).getType()==2)) {                                    // 2 문장에 대한 주제목록
//                    sentenceTopics.add(topics.get(i));
//                    Log.d("sentencetopics",String.valueOf(sentenceTopics.size()));
//                }
//            }
//            firstSentenceTopics = false;
//        }
        //    Log.d("getWordTopics", "topics.size() : " + topics.size());
        return sentenceTopics;
    }

    public static ArrayList<StudyInfo> getLearnedConsonant(){
        if(learnedInfos!=null && firstLearnedConsonant==true)
            distributeLearnedInfo();

        return learnedConsonant;
    }

    public static ArrayList<StudyInfo> getLearnedVowel(){
        if(learnedInfos!=null && firstLearnedVowel==true)
            distributeLearnedInfo();

        return learnedVowel;
    }


    public static ArrayList<StudyInfo> getLearnedWords(){
        if(learnedInfos!=null && firstLearnedWords==true)
            distributeLearnedInfo();

        return learnedWords;
    }
    public static ArrayList<StudyInfo> getLearnedSentences(){
        if(learnedInfos!=null && firstLearnedSentences==true)
            distributeLearnedInfo();

        return learnedSentences;
    }

    public static ArrayList<StudyInfo> getLearnedFinalConsonant(){
        if(learnedInfos!=null && firstLearnedFinalConsonant==true)
            distributeLearnedInfo();

        return learnedFinalConsonant;
    }

    private static void distributeLearnedInfo(){
        ArrayList<StudyInfo> learnedBase;
        for(int i=0;i<learnedInfos.size();i++){
            if(learnedInfos.get(i).getType()==0){                              //0 자음에 대한 학습완료 목록
                learnedBase=learnedConsonant;
            }
            else if(learnedInfos.get(i).getType()==1){                        //1 모음에 대한 학습완료 목록
                learnedBase=learnedVowel;
            }
            else if(learnedInfos.get(i).getType()==2){                    //2 받침에 대한 학습완료 목록
                learnedBase=learnedFinalConsonant;
            }
            else if(learnedInfos.get(i).getType()>=4 && learnedInfos.get(i).getType()<=10 ){                      // 단어에 대한 학습완료 목록
                learnedBase=learnedWords;
            }
            else{                      //5문장에 대한 학습완료 목록
                learnedBase=learnedSentences;
            }


            learnedBase.add(learnedInfos.get(i));
        }
    }

    public static ArrayList<StudyInfo> getSavedConsonant(){
        if(savedInfos!=null && firstSavedConsonant==true)
            distributeSavedInfo();

        return savedConsonant;
    }

    public static ArrayList<StudyInfo> getSavedVowel(){
        if(savedInfos!=null && firstSavedVowel==true)
            distributeSavedInfo();

        return savedVowel;
    }

    public static ArrayList<StudyInfo> getSavedWords(){
        if(savedInfos!=null && firstSavedWords==true)
            distributeSavedInfo();

        return savedWords;
    }

    public static ArrayList<StudyInfo> getSavedSentences(){
        if(savedInfos!=null && firstSavedSentences==true)
            distributeSavedInfo();

        return savedSentences;
    }

    public static ArrayList<StudyInfo> getSavedFinalConsonant(){
        if(savedInfos!=null && firstSavedFinalConsonant==true)
            distributeSavedInfo();

        return savedFinalConsonant;
    }

    private static void distributeSavedInfo(){
        ArrayList<StudyInfo> savedBase;
        for(int i=0;i<savedInfos.size();i++){
            if(savedInfos.get(i).getType()==1){                              //1 자음에 대한 저장목록
                savedBase=savedConsonant;
            }
            else if(savedInfos.get(i).getType()==2){                        //2 모음에 대한 저장목록
                savedBase=savedVowel;
            }
            else if(savedInfos.get(i).getType()==3){                      //3 단어에 대한 저장목록
                savedBase=savedWords;
            }
            else if(savedInfos.get(i).getType()==4){                      //4 문장에 대한 저장목록     (가정)
                savedBase=savedSentences;
            }
            else{                                                      //5 받침에 대한 저장목록           (가정)
                savedBase=savedFinalConsonant;
            }

            savedBase.add(savedInfos.get(i));
        }
    }
    public static ArrayList<Writing> getWritingArrayList() {
        if(writings!=null && firstWritings==true) {
            for (int i = 0; i < writings.size(); i++)
                writingArrayList.add(writings.get(i));
        }
        firstWritings = false;
        return writingArrayList;
    }

    public static void setWritingList(List<Writing> writings) {
        AssembledData.writings = writings;
        Log.d("writings너는 사이즈가 뭐니", String.valueOf(AssembledData.writings.size()));
    }

    public static ArrayList<Speaking> getSpeakingArrayList() {
        if(speakings!=null && firstSpeaking==true) {
            for (int i = 0; i < speakings.size(); i++)
                speakingArrayList.add(speakings.get(i));
        }

        firstSpeaking = false;
        return speakingArrayList;
    }

    public static void setSpeakingList(List<Speaking> speakings) {
        AssembledData.speakings=speakings;
        Log.d("speakings너는 사이즈가 뭐니", String.valueOf(AssembledData.speakings.size()));
    }
}