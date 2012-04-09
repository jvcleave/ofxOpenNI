/*
 *  OpenNIGrabber.h
 *  ofxMarchingCubesExample
 *
 *  Created by Jason Van Cleave on 3/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include "ofMain.h"
#include "ofxOpenNI.h"
#include "OpenNIPerson.h"

class OpenNIGrabberEventData  {
public:
	OpenNIGrabberEventData(int personID)
	{
		id = personID;
	}
	int id;
};

class OpenNIGrabber
{
public:
	OpenNIGrabber();
	~OpenNIGrabber();
	void setup();
	void setupWithFile(string _filename);
	void update();
	void addCallbacks();
	void draw();
	void drawUsers();
	void drawAllScreens();
	ofxOpenNIContext context;
	ofxDepthGenerator depthGenerator;
	ofxImageGenerator imageGenerator;
	ofxUserGenerator userGenerator;
	ofxHandGenerator handGenerator;
	
	void createUser(int nID);
	void deleteUser(int nID);
	void onUserReEnter(int nID);
	void onUserExit(int nID);
	
	vector<OpenNIPerson> people;
	
	
	float filterFactor;
	bool isMasking;
	bool isCloud;
	bool doAlignImageToDepth;
	ofEvent<OpenNIGrabberEventData> onPersonCreatedEventDispatcher;
	ofEvent<OpenNIGrabberEventData> onPersonDeletedEventDispatcher;
	ofEvent<OpenNIGrabberEventData> onPersonReEnterDispatcher;
	ofEvent<OpenNIGrabberEventData> onPersonExitDispatcher;

	
	
};
