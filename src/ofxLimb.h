/*
 *  ofxLimb.h
 *  OpenNI_Skeleton
 *
 *  Created by Jason Van Cleave on 4/9/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include <XnOpenNI.h>
#include <XnCppWrapper.h>
#include "ofMain.h"

class  ofxLimb {
public:
	ofTrueTypeFont font;
	ofxLimb(XnSkeletonJoint nStartJoint, XnSkeletonJoint nEndJoint)
	:start_joint(nStartJoint)
	,end_joint(nEndJoint)
	,found(false)
	{
		position[0].X = position[1].X = 0;
		position[0].Y = position[1].Y = 0;
		position[0].Z = position[1].Z = 0;
		font.loadFont("frabk.ttf", 24);

	}
	
	ofxLimb(){};
	~ofxLimb(){};
	
	XnSkeletonJoint start_joint;
	XnSkeletonJoint end_joint;
	XnPoint3D position[2];
	bool found;
	ofVec3f begin;
	ofVec3f end;
	float angle;
	void debugDraw(bool doFont = false) 
	{
		if(!found)
		{
			return;
		}
		ofVec3f a(position[0].X, position[0].Y);
		ofVec3f b(position[1].X, position[1].Y);
		
		ofVec3f normal = b - a;
		
		float height = normal.length();
		
		ofPushStyle();
		ofPushMatrix();
			ofSetLineWidth(5);
			ofSetColor(ofColor::red);
			glBegin(GL_LINES);
				glVertex2i(position[0].X, position[0].Y);
				glVertex2i(position[1].X, position[1].Y);
			glEnd();
			ofPopMatrix();
		ofPopStyle();
		
	
		normal.normalize();
		
		ofVec3f forward(0, -1, 0);
		ofVec3f axis = forward.crossed(normal);
		float angle = forward.angle(normal);

		/*if (doFont)
		{
			font.drawString(ofToString(angle, 1), begin.x+30, begin.y);
			
			font.drawString(ofToString(angle), 20, 70);
			ofPushMatrix();
			ofPushStyle();
			ofSetColor(ofColor::black);
			ofTranslate(a.x, a.y);  
			ofRotateY(angle);
			//( angle, axis.x, axis.y,axis.z);
			//ofRotate( angle,axis.x,axis.y,axis.z); 
			
			ofPopStyle();
			ofPopMatrix();
		}*/

	}
	
};