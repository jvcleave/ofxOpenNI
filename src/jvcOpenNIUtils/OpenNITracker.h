/*
 *  OpenNITracker.h
 *  jvcOpenNI
 *
 *  Created by jason van cleave on 6/24/12.
 *  Copyright 2012 jasonvancleave.com. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxOpenNI.h"
#include "OpenNIPerson.h"
#include "OpenNIGrabber.h"

class OpenNITrackerEventData  {
public:
	OpenNITrackerEventData(int personID)
	{
		id = personID;
	}
	int id;
};

class OpenNITracker
{
public:
	OpenNITracker();
	~OpenNITracker();
	void setup(OpenNIGrabber *openNIGrabber);
	void update();
	void draw();
	void createUser(int nID);
	void createTrackedUser(int nID);
	void deleteUser(int nID);
	void onUserReEnter(int nID);
	void onUserExit(int nID);
	OpenNIGrabber* grabber;
	
	void addCallbacks();
	
	vector<OpenNIPerson> people;
	ofxUserGenerator* userGenerator;
	ofEvent<OpenNITrackerEventData> onPersonCreatedEventDispatcher;
	ofEvent<OpenNITrackerEventData> onPersonDeletedEventDispatcher;
	ofEvent<OpenNITrackerEventData> onPersonReEnterDispatcher;
	ofEvent<OpenNITrackerEventData> onPersonExitDispatcher;
	XnCallbackHandle user_cb_handle;
	XnCallbackHandle user_exit_handle;
	XnCallbackHandle user_reenter_handle;
	XnCallbackHandle calibration_cb_handle;
	
	bool areCallbacksActive;

};