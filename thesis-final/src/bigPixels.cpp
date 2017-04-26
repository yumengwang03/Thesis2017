//
//  bigPixels.cpp
//  thesis-final
//
//  Created by wang yumeng on 4/21/17.
//
//

#include "bigPixels.h"

BigPixels::BigPixels() {
    
}

void BigPixels::setup() {
//    ofBackground(0);
    
    border = 40;
    cameraW = 720 + border;
    cameraH = 720 + border;

    
    pixelMovie.loadMovie("test.MOV");
    pixelMovie.play();
    pixelMovie.setVolume(0);
    
    pixelThreshold = 1;
    
    startTime = 0;
    addPixels = false;
}

void BigPixels::update() {
    pixelMovie.update();
    
    
    timer();
    
    pixelGap = cameraW/pixelThreshold;
    if (pixelGap >= 2 && addPixels) {
        pixelThreshold ++;
    }
}

void BigPixels::draw() {
    unsigned char * pixels = pixelMovie.getPixels();
    int nChannels = pixelMovie.getPixelsRef().getNumChannels();
    
    int movieWidth = pixelMovie.getWidth();
    int movieHeight = pixelMovie.getHeight();
    
    for (int i = 0; i < cameraW/pixelGap; i++) {
        for (int j = 0; j < cameraH/pixelGap; j++) {
            int redPixels = pixels[(j * pixelGap * movieWidth + i * pixelGap) * nChannels];
            int greenPixels = pixels[(j * pixelGap * movieWidth + i * pixelGap) * nChannels + 1];
            int bluePixels = pixels[(j * pixelGap * movieWidth + i * pixelGap) * nChannels + 2];

            ofSetColor(redPixels, greenPixels, bluePixels);
            ofRect(pixelGap * i + 280, pixelGap * j, pixelGap, pixelGap);
        }
    }
    
    ofSetColor(0);
    ofRect(280, cameraH - border, cameraW, border);
    ofRect(cameraW - border +280, 0, border, cameraH);
}

void BigPixels::timer() {
    int currentTime = ofGetElapsedTimeMillis();
    
    if (currentTime - startTime >= 600) {
        addPixels = true;
        //        cout<<"add pixels now"<<endl;
        startTime = currentTime;
    } else {
        addPixels = false;
    }
}

void BigPixels::clear() {
    
}

