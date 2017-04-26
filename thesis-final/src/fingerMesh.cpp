//
//  fingerMesh.cpp
//  thesis-final
//
//  Created by wang yumeng on 4/25/17.
//
//

#include "fingerMesh.h"

FingerMesh::FingerMesh() {
    
}

void FingerMesh::setup() {
    image.load("test6.png");
    image.resize(200, 200);
    
    mesh.setMode(OF_PRIMITIVE_POINTS);
    //    mesh.setMode(OF_PRIMITIVE_LINES);
    
    mesh.enableColors();
    
    float intensityThreshold = 50.0;
    int w = image.getWidth();
    int h = image.getHeight();
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            ofColor c = image.getColor(x, y);
            float intensity = c.getLightness();
            if (intensity >= intensityThreshold) {
                float saturation = c.getSaturation();
                float z = ofMap(saturation, 0, 255, -300, 300);
                ofVec3f pos(x * 4, y * 4, z);
                mesh.addVertex(pos);
                mesh.addColor(c);
                
                offsets.push_back(ofVec3f(ofRandom(0, 100000), ofRandom(0, 100000), ofRandom(0, 100000)));
            }
        }
    }
    
    
    mesh.enableIndices();
    
    float connectionDistance = 20;
    int numVerts = mesh.getNumVertices();
    for (int a = 0; a < numVerts; a++) {
        ofVec3f verta = mesh.getVertex(a);
        for (int b = a + 1; b < numVerts; b++) {
            ofVec3f vertb = mesh.getVertex(b);
            float distance = verta.distance(vertb);
            if (distance <= connectionDistance) {
                mesh.addIndex(a);
                mesh.addIndex(b);
            }
            
        }
    }
    
    
    meshCentroid = mesh.getCentroid();
    for (int i = 0; i < numVerts; i++) {
        ofVec3f vert = mesh.getVertex(i);
        float distance = vert.distance(meshCentroid);
        float angle = atan2(vert.y-meshCentroid.y, vert.x - meshCentroid.x);
        distances.push_back(distance);
        angles.push_back(angle);
    }
    
    orbiting = false;
    shrinking = false;
    startOrbitTime = 0.0;
    meshCopy = mesh;
}

void FingerMesh::update() {
    int numVerts = mesh.getNumVertices();
    
    for (int i = 0; i < numVerts; i++) {
        ofVec3f vert = mesh.getVertex(i);
        
        float timeM = ofGetElapsedTimef();
        float timeScaleM = 1.0;
        float displacementScaleM = 0.75;
        ofVec3f timeOffsetsM = offsets[i];
        
        vert.x = 0.999 * vert.x + 0.001 * meshCentroid.x;
        vert.y = 0.999 * vert.y + 0.001 * meshCentroid.y;
        
        vert.x += (ofSignedNoise(timeM*timeScaleM+timeOffsetsM.x)) * displacementScaleM;
        vert.y += (ofSignedNoise(timeM*timeScaleM+timeOffsetsM.y)) * displacementScaleM;
        vert.z += (ofSignedNoise(timeM*timeScaleM+timeOffsetsM.z)) * displacementScaleM;
        
        mesh.setVertex(i, vert);
    }
    
}

void FingerMesh::draw() {
    ofBackground(0, 0, 0);
    
    easyCam.begin();
    ofPushMatrix();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    mesh.draw();
    ofPopMatrix();
    easyCam.end();

}