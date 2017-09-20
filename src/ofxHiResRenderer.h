#pragma once
#include "ofMain.h"

class ofxHiResRenderer{
public:
	void render(const ofCamera& cam, const ofRectangle& viewport, float scale, std::function<void()> drawScene, std::string path = "", bool bDrawToScreen = false);

	void drawDebug(const ofCamera& cam, const ofRectangle& viewport, float scale, std::function<void()> drawScene, bool bDrawViewport);
protected:

//--------------------------------------------------------------
	float getFovForViewport(const ofRectangle &viewport, const ofCamera& camera);
	glm::vec2 getOffsetForViewport(const ofRectangle &viewport);
	
	void copyPixels(ofPixels& target, ofPixels& original, int posX, int posY) const;
	ofCamera getCamForViewport(const ofCamera& cam, const ofRectangle& viewport);
private:

	ofRectangle originalViewport, renderTotalRect;
	float scale = 0;
	
	bool bRendering = false;
};