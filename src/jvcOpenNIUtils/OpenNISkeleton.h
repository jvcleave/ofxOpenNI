/*
 *  OpenNISkeleton.h
 *  OpenNI_Skeleton
 *
 *  derived from https://github.com/kikko/ofApps/blob/master/openNISkeleton/src/testApp.h
 *
 */

#pragma once

#include "ofMain.h"
#include "OpenNIGrabber.h"

#define kNumBones 11

class Bone : public ofNode {
	
public:
	
	ofQuaternion bindPoseOrientation;
	
	void customDraw()
	{
		ofPushStyle();
		ofSetColor(ofColor::white);
		ofPushMatrix();
		ofTranslate(0, -20, 0);
		ofScale(3, 30, 3);
		ofBox(0, 0, 0, 1);
		ofPopMatrix();	
		ofPopStyle();
	}
};

class OpenNISkeleton
{
public:
	OpenNISkeleton();
	Bone	bones[kNumBones];
	ofxTrackedUser* user;
	int id;
	void setup(OpenNIGrabber* grabber, ofxTrackedUser* trackedUser);
	void update();
	void transformNode(int nodeNum, XnSkeletonJoint skelJoint);
	void draw();
	OpenNIGrabber* oniGrabber;
};