package com.ircad.test;

public class MyActivity extends android.app.NativeActivity {

    static {
       System.loadLibrary("IGTLMobile"); 
       System.loadLibrary("OpenIGTLink");
    }
 }
