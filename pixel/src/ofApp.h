#pragma once

#include "ofMain.h"
#include "ofxPostGlitch.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

    void timer();
    
    ofVideoGrabber videoGrabber;
    ofVideoPlayer pixelMovie;
    int cameraW, cameraH;
    int pixelThreshold, pixelGap, pixelPos;
    
    int startTime;
    bool addPixels;
    
    // glitch instance
    ofFbo myFbo;
    ofxPostGlitch shakerGlitch;
    
    
		
};
