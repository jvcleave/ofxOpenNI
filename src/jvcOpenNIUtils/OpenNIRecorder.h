/*
 *  OpenNIRecorder.h
 *  OpenNI_Bullet
 *
 *  Created by Jason Van Cleave on 4/2/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include "ofxOpenNI.h"


class OpenNIRecorder
{
public:
	OpenNIRecorder();
	~OpenNIRecorder();
	void setup(ofxOpenNIContext* contextPtr);
	void update();
	void startRecording();
	void stopRecording();
	ofxOpenNIRecorder	recorder;
	ofxOpenNIContext	*context;
	bool isRecording;
};