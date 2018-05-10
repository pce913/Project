package com.brave.blank.erm;

import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentStatePagerAdapter;


public class ViewPagerAdapter extends FragmentStatePagerAdapter {

    CharSequence Titles[]; // This will Store the Titles of the Tabs which are Going to be passed when ViewPagerAdapter is created
    int NumbOfTabs; // Store the number of tabs, this will also be passed when the ViewPagerAdapter is created
    BaseFragment content1;
    BaseFragment content2;

    // Build a Constructor and assign the passed Values to appropriate values in the class
    public ViewPagerAdapter(FragmentManager fm, CharSequence mTitles[], int mNumbOfTabsumb,BaseFragment content1, BaseFragment content2) {
        super(fm);

        this.Titles = mTitles;
        this.NumbOfTabs = mNumbOfTabsumb;
        this.content1 = content1;
        this.content2 = content2;
    }

    //This method return the fragment for the every position in the View Pager
    @Override
    public BaseFragment getItem(int position) {

        if(position == 0) // if the position is 0 we are returning the First tab
        {
            BaseFragment tab1 = content1;
            return tab1;
        }
        else           // As we are having 2 tabs if the position is now 0 it must be 1 so we are returning second tab
        {
           BaseFragment tab2 = content2;
           return tab2;
        }



    }

    // This method return the titles for the Tabs in the Tab Strip

    @Override
    public CharSequence getPageTitle(int position) {
        return Titles[position];
    }

    // This method return the Number of tabs for the tabs Strip

    @Override
    public int getCount() {
        return NumbOfTabs;
    }

}
