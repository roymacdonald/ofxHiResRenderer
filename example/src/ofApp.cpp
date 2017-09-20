#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	int numPoints = 1000;
	
	for (int i = 0; i < numPoints; i++){
		points.push_back({ofRandom(-500, 500),ofRandom(-500, 500),ofRandom(-500, 500)});
		colors.push_back(ofColor(ofRandom(255),ofRandom(255),ofRandom(255)));
	}
	
	gui.setup();
	gui.add(scale.set("Scale", 1,1, 10));
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	if(ofGetKeyPressed(' ')){
		renderer.drawDebug(cam, ofGetCurrentViewport(), scale.get(), std::bind(&ofApp::drawScene, this), ofGetKeyPressed(OF_KEY_SHIFT));
	}else{
	float n = scale.get();
	cam.begin();//{0,0,floor(ofGetWidth()/n)*n,floor(ofGetHeight()/n)*n });
	drawScene();
	cam.end();
	}
	gui.draw();
}
//--------------------------------------------------------------
void ofApp::drawScene(){
	for (int i =0; i < points.size(); i++) {
		ofSetColor(colors[i]);
		ofDrawSphere(points[i], 10);
	}
	ofDrawGrid(100,10);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if(key == OF_KEY_RETURN){
		renderer.render(cam, ofGetCurrentViewport(), scale.get(), std::bind(&ofApp::drawScene, this), ofGetTimestampString()+".png");
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
	
}
