/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import java.util.Arrays;

import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.FacebookSdk;
import com.facebook.login.LoginManager;
import com.facebook.login.LoginResult;
import com.facebook.share.Sharer;
import com.facebook.share.model.ShareLinkContent;
import com.facebook.share.widget.ShareDialog;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import sonar.systems.framework.SonarFrameworkActivity;

public class AppActivity extends SonarFrameworkActivity {
	CallbackManager callbackManager;
	static ShareDialog shareDialog;
	
	@Override
	protected void onCreate(Bundle b) {
		// TODO Auto-generated method stub
		super.onCreate(b);
		FacebookSdk.sdkInitialize(getApplicationContext());
        callbackManager = CallbackManager.Factory.create();
        shareDialog = new ShareDialog(this);
        LoginManager.getInstance().registerCallback(callbackManager, new FacebookCallback<LoginResult>() {
            @Override
            public void onSuccess(LoginResult loginResult) {
            	
               
                
                //if (ShareDialog.canShow(ShareLinkContent.class)) {
                    
               // }
            }

            @Override
            public void onCancel() {
                 // App code
            }

            @Override
            public void onError(FacebookException exception) {
                 // App code   
            }});
       // LoginManager.getInstance().logInWithPublishPermissions(this, Arrays.asList("publish_actions"));
        // this part is optional
        shareDialog.registerCallback(callbackManager, new FacebookCallback<Sharer.Result>() {
        	 @Override
             public void onCancel() {

             }

             @Override
             public void onError(FacebookException error) {

             }

             @Override
             public void onSuccess(Sharer.Result result) {

             }

        });
	}
	
	@Override
	protected void onActivityResult(int request, int response, Intent data) {
		// TODO Auto-generated method stub
		super.onActivityResult(request, response, data);
		callbackManager.onActivityResult(request, response, data);
	}
	
	public static void shareScore(int score){
		ShareLinkContent linkContent = new ShareLinkContent.Builder()
                .setContentTitle("Zippyroid")
                .setContentDescription(
                       "I scored " + Integer.toString(score) + "!!!")
                .setContentUrl(Uri.parse("https://www.facebook.com/zippyroid"))
                .build();

        shareDialog.show(linkContent);
	}
}
