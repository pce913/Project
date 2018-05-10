package com.brave.blank.erm.Network.Request;

/**
 * Created by chanung on 2016-08-07.
 */
public class Signup {
    private String user;
    private  String password;
    private String name;
    private int school;
    private int grade;
    private int class_num;
    private String teacher;

    public String getUser() {
        return user;
    }

    public void setUser(String user) {
        this.user = user;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getSchool() {
        return school;
    }

    public void setSchool(int school) {
        this.school = school;
    }

    public int getGrade() {
        return grade;
    }

    public void setGrade(int grade) {
        this.grade = grade;
    }

    public int getClass_num() {
        return class_num;
    }

    public void setClass_num(int class_num) {
        this.class_num = class_num;
    }

    public String getTeacher() {
        return teacher;
    }

    public void setTeacher(String teacher) {
        this.teacher = teacher;
    }
}
