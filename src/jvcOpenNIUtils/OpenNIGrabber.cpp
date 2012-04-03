/*
 *  OpenNIGrabber.cpp
 *  ofxMarchingCubesExample
 *
 *  Created by Jason Van Cleave on 3/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenNIGrabber.h"
void XN_CALLBACK_TYPE onNewUser(xn::UserGenerator& rGenerator, XnUserID nID, void* pCookie)
{
	OpenNIGrabber* grabberInstance = static_cast<OpenNIGrabber*>(pCookie);
	cout << "OpenNIGrabber onNewUser<< " << nID << endl;

	//grabberInstance->createUser(nID);
}

// Callback: An existing user was lost
void XN_CALLBACK_TYPE onLostUser(xn::UserGenerator& rGenerator, XnUserID nID, void* pCookie)
{
	OpenNIGrabber* grabberInstance = static_cast<OpenNIGrabber*>(pCookie);
	cout << "OpenNIGrabber onLostUser<< " << nID << endl;

	grabberInstance->deleteUser(nID);
}

// Callback: Detected a pose
void XN_CALLBACK_TYPE onPoseDetected(xn::PoseDetectionCapability& rCapability, const XnChar* strPose, XnUserID nID, void* pCookie)
{
	OpenNIGrabber* grabberInstance = static_cast<OpenNIGrabber*>(pCookie);
	cout << "OpenNIGrabber onPoseDetected: strPose<< " <<  strPose << " id: " << nID << endl;

	
}



void XN_CALLBACK_TYPE onCalibrationStart(xn::SkeletonCapability& capability ,XnUserID nID, void* pCookie)
{
	OpenNIGrabber* grabberInstance = static_cast<OpenNIGrabber*>(pCookie);

	cout << "OpenNIGrabber onCalibrationStart: << " <<  nID << endl;
}


void XN_CALLBACK_TYPE onCalibrationEnd(xn::SkeletonCapability& rCapability ,XnUserID nID, XnBool bSuccess, void* pCookie)
{
	OpenNIGrabber* grabberInstance = static_cast<OpenNIGrabber*>(pCookie);
	if(bSuccess) 
	{
		cout << "OpenNIGrabber onCalibrationEnd success: << " <<  nID << endl;
		grabberInstance->createUser(nID);
	}else {
		cout << "OpenNIGrabber onCalibrationEnd failed: << " <<  nID << endl;
	}
	
}

void XN_CALLBACK_TYPE onUserExit(xn::UserGenerator& rGenerator, XnUserID nID, void* pCookie)
{
	cout << " OpenNIGrabber USER LEFT" << endl;
	//grabberInstance->hideUser(nID);
	
}
void XN_CALLBACK_TYPE onUserReEnter(xn::UserGenerator& rGenerator, XnUserID nID, void* pCookie)
{
	cout << "OpenNIGrabber USER RE_ENTERED" << endl;
	OpenNIGrabber* grabberInstance = static_cast<OpenNIGrabber*>(pCookie);
	grabberInstance->showUser(nID);
}




OpenNIGrabber::OpenNIGrabber()
{
	filterFactor = 0.1f;
	isMasking = true;
	isCloud = false;
}
void OpenNIGrabber::setupWithFile(string _filename)
{
	context.setupUsingRecording(ofToDataPath(_filename));
	
	handGenerator.setup(&context, 4);
	handGenerator.setSmoothing(filterFactor);			// built in openni hand track smoothing...
	handGenerator.setFilterFactors(filterFactor);		// custom smoothing/filtering (can also set per hand with setFilterFactor)...set them all to 0.1f to begin with
	
	addCallbacks();
	
}

void OpenNIGrabber::setup()
{
	context.setup();	// all nodes created by code -> NOT using the xml config file at all
	context.setMirror(true);
	
	addCallbacks();
}
void OpenNIGrabber::addCallbacks()
{
	depthGenerator.setup(&context);
	imageGenerator.setup(&context);
	
	context.toggleRegisterViewport();
	
	userGenerator.setup(&context);
	userGenerator.setUseMaskPixels(isMasking);
	userGenerator.setUseCloudPoints(isCloud);
	XnCallbackHandle user_cb_handle;
	XnCallbackHandle user_exit_handle;
	userGenerator.getXnUserGenerator().RegisterToUserExit(onUserExit, this, user_exit_handle);
	
	XnCallbackHandle user_reenter_handle;
	userGenerator.getXnUserGenerator().RegisterToUserReEnter(onUserReEnter, this, user_reenter_handle);
	
	userGenerator.getXnUserGenerator().RegisterUserCallbacks(onNewUser, onLostUser, this, user_cb_handle);
	
	XnCallbackHandle calibration_cb_handle;
	userGenerator.getXnUserGenerator().GetSkeletonCap().RegisterCalibrationCallbacks(onCalibrationStart, onCalibrationEnd, this, calibration_cb_handle);
	
	userGenerator.setSmoothing(filterFactor);
}
void OpenNIGrabber::update()
{
	context.update();
	depthGenerator.update();
	imageGenerator.update();
	userGenerator.update();
	

	
	
}

void OpenNIGrabber::draw()
{
	if (people.size()==0) 
	{
		depthGenerator.draw(0, 0, 640, 480);

	}
	drawUsers();
}
void OpenNIGrabber::drawUsers()
{
	for(int i=0; i<people.size(); i++)
	{
		people[i].draw();
	}
	
}

void OpenNIGrabber::drawAllScreens()
{
	imageGenerator.draw(0, 0, 640, 480);
	depthGenerator.draw(640, 0, 640, 480);
	ofPushMatrix();
	ofTranslate(0, 480, 0);
	userGenerator.draw();
	ofPopMatrix();
	
	ofPushMatrix();
	ofTranslate(640, 480, 0);
	ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
	imageGenerator.draw(0, 0, 640, 480);
	depthGenerator.draw(0, 0, 640, 480);
	ofDisableBlendMode();
	userGenerator.draw();
	ofPopMatrix();
	
}
void OpenNIGrabber::createUser(int nID)
{
	
	OpenNIPerson person;
	person.setup(nID, userGenerator.getTrackedUser(nID));
	people.push_back(person);
	cout << "OpenNIGrabber createUser: " << endl;
	
}

void OpenNIGrabber::deleteUser(int nID)
{
	cout << "OpenNIGrabber deleteUser: " << endl;
	for (int i = 0; i<people.size(); i++) 
	{
		if (people[i].id == nID) 
		{
			people.erase(people.begin() +i);
		}
		
	}
}
void OpenNIGrabber::showUser(int nID)
{
	cout << "OpenNIGrabber showUser: " << endl;
}
void OpenNIGrabber::hideUser(int nID)
{
	cout << "OpenNIGrabber hideUser: " << endl;
}

