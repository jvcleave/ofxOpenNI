/*
 *  OpenNIPerson.h
 *  OpenNI_Bullet
 *
 *  Created by Jason Van Cleave on 3/30/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"
#include "ofxOpenNI.h"


class OpenNIPerson
{
public:
	OpenNIPerson();
	~OpenNIPerson();
	int id;
	void setup(int personID, ofxTrackedUser* trackedUser);
	void update();
	void draw();
	ofxTrackedUser *user;
};