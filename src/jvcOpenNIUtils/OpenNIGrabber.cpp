/*
 *  OpenNIGrabber.cpp
 *  ofxMarchingCubesExample
 *
 *  Created by Jason Van Cleave on 3/29/12.
 *
 */
#include "OpenNIGrabber.h"

OpenNIGrabber::OpenNIGrabber()
{
	isReady = false;
	filterFactor = 0.1f;
	isMasking = true;
	isCloud = false;
	doAlignImageToDepth = true;
	depthGenerator = new ofxDepthGenerator();
}
void OpenNIGrabber::setupWithFile(string _filename)
{
	context.setupUsingRecording(ofToDataPath(_filename));
	handGenerator.setup(&context, 4);
	handGenerator.setSmoothing(filterFactor);			// built in openni hand track smoothing...
	handGenerator.setFilterFactors(filterFactor);		// custom smoothing/filtering (can also set per hand with setFilterFactor)...set them all to 0.1f to begin with
	
	start();
	
}

void OpenNIGrabber::setup()
{
	context.setup();	// all nodes created by code -> NOT using the xml config file at all
	context.setMirror(true);
	if (doAlignImageToDepth) 
	{
		context.unregisterViewport();
	}
	start();
	
}

void OpenNIGrabber::start()
{
	
	depthGenerator->setup(&context);
	imageGenerator.setup(&context);
	userGenerator.setup(&context, 3);
	userGenerator.setUseMaskPixels(isMasking);
	userGenerator.setUseCloudPoints(isCloud);
	userGenerator.setSmoothing(filterFactor);
	isReady = true;
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

	depthGenerator->draw(0, 0, 640, 480);
}



void OpenNIGrabber::drawAllScreens()
{
	if(!isReady) return;
	ofPushStyle();
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
	ofPopStyle();
}

OpenNIGrabber::~OpenNIGrabber()
{
	ofLogVerbose() << "~OpenNIGrabber" << endl;
	

	context.shutdown();
	delete depthGenerator;
	depthGenerator = NULL;
}

