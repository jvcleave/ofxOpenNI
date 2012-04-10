/*
 *  OpenNISkeleton.cpp
 *  OpenNI_Skeleton
 *
 *  Created by Jason Van Cleave on 4/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "OpenNISkeleton.h"


OpenNISkeleton::OpenNISkeleton()
{
	for(int i=0; i<kNumBones; i++) {
		
		bones[i].setPosition(ofRandomf()*10-5, ofRandomf()*10-5, ofRandomf()*10-5);
		bones[i].setScale(10);
		
		// setup a traditional humanoid bind pose
		
		// LEFT ARM
		if(i==2||i==4){
			bones[i].bindPoseOrientation.makeRotate(-90.0, ofVec3f(0.0f, 0.0f, 1.0f));
			// RIGHT ARM
		} else if(i==3||i==5){
			bones[i].bindPoseOrientation.makeRotate(90.0, ofVec3f(0.0f, 0.0f, 1.0f));
			// NECK
		} else if(i==10){
			bones[i].bindPoseOrientation.makeRotate(180.0, ofVec3f(0.0f, 0.0f, 1.0f));
		} else {
			bones[i].bindPoseOrientation.set(0, 0, 0, 1);
		}
	}
}

void OpenNISkeleton::setup(OpenNIGrabber* grabber, ofxTrackedUser* trackedUser)
{
	oniGrabber = grabber;
	user = trackedUser;
	id = user->id;
}
void OpenNISkeleton::update()
{
	if (user != NULL) 
	{
		transformNode(0, XN_SKEL_TORSO);
		transformNode(1, XN_SKEL_WAIST);
		transformNode(2, XN_SKEL_LEFT_SHOULDER);
		transformNode(3, XN_SKEL_RIGHT_SHOULDER);
		transformNode(4, XN_SKEL_LEFT_ELBOW);
		transformNode(5, XN_SKEL_RIGHT_ELBOW);
		transformNode(6, XN_SKEL_LEFT_HIP);
		transformNode(7, XN_SKEL_RIGHT_HIP);
		transformNode(8, XN_SKEL_LEFT_KNEE);
		transformNode(9, XN_SKEL_RIGHT_KNEE);
		transformNode(10, XN_SKEL_NECK);
	}
}
void OpenNISkeleton::transformNode(int nodeNum, XnSkeletonJoint skelJoint)
{
	// Adapted code from OpenNI Simbad example

	XnUserID userId = user->id;
	
	// Get the openNI bone info	
	xn::SkeletonCapability pUserSkel = oniGrabber->userGenerator.getXnUserGenerator().GetSkeletonCap();		
	
	XnSkeletonJointOrientation jointOri;
	pUserSkel.GetSkeletonJointOrientation(userId, skelJoint, jointOri);
	
	XnSkeletonJointPosition jointPos;
	pUserSkel.GetSkeletonJointPosition(userId, skelJoint, jointPos);
	
	if(jointOri.fConfidence > 0 )
	{
		float * oriM = jointOri.orientation.elements;
		
		ofMatrix4x4 rotMatrix;
		
		// Create a 4x4 rotation matrix (converting row to column-major)
		rotMatrix.set(oriM[0], oriM[3], oriM[6], 0.0f,
					  oriM[1], oriM[4], oriM[7], 0.0f,
					  oriM[2], oriM[5], oriM[8], 0.0f,
					  0.0f, 0.0f, 0.0f, 1.0f);
		
		ofQuaternion q = rotMatrix.getRotate();
		
		bones[nodeNum].setPosition(jointPos.position.X, jointPos.position.Y, jointPos.position.Z);
		
		// apply skeleton pose relatively to the bone bind pose
		// /!\ WARNING the order of the quat' multiplication does mater!!
		bones[nodeNum].setOrientation(bones[nodeNum].bindPoseOrientation*q);
	}
}

void OpenNISkeleton::draw()
{
	//glEnable(GL_DEPTH_TEST);
	for(int i=0; i<kNumBones; i++)
	{
		bones[i].draw();
	}
	//glDisable(GL_DEPTH_TEST);
}
