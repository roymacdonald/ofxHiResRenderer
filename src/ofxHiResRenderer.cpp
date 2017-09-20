#include "ofxHiResRenderer.h"
//--------------------------------------------------------------
ofRectangle& floorRect(ofRectangle& rect){
	rect.x = floor(rect.x);
	rect.y = floor(rect.y);
	rect.width = floor(rect.width);
	rect.height = floor(rect.height);
	return rect;
}
//--------------------------------------------------------------
ofRectangle floorRect(const ofRectangle& rect){
	ofRectangle r;
	r.x = floor(rect.x);
	r.y = floor(rect.y);
	r.width = floor(rect.width);
	r.height = floor(rect.height);
	return r;
}
//--------------------------------------------------------------
void ofxHiResRenderer::render(const ofCamera& cam, const ofRectangle& viewport, float scale, std::function<void()> drawScene,  std::string path, bool bDrawToScreen){
	this->scale = scale;
	if(scale <= 1){
		ofLogError("ofxHiResRenderer::render", "render failed. Scale needs to be more than 1");
		return;
	}
	if(path.empty() && !bDrawToScreen){
		ofLogError("ofxHiResRenderer::render", "render failed. Empty path to save file.");
	}
	originalViewport = floorRect(viewport);
	originalViewport.x = 0;
	originalViewport.y = 0;
	ofFbo fbo;
	ofPixels renderPixels;
	if(bDrawToScreen){
		originalViewport.width /= scale;
		originalViewport.height /= scale;
		originalViewport = floorRect(originalViewport);
		renderTotalRect = floorRect(viewport);
	}else{
		renderTotalRect = ofRectangle(0,0,round(viewport.width* scale),round(viewport.height* scale));
	}
	fbo.allocate(originalViewport.width, originalViewport.height,GL_RGBA32F_ARB, 4);
	renderPixels.allocate(renderTotalRect.width , renderTotalRect.height, OF_IMAGE_COLOR_ALPHA);
	
	bRendering = true;
	int n = ceil(scale);
	for(int y = 0; y < n; y++){
		for(int x = 0; x < n; x++){
			auto vp =  originalViewport;
			vp.x = vp.width * x;
			vp.y = vp.height * y;
			vp = vp.getIntersection(renderTotalRect);
			auto camVp = vp;
			if(!bDrawToScreen){
				if(vp.width != fbo.getWidth()||vp.height != fbo.getHeight()){
					fbo.allocate(vp.width, vp.height,GL_RGBA32F_ARB, 4);
				}
				fbo.begin();
				ofClear(0, 0);
				camVp.x = 0;
				camVp.y = 0;
			}
			ofCamera rectCam = getCamForViewport(cam, vp);
			rectCam.begin(camVp);
			drawScene();
			rectCam.end();
			
			if(!bDrawToScreen){
				fbo.end();
				ofPixels tempPix;
				fbo.readToPixels(tempPix);
				copyPixels(renderPixels, tempPix, vp.x, vp.y);
			}
		}
	}
	if(!bDrawToScreen){
		ofSaveImage(renderPixels,  path);
	}
	bRendering = false;
	
}

//--------------------------------------------------------------
void ofxHiResRenderer::drawDebug(const ofCamera& cam, const ofRectangle& viewport, float scale, std::function<void()> drawScene, bool bDrawViewport){
	render(cam, viewport, scale, drawScene, "", true);
}
//--------------------------------------------------------------
ofCamera ofxHiResRenderer::getCamForViewport(const ofCamera& cam, const ofRectangle& viewport){
	ofCamera rectCam = cam;
	rectCam.setFov(getFovForViewport(viewport, cam));
	rectCam.setLensOffset(getOffsetForViewport(viewport));
	rectCam.setAspectRatio(viewport.width/viewport.height);
	return rectCam;
}
//--------------------------------------------------------------
void ofxHiResRenderer::copyPixels(ofPixels& target, ofPixels& original, int posX, int posY) const {
	for(int y = 0; y < original.getHeight(); y++){
		for(int x = 0; x < original.getWidth(); x++){
			target.setColor(posX  + x, posY + y, original.getColor(x, y));
		}
	}
}
//--------------------------------------------------------------
float ofxHiResRenderer::getFovForViewport(const ofRectangle &viewport, const ofCamera& camera){
	return 2* ofRadToDeg(atan( (viewport.height/ renderTotalRect.height)*tan(ofDegToRad(camera.getFov()) /2)));
}
//--------------------------------------------------------------
glm::vec2 ofxHiResRenderer::getOffsetForViewport(const ofRectangle &viewport){
	float n = renderTotalRect.width/viewport.width;
	float m = renderTotalRect.height/viewport.height;
	return {ofMap(viewport.getCenter().x, 0, renderTotalRect.width, -n,  n), ofMap(viewport.getCenter().y, 0,renderTotalRect.height,  m, -m)};
}

