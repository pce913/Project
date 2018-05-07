package com.brave.blank.erm.Login;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.text.Editable;
import android.text.TextUtils;
import android.text.TextWatcher;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.brave.blank.erm.Network.ApplicationController;
import com.brave.blank.erm.Network.NetworkService;
import com.brave.blank.erm.Network.Request.Signup;
import com.brave.blank.erm.Network.Response.Result;
import com.brave.blank.erm.Network.Response.SignupResult;
import com.brave.blank.erm.R;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

/**
 * Created by IT on 2016-07-26.
 */
public class JoinActivity extends AppCompatActivity {
    Button join, cancle, idcheck, teacheridCheck;
    EditText userid, userpasswd, passwdcheck, username, userclass, usergrade, teacherid;
    Spinner school_select;
    String selectedSchool;
    Toolbar toolbar;
    TextView toolbar_title;
    boolean isMypage;
    boolean hasIdChecked;
    boolean hasTeacherIdChecked;
    String inputId;
    String inputTeacherId;

    private NetworkService networkService;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_join);
        initView();
        networkService = ApplicationController.getInstance().getNetworkService();
        hasIdChecked=false;
        hasTeacherIdChecked=false;
        setSupportActionBar(toolbar);
        toolbar_title.setText("회원가입");
//        toolbar.setTitle("회원가입");
        getSupportActionBar().setDisplayShowTitleEnabled(false);
        changeToolbar(1);
        isMypage = true;


        // 아이디 중복 검사m
        idcheck.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                hasIdChecked=true;
                if (TextUtils.isEmpty(userid.getText().toString())) {
                    Toast.makeText(JoinActivity.this, "아이디를 입력하세요!", Toast.LENGTH_SHORT).show();
                    userid.requestFocus();
                    return;
                } else {
                    Call<Result> resultCall = networkService.getDuplication(userid.getText().toString());
                    resultCall.enqueue(new Callback<Result>() {
                        @Override
                        public void onResponse(Call<Result> call, Response<Result> response) {
                            int statusCode = response.code();
                            if (response.isSuccessful()) {
                                Log.d("MyTag", "성공! 응답코드 : : " + statusCode);
                                Result isCheckId = response.body();
                                if (!isCheckId.isResult()) {  // 아이디가 중복된 경우
                                    Log.i("MyTag", "아이디 중복 있음 : " + idcheck);
                                    Toast.makeText(JoinActivity.this, "중복된 아이디가 있습니다.", Toast.LENGTH_SHORT).show();
                                    userid.requestFocus();
                                    join.setEnabled(false);
                                } else {
                                    Log.i("MyTag", "아이디 중복 없음 : " + idcheck);
                                    Toast.makeText(JoinActivity.this, "아이디를 사용할 수 있습니다.", Toast.LENGTH_SHORT).show();
                                    inputId=userid.getText().toString();
                                    join.setEnabled(true);
                                }
                            } else {
                                Log.d("MyTag", "응답코드 : " + statusCode);
                                Toast.makeText(JoinActivity.this, "네트워크 오류입니다. 회원가입을 하실 수 없습니다.", Toast.LENGTH_SHORT).show();
                                join.setEnabled(false);
                                finish();
                            }
                            Result isCheckId = response.body();
                        }

                        @Override
                        public void onFailure(Call<Result> call, Throwable t) {
                            Log.i("MyTag", "아이디 중복확인 Error : " + idcheck);
                        }
                    });
                }
            }
        });

        // 선생님 ID 확인
        teacheridCheck.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                hasTeacherIdChecked=true;
                if (TextUtils.isEmpty(teacherid.getText().toString())) {
                    Toast.makeText(JoinActivity.this, "아이디를 입력하세요!", Toast.LENGTH_SHORT).show();
                    teacherid.requestFocus();
                    return;
                }

                Call<Result> resultCall = networkService.getTeacherExist(teacherid.getText().toString());
                resultCall.enqueue(new Callback<Result>() {
                    @Override
                    public void onResponse(Call<Result> call, Response<Result> response) {
                        int statusCode = response.code();
                        if (response.isSuccessful()) {
                            Log.d("MyTag", "성공! 응답코드 : : " + statusCode);
                            Result isCheckedTeacher = response.body();
                            if (isCheckedTeacher.isResult()) {  // 선생님 아이디가 맞는 경우
                                Log.i("MyTag", "선생님 확인");
                                Toast.makeText(JoinActivity.this, "선생님 아이디가 확인되었습니다.", Toast.LENGTH_SHORT).show();
                                teacherid.requestFocus();
                                inputTeacherId=teacherid.getText().toString();
                                join.setEnabled(true);
                            } else {
                                Log.i("MyTag", "선생님 아이디가 없음");
                                Toast.makeText(JoinActivity.this, "선생님 아이디를 다시 입력해주세요", Toast.LENGTH_SHORT).show();
                                teacherid.setEnabled(true);
                                join.setEnabled(false);
                            }
                        } else {
                            Log.d("MyTag", "응답코드 : " + statusCode);
                        }
                    }

                    @Override
                    public void onFailure(Call<Result> call, Throwable t) {
                        Log.i("MyTag", "선생님 확인 실패");
                        return;
                    }
                });
            }
        });

        // 비밀번호 일치 검사
        passwdcheck.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                String password = userpasswd.getText().toString();
                String confirm = passwdcheck.getText().toString();

                if (password.equals(confirm)) {
                    userpasswd.setBackgroundColor(getResources().getColor(R.color.colorPrimary));
                    passwdcheck.setBackgroundColor(getResources().getColor(R.color.colorPrimary));
                } else {
                    userpasswd.setBackgroundColor(Color.RED);
                    passwdcheck.setBackgroundColor(Color.RED);
                }
            }

            @Override
            public void afterTextChanged(Editable s) {
            }
        });


        // String myString = "미취학"; // 스피터 초기값
