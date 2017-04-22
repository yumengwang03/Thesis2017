

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    cameraW = 600;
    cameraH = 600;
//    videoGrabber.setVerbose(true);
//    videoGrabber.setup(cameraW, cameraH);
    
    pixelMovie.loadMovie("/Users/wangyumeng/Pictures/videos/test.MOV");
    pixelMovie.play();
    pixelMovie.setVolume(0);
    
    pixelThreshold = 1;
    
//    pixelPos = pixelGap;
    
    startTime = 0;
    addPixels = false;
    
    shakerGlitch.setup(&myFbo);

}

//--------------------------------------------------------------
void ofApp::update(){
//    videoGrabber.update();
    pixelMovie.update();
    
    
    timer();
    
    pixelGap = cameraW/pixelThreshold;
    if (pixelGap >= 2 && addPixels) {
        pixelThreshold ++;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
//    videoGrabber.draw(0,0);
//    pixelMovie.draw(0, 0, cameraW, cameraH);
    
    //myFbo.begin();
    
    unsigned char * pixels = pixelMovie.getPixels();
    int nChannels = pixelMovie.getPixelsRef().getNumChannels();
    
    //int red = pixels[(20 * cameraW + 100) * nChannels];
    //cout<<red<<endl;
    
    int movieWidth = pixelMovie.getWidth();
    int movieHeight = pixelMovie.getHeight();
    
    for (int i = 0; i < cameraW/pixelGap; i++) {
        for (int j = 0; j < cameraH/pixelGap; j++) {
            int redPixels = pixels[(j * pixelGap * movieWidth + i * pixelGap) * nChannels];
            int greenPixels = pixels[(j * pixelGap * movieWidth + i * pixelGap) * nChannels + 1];
            int bluePixels = pixels[(j * pixelGap * movieWidth + i * pixelGap) * nChannels + 2];
            
            ofSetColor(redPixels, greenPixels, bluePixels);
            ofRect(pixelGap * i, pixelGap * j, pixelGap, pixelGap);
        }
    }
    
    ofSetColor(0);
    int border = 40;
    ofRect(0, cameraH - border, cameraW, border);
    ofRect(cameraW - border, 0, border, cameraH);
    
    //myFbo.end();
    
    
//    shakerGlitch.generateFx();
//    shakerGlitch.setFx(OFXPOSTGLITCH_SHAKER, true);
//    ofSetColor(255);
//    myFbo.draw(0, 0);

}

//--------------------------------------------------------------
void ofApp::timer(){
    int currentTime = ofGetElapsedTimeMillis();
    
    if (currentTime - startTime >= 600) {
        addPixels = true;
//        cout<<"add pixels now"<<endl;
        startTime = currentTime;
    } else {
        addPixels = false;
    }
    cout<<addPixels<<endl;
}
