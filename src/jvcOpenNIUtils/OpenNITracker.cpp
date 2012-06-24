/*
 *  OpenNITracker.cpp
 *  jvcOpenNI
 *
 *  Created by jason van cleave on 6/24/12.
 *  Copyright 2012 jasonvancleave.com. All rights reserved.
 *
 */

#include "OpenNITracker.h"

void XN_CALLBACK_TYPE onNewUserCallback(xn::UserGenerator& rGenerator, XnUserID nID, void* pCookie)
{
	OpenNITracker* grabberInstance = static_cast<OpenNITracker*>(pCookie);
	ofLogVerbose() << "OpenNITracker onNewUser<< " << nID << endl;
	grabberInstance->createUser(nID);
}

// Callback: An existing user was lost
void XN_CALLBACK_TYPE onLostUserCallback(xn::UserGenerator& rGenerator, XnUserID nID, void* pCookie)
{
	OpenNITracker* grabberInstance = static_cast<OpenNITracker*>(pCookie);
	ofLogVerbose() << "OpenNITracker onLostUser<< " << nID << endl;
	
	grabberInstance->deleteUser(nID);
}

// Callback: Detected a pose
void XN_CALLBACK_TYPE onPoseDetectedCallback(xn::PoseDetectionCapability& rCapability, const XnChar* strPose, XnUserID nID, void* pCookie)
{
	OpenNITracker* grabberInstance = static_cast<OpenNITracker*>(pCookie);
	ofLogVerbose() << "OpenNITracker onPoseDetected: strPose<< " <<  strPose << " id: " << nID << endl;
}



void XN_CALLBACK_TYPE onCalibrationStartCallback(xn::SkeletonCapability& capability ,XnUserID nID, void* pCookie)
{
	OpenNITracker* grabberInstance = static_cast<OpenNITracker*>(pCookie);
	
	ofLogVerbose() << "OpenNITracker onCalibrationStart: << " <<  nID << endl;
}


void XN_CALLBACK_TYPE onCalibrationEndCallback(xn::SkeletonCapability& rCapability ,XnUserID nID, XnBool bSuccess, void* pCookie)
{
	OpenNITracker* grabberInstance = static_cast<OpenNITracker*>(pCookie);
	if(bSuccess) 
	{
		ofLogVerbose() << "OpenNITracker onCalibrationEnd success: << " <<  nID << endl;
		grabberInstance->createTrackedUser(nID);
	}else {
		ofLogVerbose() << "OpenNITracker onCalibrationEnd failed: << " <<  nID << endl;
	}
	
}

void XN_CALLBACK_TYPE onUserExitCallback(xn::UserGenerator& rGenerator, XnUserID nID, void* pCookie)
{
	ofLogVerbose() << " OpenNITracker onUserExitCallback" << endl;
	OpenNITracker* grabberInstance = static_cast<OpenNITracker*>(pCookie);
	grabberInstance->onUserExit(nID);
	
}
void XN_CALLBACK_TYPE onUserReEnterCallback(xn::UserGenerator& rGenerator, XnUserID nID, void* pCookie)
{
	ofLogVerbose() << "OpenNITracker onUserReEnterCallback" << endl;
	OpenNITracker* grabberInstance = static_cast<OpenNITracker*>(pCookie);
	grabberInstance->onUserReEnter(nID);
	
}

OpenNITracker::OpenNITracker()
{
	grabber = NULL;
	areCallbacksActive = false;
}
OpenNITracker::~OpenNITracker()
{
	if (areCallbacksActive) 
	{
		userGenerator->getXnUserGenerator().UnregisterFromUserExit(user_exit_handle);
		
		userGenerator->getXnUserGenerator().UnregisterFromUserReEnter(user_reenter_handle);
		
		userGenerator->getXnUserGenerator().UnregisterUserCallbacks(user_cb_handle);
		
		userGenerator->getXnUserGenerator().GetSkeletonCap().UnregisterCalibrationCallbacks(calibration_cb_handle);
		areCallbacksActive = false;
	}
}

void OpenNITracker::setup(OpenNIGrabber *openNIGrabber)
{
	grabber = openNIGrabber;
	userGenerator = &grabber->userGenerator;
	addCallbacks();
}

void OpenNITracker::update()
{
	for (int i = 0; i<people.size(); i++) 
	{
		people[i].update();
	}
}

void OpenNITracker::draw()
{
	for(int i=0; i<people.size(); i++)
	{
		people[i].draw();
	}
}
void OpenNITracker::addCallbacks()
{
	userGenerator->getXnUserGenerator().RegisterToUserExit(onUserExitCallback, this, user_exit_handle);
	
	userGenerator->getXnUserGenerator().RegisterToUserReEnter(onUserReEnterCallback, this, user_reenter_handle);
	
	userGenerator->getXnUserGenerator().RegisterUserCallbacks(onNewUserCallback, onLostUserCallback, this, user_cb_handle);
	
	userGenerator->getXnUserGenerator().GetSkeletonCap().RegisterCalibrationCallbacks(onCalibrationStartCallback, onCalibrationEndCallback, this, calibration_cb_handle);
	
	areCallbacksActive = true;
}

void OpenNITracker::createUser(int nID)
{
	ofLogVerbose() << "OpenNITracker createUser: " << endl;
	
	OpenNIPerson person;
	person.setup(nID, userGenerator);
	people.push_back(person);
	OpenNITrackerEventData eventData(nID);
	ofNotifyEvent(onPersonCreatedEventDispatcher, eventData);
	
	
}
void OpenNITracker::createTrackedUser(int nID)
{
	ofLogVerbose() << "OpenNITracker createTrackedUser: " << endl;
	for (int i=0; i<people.size(); i++)
	{
		if (people[i].id = nID)
		{
			people[i].addSkeleton();
			break;
		}
	}

	
	
}
void OpenNITracker::deleteUser(int nID)
{
	ofLogVerbose() << "OpenNITracker deleteUser: " << endl;
	bool wasPersonDeleted = false;
	int idOfDeletedPerson = -1;
	for (int i = 0; i<people.size(); i++) 
	{
		if (people[i].id == nID) 
		{
			wasPersonDeleted = true;
			people.erase(people.begin() +i);
			break;
		}
		
	}
	if (wasPersonDeleted) 
	{
		OpenNITrackerEventData eventData(nID);
		ofNotifyEvent(onPersonDeletedEventDispatcher, eventData);
	}
	
	
}
void OpenNITracker::onUserReEnter(int nID)
{
	ofLogVerbose() << "OpenNITracker onUserReEnter: " << endl;
	OpenNITrackerEventData eventData(nID);
	ofNotifyEvent(onPersonReEnterDispatcher, eventData);
}
void OpenNITracker::onUserExit(int nID)
{
	ofLogVerbose() << "OpenNITracker onUserExit: " << endl;
	OpenNITrackerEventData eventData(nID);
	ofNotifyEvent(onPersonExitDispatcher, eventData);
}