//        ArrayAdapter pAdapter = ArrayAdapter.createFromResource(this, R.array.sch, android.R.layout.simple_spinner_item);
//        pAdapter.setDropDownViewResource(android.R.layout.simple_spinner_item);
////        pAdapter = (ArrayAdapter)school_select.getAdapter();
        ArrayAdapter pAdapter = ArrayAdapter.createFromResource(this, R.array.sch, R.layout.spinner_item);
        pAdapter.setDropDownViewResource(R.layout.spinner_item);
//
//
//        int spinnerPosition = pAdapter.getPosition(myString);
        school_select.setAdapter(pAdapter);
        //school_select.setSelection(spinnerPosition);


        school_select.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                //selectedSchool =  getResources().getStringArray(R.array.sch);
                selectedSchool = school_select.getSelectedItem().toString();
                if (position == 0 || position == 4) {
                    usergrade.setEnabled(false);
                    userclass.setEnabled(false);
                    teacherid.setEnabled(false);
                    teacheridCheck.setEnabled(false);
//                    usergrade.setBackgroundColor(Color.BLACK);
//                    userclass.setBackgroundColor(Color.BLACK);
//                    teacherid.setBackgroundColor(Color.BLACK);
                } else {
                    usergrade.setEnabled(true);
                    userclass.setEnabled(true);
                    teacherid.setEnabled(true);
                    teacheridCheck.setEnabled(true);
//                    usergrade.setBackgroundColor(Color.);
//                    userclass.setBackgroundColor(Color.TRANSPARENT);
//                    teacherid.setBackgroundColor(Color.TRANSPARENT);
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });


        cancle.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
            }
        });

        join.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if( hasIdChecked==false || !inputId.equals(userid.getText().toString())){                       //아이디 중복 확인 후에 값을 바꿨을 경우 체크.
                    Toast.makeText(JoinActivity.this, "아이디 중복확인을 해주세요!", Toast.LENGTH_SHORT).show();
                    userid.requestFocus();
                    return;
                }

                if(hasTeacherIdChecked==false || !inputTeacherId.equals(teacherid.getText().toString())){                       //선생님 ID 확인 후에 값을 바꿨을 경우 체크.
                    Toast.makeText(JoinActivity.this, "선생님ID를 확인 해주세요!", Toast.LENGTH_SHORT).show();
                    userid.requestFocus();
                    return;
                }

                // 아이디 입력 확인
                if (userid.getText().toString().length() == 0) {
                    Toast.makeText(JoinActivity.this, "아이디를 입력하세요!", Toast.LENGTH_SHORT).show();
                    userid.requestFocus();
                    return;
                }

                // 비밀번호 입력 확인
                if (userpasswd.getText().toString().length() == 0) {
                    Toast.makeText(JoinActivity.this, "비밀번호를 입력하세요!", Toast.LENGTH_SHORT).show();
                    userpasswd.requestFocus();
                    return;
                }

                // 비밀번호 확인 입력 확인
                if (passwdcheck.getText().toString().length() == 0) {
                    Toast.makeText(JoinActivity.this, "비밀번호 확인을 입력하세요!", Toast.LENGTH_SHORT).show();
                    passwdcheck.requestFocus();
                    return;
                }

                // 비밀번호 일치 확인
                if (!userpasswd.getText().toString().equals(passwdcheck.getText().toString())) {
                    Toast.makeText(JoinActivity.this, "비밀번호가 일치하지 않습니다!", Toast.LENGTH_SHORT).show();
                    userpasswd.setText("");
                    passwdcheck.setText("");
                    userpasswd.requestFocus();
                    return;
                }

                // 이름 입력 확인
                if (username.getText().toString().length() == 0) {
                    Toast.makeText(JoinActivity.this, "이름을 입력하세요!", Toast.LENGTH_SHORT).show();
                    username.requestFocus();
                    return;
                }

                if (selectedSchool.equals("초등학교") || selectedSchool.equals("중학교") || selectedSchool.equals(("고등학교"))) {
                    if (usergrade.getText().toString().length() == 0) {
                        Toast.makeText(JoinActivity.this, "학년을 입력하세요!", Toast.LENGTH_SHORT).show();
                        usergrade.requestFocus();
                        return;
                    }

                    if (userclass.getText().toString().length() == 0) {
                        Toast.makeText(JoinActivity.this, "반을 입력하세요!", Toast.LENGTH_SHORT).show();
                        userclass.requestFocus();
                        return;
                    }

                    if (teacherid.getText().toString().length() == 0) {
                        Toast.makeText(JoinActivity.this, "선생님ID를 입력하세요!", Toast.LENGTH_SHORT).show();
                        teacherid.requestFocus();
                        return;
                    }
                }

                // 네트워크에 보내기
                Signup signup = new Signup();
                signup.setUser(userid.getText().toString());
                signup.setPassword(userpasswd.getText().toString());
                signup.setName(username.getText().toString());
                signup.setTeacher(teacherid.getText().toString());
                signup.setGrade(Integer.parseInt(usergrade.getText().toString()));
                signup.setSchool(school_select.getSelectedItemPosition());

                signup.setClass_num(Integer.parseInt(userclass.getText().toString()));

                Call<SignupResult> signupResultCall = networkService.getSigninResult(signup);
                signupResultCall.enqueue(new Callback<SignupResult>() {
                    @Override
                    public void onResponse(Call<SignupResult> call, Response<SignupResult> response) {
                        if (response.isSuccessful()) {
                            SignupResult signinResult = response.body();
                            Log.i("MyTag", "콘텐츠 제목 : " + signinResult);
                        } else {
                            int statusCode = response.code();
                            Log.i("MyTag", "응답코드 : " + statusCode);
                        }
                    }

                    @Override
                    public void onFailure(Call<SignupResult> call, Throwable t) {
                        Toast.makeText(getApplicationContext(), "Failed to load", Toast.LENGTH_LONG).show();
                        Log.i("MyTag", "에러내용 : " + t.getMessage());
                        finish();
                    }
                });

                // 다 입력했으면 로그인 화면으로 돌아가기
                Intent intent = new Intent(getApplicationContext(), LoginActivity.class);
                startActivity(intent);
            }
        });

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        if (isMypage == true) {
            getMenuInflater().inflate(R.menu.global, menu);
            menu.findItem(R.id.action_settings).setVisible(false);
            return super.onCreateOptionsMenu(menu);
        } else {
            getMenuInflater().inflate(R.menu.global, menu);
            return super.onCreateOptionsMenu(menu);
        }

    }

    MenuItem item1 = null;

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                onBackPressed();
                if (item1 != null)
                    item1.setVisible(true);
                return true;

        }
        return super.onOptionsItemSelected(item);
    }

    public void changeToolbar(int mode) {
        if (mode == 0) {
            getSupportActionBar().setIcon(R.drawable.ic_main_home);
            getSupportActionBar().setDisplayHomeAsUpEnabled(false);
        } else if (mode == 1) {
            getSupportActionBar().setIcon(null);
            getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        }
    }

    private void initView() {
        join = (Button) findViewById(R.id.joinbtn);
        cancle = (Button) findViewById(R.id.canclebtn);
        idcheck = (Button) findViewById(R.id.idcheck);
        teacheridCheck = (Button) findViewById(R.id.teacherid_check);
        userid = (EditText) findViewById(R.id.userid);
        userpasswd = (EditText) findViewById(R.id.userpasswd);
        passwdcheck = (EditText) findViewById(R.id.passwdcheck);
        username = (EditText) findViewById(R.id.username);
        userclass = (EditText) findViewById(R.id.userclass);
        usergrade = (EditText) findViewById(R.id.usergrade);
        teacherid = (EditText) findViewById(R.id.teacherid);
        school_select = (Spinner) findViewById(R.id.sch);
        toolbar = (Toolbar) findViewById(R.id.joinToolbar);
        toolbar_title = (TextView) findViewById(R.id.toolbar_title);
    }
}