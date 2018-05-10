package com.brave.blank.erm;

import android.support.v4.app.FragmentManager;
import android.support.v4.app.Fragment;

/**
 * Created by jeonyongjin on 2016. 7. 28..
 */
public class BaseFragment extends Fragment{
    protected void startFragment(FragmentManager fm, Class<? extends BaseFragment> fragmentClass){
        BaseFragment fragment = null;
        try{
            fragment = fragmentClass.newInstance();
        }
        catch (java.lang.InstantiationException e){
            e.printStackTrace();
        }
        catch (IllegalAccessException e){
            e.printStackTrace();
        }
        if(fragment == null) {
            throw new IllegalStateException("cannot start fragment." + fragmentClass.getName());
        }
        getActivity().getSupportFragmentManager().beginTransaction().replace(R.id.container,fragment).addToBackStack(null).commit();

    }
    protected void finishFragment(){
        getFragmentManager().popBackStack();
    }
    public void onPressedBackkey(){
        finishFragment();
    }
    public void getRecordText(String string){};
}
