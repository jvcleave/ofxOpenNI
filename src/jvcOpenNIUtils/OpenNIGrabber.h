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



class OpenNIGrabber
{
public:
	OpenNIGrabber();
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
	void showUser(int nID);
	void hideUser(int nID);
	
	vector<OpenNIPerson> people;
	
	
	float filterFactor;
	bool isMasking;
	bool isCloud;
};
