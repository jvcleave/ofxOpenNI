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
	trackedUser = NULL;
	userGenerator = NULL;
	skeleton  = NULL;
	id = -1;
}
OpenNIPerson::~OpenNIPerson()
{
	cout << "OpenNIPerson destructor" << endl;
	trackedUser = NULL;
}
void OpenNIPerson::setup(int personID, ofxUserGenerator* userGen)
{
	id = personID;
	userGenerator = userGen;
	
}

void OpenNIPerson::addSkeleton()
{
	trackedUser = userGenerator->getTrackedUser(id);
	skeleton = new OpenNISkeleton();
	skeleton->setup(userGenerator, trackedUser);
}
void OpenNIPerson::update()
{
	image.setFromPixels(userGenerator->getUserPixels(id), 640, 480, OF_IMAGE_GRAYSCALE);

}

void OpenNIPerson::draw(int x, int y)
{
	ofPushMatrix();
	ofTranslate(x, y, 0);
		image.draw(0, 0);
		if(trackedUser != NULL)
		{
			trackedUser->debugDraw();

		}
		if (skeleton != NULL)
		{
			skeleton->draw();
		}
	ofPopMatrix();
}

void OpenNIPerson::draw()
{
	draw(0, 480);
}