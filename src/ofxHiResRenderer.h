#pragma once
#include "ofMain.h"

class ofxHiResRenderer{//:	private ofCamera{
public:
	void render(const ofCamera& cam, int numSections, std::function<void()> drawScene, std::string path = "");

protected:
	float getAngle(float pct, float fov);
	
	glm::vec2 getOffsetForSection(int x, int y);
	
	glm::vec2 getIntSize();

	void copyPixels(ofPixels& target, ofPixels& original, int posX, int posY);
private:

	size_t numSections = 0;
	bool bRendering = false;
};