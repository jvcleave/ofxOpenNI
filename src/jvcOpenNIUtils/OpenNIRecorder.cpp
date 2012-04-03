/*
 *  OpenNIRecorder.cpp
 *  OpenNI_Bullet
 *
 *  Created by Jason Van Cleave on 4/2/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "OpenNIRecorder.h"

OpenNIRecorder::OpenNIRecorder()
{
	isRecording = false;
	context = NULL;
}

OpenNIRecorder::~OpenNIRecorder()
{

}

void OpenNIRecorder::setup(ofxOpenNIContext* contextPtr)
{
	context = contextPtr;
	recorder.setup(context, ONI_STREAMING);
}
void OpenNIRecorder::update()
{
	recorder.update();
}

void OpenNIRecorder::startRecording()
{
	recorder.startRecord(ofGetTimestampString()+".oni");
	isRecording = true;
}

void OpenNIRecorder::stopRecording()
{
	recorder.stopRecord();
	isRecording = false;
}