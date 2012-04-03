#include "PlaybackApp.h"


//--------------------------------------------------------------
void PlaybackApp::setup()
{
	doInit = false;
	isPlayerReady = false;
	ofDirectory directory(ofToDataPath("", true));
	directory.listDir();
	vector<ofFile> files = directory.getFiles();
	for (int i =0; i<files.size(); i++)
	{
		
		
		if (files[i].getExtension() == "oni") 
		{
			cout << "HIT: " << files[i].getFileName() << endl;
			oniFilePaths.push_back(files[i].getFileName());
		}
	}
	if (oniFilePaths.size() > 0) 
	{
		info = "";
	}else {
		info = "NO FILES AVAILABLE";
	}

	for (int i =0; i<oniFilePaths.size(); i++)
	{
		
		info += ofToString(i) + " : " + oniFilePaths[i] + "\n";
		//cout << "HIT: " << files[i].getFileName() << endl;

	}
						 
}

//--------------------------------------------------------------
void PlaybackApp::update(){
	if (doInit ) 
	{
		doInit = false;
		
		player.setupWithFile(selectedFileName);
		isPlayerReady = true;
	}
	if (isPlayerReady) {
		player.update();
	}
}

//--------------------------------------------------------------
void PlaybackApp::draw(){
	if (isPlayerReady)
	{
		player.drawAllScreens();
	}
	ofDrawBitmapString(info, 20, 20);
}

//--------------------------------------------------------------
void PlaybackApp::keyPressed(int key){
	

	int keyOffset = key-48;
	cout << "keyPressed: " << key << "keyOffset: " << keyOffset << " oniFilePaths.size(): " << oniFilePaths.size() << endl;
	
	if (keyOffset <= oniFilePaths.size()-1) 
	{
		cout << "SELECTING: " << oniFilePaths.at(keyOffset) << endl;
		selectedFileName = oniFilePaths.at(keyOffset);
		doInit = true;
	}
	
}

//--------------------------------------------------------------
void PlaybackApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void PlaybackApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void PlaybackApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void PlaybackApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void PlaybackApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void PlaybackApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void PlaybackApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void PlaybackApp::dragEvent(ofDragInfo dragInfo){ 
	
}