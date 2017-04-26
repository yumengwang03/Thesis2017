//
//  bigPixels.h
//  thesis-final
//
//  Created by wang yumeng on 4/21/17.
//
//

#ifndef bigPixels_h
#define bigPixels_h

#include "ofMain.h"

class BigPixels {
    
public:
    void setup();
    void update();
    void draw();
    void timer();
    void clear();
    
    ofVideoGrabber videoGrabber;
    ofVideoPlayer pixelMovie;
    int cameraW, cameraH;
    int pixelThreshold, pixelGap, pixelPos;
    
    int startTime;
    bool addPixels;
    
    int border;
    
    BigPixels();
};

#endif
