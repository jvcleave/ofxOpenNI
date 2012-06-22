/*
 *  OpenNIGrabber.cpp
 *  ofxMarchingCubesExample
 *
 *  Created by Jason Van Cleave on 3/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenNIGrabber.h"
void XN_CALLBACK_TYPE onNewUserCallback(xn::UserGenerator& rGenerator, XnUserID nID, void* pCookie)
{
	OpenNIGrabber* grabberInstance = static_cast<OpenNIGrabber*>(pCookie);
	ofLogVerbose() << "OpenNIGrabber onNewUser<< " << nID << endl;

}

// Callback: An existing user was lost
void XN_CALLBACK_TYPE onLostUserCallback(xn::UserGenerator& rGenerator, XnUserID nID, void* pCookie)
{
	OpenNIGrabber* grabberInstance = static_cast<OpenNIGrabber*>(pCookie);
	ofLogVerbose() << "OpenNIGrabber onLostUser<< " << nID << endl;

	grabberInstance->deleteUser(nID);
}

// Callback: Detected a pose
void XN_CALLBACK_TYPE onPoseDetectedCallback(xn::PoseDetectionCapability& rCapability, const XnChar* strPose, XnUserID nID, void* pCookie)
{
	OpenNIGrabber* grabberInstance = static_cast<OpenNIGrabber*>(pCookie);
	ofLogVerbose() << "OpenNIGrabber onPoseDetected: strPose<< " <<  strPose << " id: " << nID << endl;
}



void XN_CALLBACK_TYPE onCalibrationStartCallback(xn::SkeletonCapability& capability ,XnUserID nID, void* pCookie)
{
	OpenNIGrabber* grabberInstance = static_cast<OpenNIGrabber*>(pCookie);

	ofLogVerbose() << "OpenNIGrabber onCalibrationStart: << " <<  nID << endl;
}


void XN_CALLBACK_TYPE onCalibrationEndCallback(xn::SkeletonCapability& rCapability ,XnUserID nID, XnBool bSuccess, void* pCookie)
{
	OpenNIGrabber* grabberInstance = static_cast<OpenNIGrabber*>(pCookie);
	if(bSuccess) 
	{
		ofLogVerbose() << "OpenNIGrabber onCalibrationEnd success: << " <<  nID << endl;
		grabberInstance->createUser(nID);
	}else {
		ofLogVerbose() << "OpenNIGrabber onCalibrationEnd failed: << " <<  nID << endl;
	}
	
}

void XN_CALLBACK_TYPE onUserExitCallback(xn::UserGenerator& rGenerator, XnUserID nID, void* pCookie)
{
	ofLogVerbose() << " OpenNIGrabber onUserExitCallback" << endl;
	OpenNIGrabber* grabberInstance = static_cast<OpenNIGrabber*>(pCookie);
	grabberInstance->onUserExit(nID);
	
}
void XN_CALLBACK_TYPE onUserReEnterCallback(xn::UserGenerator& rGenerator, XnUserID nID, void* pCookie)
{
	ofLogVerbose() << "OpenNIGrabber onUserReEnterCallback" << endl;
	OpenNIGrabber* grabberInstance = static_cast<OpenNIGrabber*>(pCookie);
	grabberInstance->onUserReEnter(nID);

}




OpenNIGrabber::OpenNIGrabber()
{
	isReady = false;
	filterFactor = 0.1f;
	isMasking = true;
	isCloud = false;
	doAlignImageToDepth = false;
	areCallbacksActive = false;
	depthGenerator = new ofxDepthGenerator();
}
void OpenNIGrabber::setupWithFile(string _filename)
{
	context.setupUsingRecording(ofToDataPath(_filename));
	handGenerator.setup(&context, 4);
	handGenerator.setSmoothing(filterFactor);			// built in openni hand track smoothing...
	handGenerator.setFilterFactors(filterFactor);		// custom smoothing/filtering (can also set per hand with setFilterFactor)...set them all to 0.1f to begin with
	
	addCallbacks();
	isReady = true;
	
}

void OpenNIGrabber::setup()
{
	context.setup();	// all nodes created by code -> NOT using the xml config file at all
	context.setMirror(true);
	
	addCallbacks();
	isReady = true;
}
void OpenNIGrabber::addCallbacks()
{

	
	//
	depthGenerator->setup(&context);
	imageGenerator.setup(&context);
	if (doAlignImageToDepth) 
	{
		context.unregisterViewport();
	}
	userGenerator.setup(&context, 3);
	userGenerator.setUseMaskPixels(isMasking);
	userGenerator.setUseCloudPoints(isCloud);

	userGenerator.getXnUserGenerator().RegisterToUserExit(onUserExitCallback, this, user_exit_handle);
	
	userGenerator.getXnUserGenerator().RegisterToUserReEnter(onUserReEnterCallback, this, user_reenter_handle);
	
	userGenerator.getXnUserGenerator().RegisterUserCallbacks(onNewUserCallback, onLostUserCallback, this, user_cb_handle);
	
	userGenerator.getXnUserGenerator().GetSkeletonCap().RegisterCalibrationCallbacks(onCalibrationStartCallback, onCalibrationEndCallback, this, calibration_cb_handle);
	
	userGenerator.setSmoothing(filterFactor);
	areCallbacksActive = true;
	//context.toggleRegisterViewport();
}


void OpenNIGrabber::update()
{
	if(!isReady) return;
	context.update();
	depthGenerator->update();
	imageGenerator.update();
	userGenerator.update();	
}

void OpenNIGrabber::draw()
{
	if(!isReady) return;

	if (people.size()==0) 
	{
		depthGenerator->draw(0, 0, 640, 480);
	}
	drawUsers();
}

void OpenNIGrabber::drawUsers()
{
	if(!isReady) return;

	for(int i=0; i<people.size(); i++)
	{
		people[i].draw();
	}
	
}

void OpenNIGrabber::drawAllScreens()
{
	if(!isReady) return;

		imageGenerator.draw(0, 0, 640, 480);
		depthGenerator->draw(640, 0, 640, 480);
		ofPushMatrix();
			ofTranslate(0, 480, 0);
			userGenerator.draw();
		ofPopMatrix();
	
		ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
			ofPushMatrix();
				ofTranslate(640, 480, 0);				
					imageGenerator.draw(0, 0, 640, 480);
					depthGenerator->draw(0, 0, 640, 480);
					userGenerator.draw();
			ofPopMatrix();
		ofDisableBlendMode();
}
void OpenNIGrabber::createUser(int nID)
{
	ofLogVerbose() << "OpenNIGrabber createUser: " << endl;
	
	OpenNIPerson person;
	person.setup(nID, userGenerator.getTrackedUser(nID));
	people.push_back(person);
	OpenNIGrabberEventData eventData(nID);
	ofNotifyEvent(onPersonCreatedEventDispatcher, eventData);
	
	
}

void OpenNIGrabber::deleteUser(int nID)
{
	ofLogVerbose() << "OpenNIGrabber deleteUser: " << endl;
	bool wasPersonDeleted = false;
	int idOfDeletedPerson = -1;
	for (int i = 0; i<people.size(); i++) 
	{
		if (people[i].id == nID) 
		{
			wasPersonDeleted = true;
			people.erase(people.begin() +i);

		}
		
	}
	if (wasPersonDeleted) 
	{
		OpenNIGrabberEventData eventData(nID);
		ofNotifyEvent(onPersonDeletedEventDispatcher, eventData);
	}
	
	
}
void OpenNIGrabber::onUserReEnter(int nID)
{
	ofLogVerbose() << "OpenNIGrabber onUserReEnter: " << endl;
	OpenNIGrabberEventData eventData(nID);
	ofNotifyEvent(onPersonReEnterDispatcher, eventData);
}
void OpenNIGrabber::onUserExit(int nID)
{
	ofLogVerbose() << "OpenNIGrabber onUserExit: " << endl;
	OpenNIGrabberEventData eventData(nID);
	ofNotifyEvent(onPersonExitDispatcher, eventData);
}

OpenNIGrabber::~OpenNIGrabber()
{
	ofLogVerbose() << "~OpenNIGrabber" << endl;
	if (areCallbacksActive) 
	{
		userGenerator.getXnUserGenerator().UnregisterFromUserExit(user_exit_handle);
		
		userGenerator.getXnUserGenerator().UnregisterFromUserReEnter(user_reenter_handle);
		
		userGenerator.getXnUserGenerator().UnregisterUserCallbacks(user_cb_handle);
		
		userGenerator.getXnUserGenerator().GetSkeletonCap().UnregisterCalibrationCallbacks(calibration_cb_handle);
		areCallbacksActive = false;
	}

	context.shutdown();
	delete depthGenerator;
	depthGenerator = NULL;
}

