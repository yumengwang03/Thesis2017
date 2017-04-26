//
//  fingerMesh.h
//  thesis-final
//
//  Created by wang yumeng on 4/25/17.
//
//

#ifndef fingerMesh_h
#define fingerMesh_h

#include "ofMain.h"

class FingerMesh {
    
public:
    void setup();
    void update();
    void draw();
    
    ofMesh mesh;
    ofMesh meshCopy;
    ofImage image;
    ofEasyCam easyCam;
    vector<ofVec3f> offsets;
    
    bool orbiting;
    float startOrbitTime;
    
    vector<float> distances;
    vector<float> angles;
    ofVec3f meshCentroid;
    
    bool shrinking;
    
    FingerMesh();
};

#endif
