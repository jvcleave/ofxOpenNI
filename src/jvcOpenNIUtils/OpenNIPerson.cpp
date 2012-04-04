/*
 *  OpenNIPerson.cpp
 *  OpenNI_Bullet
 *
 *  Created by Jason Van Cleave on 3/30/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "OpenNIPerson.h"

OpenNIPerson::OpenNIPerson()
{
	user = NULL;
	id = -1;
}
OpenNIPerson::~OpenNIPerson()
{
	cout << "OpenNIPerson destructor" << endl;
	user = NULL;
}
void OpenNIPerson::setup(int personID, ofxTrackedUser* trackedUser)
{
	id = personID;
	user = trackedUser;
}

void OpenNIPerson::update()
{
	
}

void OpenNIPerson::draw()
{

	if(user != NULL)
	{
		user->debugDraw();

	}
}