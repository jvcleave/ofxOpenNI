#include "RecordingApp.h"

//--------------------------------------------------------------
void RecordingApp::setup(){
	grabber.setup();
	recorder.setup(&grabber.context);
	isRecording = false;
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
	
	ofPushStyle();
	if (isRecording) {
		ofSetColor(ofColor::red);
	}else {
		ofSetColor(ofColor::green);
	}
	ofCircle(20, 20, 20);
	ofPopStyle();

}

//--------------------------------------------------------------
void RecordingApp::keyPressed(int key){
	if (key ==  ' ') {
		
		//isRecording = !isRecording;
		if (isRecording) {
			recorder.stopRecording();
			isRecording = false;
		}else {
			recorder.startRecording();
			isRecording = true;
		}

		
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