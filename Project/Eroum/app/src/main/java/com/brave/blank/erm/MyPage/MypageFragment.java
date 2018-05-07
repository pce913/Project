package com.brave.blank.erm.MyPage;

import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.support.v4.graphics.drawable.RoundedBitmapDrawable;
import android.support.v4.graphics.drawable.RoundedBitmapDrawableFactory;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.brave.blank.erm.AssembledData;
import com.brave.blank.erm.BaseFragment;
import com.brave.blank.erm.Login.LoginActivity;
import com.brave.blank.erm.Network.ApplicationController;
import com.brave.blank.erm.Network.NetworkService;
import com.brave.blank.erm.R;
import com.brave.blank.erm.StoredExercise.StoredExerciseFragment;
import com.brave.blank.erm.record.PracticeRecordFragment;
import com.bumptech.glide.Glide;
import com.bumptech.glide.request.target.BitmapImageViewTarget;

/**
 * Created by chanung on 2016-07-28.
 */
public class MypageFragment extends BaseFragment {

    StoredExerciseFragment storedExerciseFragment;
    private static final int PICK_FROM_GALLERY = 1;
    Button gallery;
    ImageView userImg, storeContents, recordhomeclass;
    View view;
    TextView btn_logout;
    MypageFragment mypageFragment = this;
    private static MenuItem mypageItem;
    private static int myflag;
    // SharedPreferences sharedPreferences;

    // network code added
    private NetworkService networkService;
    //  List<Writing> writings;
    //   List<Speaking> speakings;

    @Override
    public View onCreateView(final LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        view = inflater.inflate(R.layout.fragment_mypage, container, false);
        userImg = (ImageView) view.findViewById(R.id.userimg);
        storeContents = (ImageView) view.findViewById(R.id.store_content);
        recordhomeclass = (ImageView) view.findViewById(R.id.record_homeclass);
        btn_logout = (TextView) view.findViewById(R.id.logout);

        storedExerciseFragment = new StoredExerciseFragment();

        initNetworkService();
        //networkWriting();
        // networkSpeaking();

        // 갤러리에서 이미지 불러오기
        gallery = (Button) view.findViewById(R.id.gallerybtn);
        gallery.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                // Gallery 호출
                intent.setType("image/*");
                intent.setAction(Intent.ACTION_GET_CONTENT);
                // 잘라내기 셋팅
                intent.putExtra("crop", "true");
                intent.putExtra("aspectX", 0);
                intent.putExtra("aspectY", 0);
                intent.putExtra("outputX", 200);
                intent.putExtra("outputY", 150);
                try {
                    intent.putExtra("return-data", true);
                    startActivityForResult(Intent.createChooser(intent,
                            "Complete action using"), (PICK_FROM_GALLERY));
                } catch (ActivityNotFoundException e) {
                    Log.i("MyTag", "갤러리 사진 가져오기 에러");
                }
            }
        });

        storeContents.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                getFragmentManager().beginTransaction().replace(R.id.container, storedExerciseFragment).commit();
            }
        });

        recordhomeclass.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startFragment(getFragmentManager(), PracticeRecordFragment.class);
            }
        });

        btn_logout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
