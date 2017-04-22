#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // enable depth
    kinect.setRegistration(true);
    
    kinect.init();
    kinect.open(0);
    
    if(kinect.isConnected()){
        ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
        ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
        ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
        ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
    }
    
    colorImg.allocate(kinect.width, kinect.height);
    filtered.allocate(kinect.width, kinect.height);
    red.allocate(kinect.width, kinect.height);
    green.allocate(kinect.width, kinect.height);
    blue.allocate(kinect.width, kinect.height);
    
    
    ofSetFrameRate(60);
    
    kinectAngle = 20;
    kinect.setCameraTiltAngle(kinectAngle);
    
    threshold = 100;
    
    // drawing point cloud from the front
//    bDrawPointCloud = false;

}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofBackground(0);
    
    kinect.update();
    
    if(kinect.isFrameNew()) {
        colorImg.setFromPixels(kinect.getPixels(), kinect.width, kinect.height);
        colorImg.mirror(false, true);
        
        colorImg.convertToGrayscalePlanarImages(red, green, blue);
        
        // to filter out only blue
        red += green;
        blue -= red;
        
//        blue.threshold(threshold);
        
        // filter image based on the color value
        for (int i = 0; i < kinect.width * kinect.height; i++) {
            filtered.getPixels()[i] = ofInRange(blue.getPixels()[i], 0, 40) ? 0 : 255;
        }
        
        filtered.flagImageChanged();
        contours.findContours(filtered, 50, kinect.width * kinect.height, 1, false);
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);

    blue.draw(0, 0);

    for (int i = 0; i < contours.nBlobs; i++) {
        ofCircle(contours.blobs[i].centroid.x, contours.blobs[i].centroid.y, 5);
        
        
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
