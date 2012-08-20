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



class OpenNIGrabber
{
public:
	OpenNIGrabber();
	~OpenNIGrabber();
	void setup();
	void setupWithFile(string _filename);
	void update();
	void start();
	void draw();
	void drawUsers();
	void drawAllScreens();
	ofxOpenNIContext context;
	ofxDepthGenerator* depthGenerator;
	ofxImageGenerator imageGenerator;
	ofxUserGenerator userGenerator;
	ofxHandGenerator handGenerator;
	
	float filterFactor;
	bool isMasking;
	bool isCloud;
	bool doAlignImageToDepth;
	bool isReady;
	
};
