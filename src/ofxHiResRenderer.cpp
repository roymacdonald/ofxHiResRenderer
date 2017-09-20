#include "ofxHiResRenderer.h"

//--------------------------------------------------------------
void ofxHiResRenderer::render(const ofCamera& cam, int numSections, std::function<void()> drawScene,  std::string path){
	this->numSections = numSections;
	ofFbo fbo;
	ofPixels renderPixels;
	auto s = getIntSize();
	fbo.allocate(s.x, s.y,GL_RGBA32F_ARB, 4);
	renderPixels.allocate(s.x * numSections , s.y * numSections, OF_IMAGE_COLOR_ALPHA);
	bRendering = true;
//	auto ts = ofGetTimestampString();
	for(int y = 0; y < numSections; y++){
		for(int x = 0; x < numSections; x++){
			fbo.begin();
			ofClear(0, 0);
			ofCamera c = cam;
			c.setFov(getAngle(1.0/numSections, cam.getFov()));
			c.setLensOffset(getOffsetForSection(x,y));
			auto s = getIntSize();
			c.begin({0, 0, s.x, s.y});
			drawScene();
			c.end();
			fbo.end();
			ofPixels tempPix;
			fbo.readToPixels(tempPix);
			copyPixels(renderPixels, tempPix, s.x * x, s.y * y);
		}
	}
	ofSaveImage(renderPixels,  path);
	bRendering = false;
}
//--------------------------------------------------------------
glm::vec2 ofxHiResRenderer::getIntSize(){
	if(numSections > 0){
		float n = numSections;
		return { floor(ofGetWidth()/n) * n, floor(ofGetHeight()/n) * n};
	}
	return {0, 0};
}
//--------------------------------------------------------------
float ofxHiResRenderer::getAngle(float pct, float fov){
	return 2*atan( pct*tan(fov*DEG_TO_RAD /2))*RAD_TO_DEG;
}
//--------------------------------------------------------------
glm::vec2 ofxHiResRenderer::getOffsetForSection(int x, int y){
	if(numSections > 0){
		int n = numSections-1;
		return {ofMap(x, 0, n, -n,  n), ofMap(y, 0, n,  n, -n)};
	}
	return {0,0};
}
//--------------------------------------------------------------
void ofxHiResRenderer::copyPixels(ofPixels& target, ofPixels& original, int posX, int posY){
	auto s = getIntSize();
	for(int y = 0; y < s.y; y++){
		for(int x = 0; x < s.x; x++){
			target.setColor(posX  + x, posY + y, original.getColor(x, y));
		}
	}
}
