#include "RecordingApp.h"

//--------------------------------------------------------------
void RecordingApp::setup(){
	grabber.setup();
	recorder.setup(&grabber.context);
	recorder.startRecording();
}

//--------------------------------------------------------------
void RecordingApp::update(){
	grabber.update();
	recorder.update();
	
}

//--------------------------------------------------------------
void RecordingApp::draw(){
	grabber.drawAllScreens();
}

//--------------------------------------------------------------
void RecordingApp::keyPressed(int key){
	if (key ==  ' ') {
		recorder.stopRecording();
	}
}

//--------------------------------------------------------------
void RecordingApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void RecordingApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void RecordingApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void RecordingApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void RecordingApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void RecordingApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void RecordingApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void RecordingApp::dragEvent(ofDragInfo dragInfo){ 
	
}