//                SharedPreferences.Editor editor = sharedPreferences.edit();
                // editor.putInt("isLogin", 0);
                // editor.commit();
                Intent intent = new Intent(v.getContext(), LoginActivity.class);

                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);               //모든 activity 스택을 지우는 플래그
                startActivity(intent);
                finishFragment();

                //  getActivity().getSupportFragmentManager().beginTransaction().remove(mypageFragment).commit();
            }
        });

        AssembledData.flag = myflag;
        view.setFocusableInTouchMode(true);
        view.requestFocus();
        view.setOnKeyListener(new View.OnKeyListener() {
            @Override
            public boolean onKey(View v, int keyCode, KeyEvent event) {
                if (keyCode == KeyEvent.KEYCODE_BACK) {
                    Log.d("keyname", "backkey");
                    mypageItem.setVisible(true);
                    if (AssembledData.flag == 1) {
                        finishFragment();

                    } else
                        getActivity().finish();
                    return true;
                } else
                    return false;
            }
        });
        return view;
    }

    public void onActivityResult(int requestCode,
                                 int resultCode,
                                 Intent data) {

        if (requestCode == PICK_FROM_GALLERY) {
            if (data == null) {
                return;
            }
            Bundle extras2 = data.getExtras();
            if (extras2 != null) {
                Bitmap photo = extras2.getParcelable("data");
                //userImg.setImageBitmap(photo);

//                Glide.with(MypageFragment.this).load(photo).asBitmap().centerCrop().into(new BitmapImageViewTarget(userImg) {
//                    @Override
//                    protected void setResource(Bitmap resource) {
//                        RoundedBitmapDrawable circularBitmapDrawable =
//                                RoundedBitmapDrawableFactory.create(getResources(), resource);
//                        circularBitmapDrawable.setCircular(true);
//                        userImg.setImageDrawable(circularBitmapDrawable);
//                    }
//                });

                RoundedBitmapDrawable bitmapDrawable = RoundedBitmapDrawableFactory.create(getResources(), photo);
                bitmapDrawable.setCornerRadius(Math.max(photo.getWidth(), photo.getHeight()) / 2.0f);
                bitmapDrawable.setAntiAlias(true);
                userImg.setImageDrawable(bitmapDrawable);
            } else {
                Log.i("MyTag", "사진 불러오지 않음");
            }
        }
    }


    private void initNetworkService() {
        // TODO: 13. ApplicationController 객체를 이용하여 NetworkService 가져오기
        networkService = ApplicationController.getInstance().getNetworkService();
    }

    public static void setMypageItem(MenuItem item, int _flag) {
        mypageItem = item;
        MypageFragment.myflag = _flag;
    }

    public static MenuItem getMypageItem() {
        return mypageItem;
    }


//    public void networkWriting(){
//        Call<List<Writing>> writingCall=networkService.getWriting(Token.getToken(), true);   //4, true      7, false //받아쓰기 true  , 말해보기 false 라고 알려줬지만 그 반대로 해야함.
//        writingCall.enqueue(new Callback<List<Writing>>() {
//            @Override
//            public void onResponse(Call<List<Writing>> call, Response<List<Writing>> response) {
//                int statusCode = response.code();
//                if(response.isSuccessful()){
//                    Log.d("MyTag", "성공! Writing 응답코드 : : "+ statusCode );
//                    writings=response.body();
//                    AssembledData.setWritingList(writings);
//                    // 네트워크 성공시에 대부분의 작업은 이 부분에서 하게 됨.
//                }
//                else{
//                    Log.d("MyTag", "응답코드 : " + statusCode);
//                }
//            }
//            @Override
//            public void onFailure(Call<List<Writing>> call, Throwable t) {
//                Log.d("MyTag","Writing 에러내용 : " + t.getMessage());
//            }
//        });
//    }
//
//
//    public void networkSpeaking(){
//        Call<List<Speaking>> speakingCall=networkService.getSpeaking(Token.getToken(), false);               //7 false    4 true
//        speakingCall.enqueue(new Callback<List<Speaking>>() {
//            @Override
//            public void onResponse(Call<List<Speaking>> call, Response<List<Speaking>> response) {
//                int statusCode = response.code();
//                if(response.isSuccessful()){
//                    Log.d("MyTag", "성공! Speaking 응답코드 : : "+ statusCode );
//                    speakings=response.body();
//                    AssembledData.setSpeakingList(speakings);
//                }
//                else{
//                    Log.d("MyTag", "응답코드 : " + statusCode);
//                }
//            }
//            @Override
//            public void onFailure(Call<List<Speaking>> call, Throwable t) {
//                Log.d("MyTag","에러내용 : " + t.getMessage());
//            }
//        });
//    }
}