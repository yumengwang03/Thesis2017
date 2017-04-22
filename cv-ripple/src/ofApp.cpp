#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    
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
    
    kinectAngle = 0;
    kinect.setCameraTiltAngle(kinectAngle);
    
    // ripple setup
    ripples.allocate(kinect.width, kinect.height);
    bounce.allocate(kinect.width, kinect.height);
    
    ofImage background;
//    background.loadImage("/Users/wangyumeng/Desktop/Miscellaneous/test.png");
//    background.resize(kinect.width, kinect.height);
//    bounce.setTexture(background.getTexture(), 1);
    
    lastTime = 0;
    readPos = false;

}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofBackground(255);
    
    kinect.update();
    
    if(kinect.isFrameNew()) {
        colorImg.setFromPixels(kinect.getPixels(), kinect.width, kinect.height);
        colorImg.mirror(false, true);
        
        colorImg.convertToGrayscalePlanarImages(red, green, blue);
        
        // to filter out only blue
        red += green;
        blue -= red;
        
        // filter image based on the color value
        for (int i = 0; i < kinect.width * kinect.height; i++) {
            filtered.getPixels()[i] = ofInRange(blue.getPixels()[i], 0, 40) ? 0 : 255;
        }
        
        filtered.flagImageChanged();
        contours.findContours(filtered, 50, kinect.width * kinect.height, 3, false);
    }
    
    smoothTimer();
    
    ripples.begin();
//    ripples.damping = 0.998;
    ripples.damping = ofMap(kinect.height, 0, ofGetHeight(), 0.98, 1.0, true);
    ofFill();
    ofSetColor(20, 70, ofNoise(ofGetFrameNum()) * 255 * 5, 255);
    
    
    for (int i = 0; i < contours.nBlobs; i++) {
//      ofCircle(contours.blobs[i].centroid.x, contours.blobs[i].centroid.y, 5);
        
        if (readPos) {
            rippleX = contours.blobs[i].centroid.x;
            rippleY = contours.blobs[i].centroid.y;
        }
        
        ofEllipse(rippleX, rippleY, 6, 6);
        
    }

    
    ripples.end();
    ripples.update();
    
//    bounce << ripples;

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    
    //blue.draw(0, 0);
    ripples.draw(0, 0);
    
//    bounce.draw(kinect.width, 0);

}

void ofApp::smoothTimer() {
    int currentTime = ofGetElapsedTimeMillis();
    
    if (currentTime - lastTime >= 500) {
        readPos = true;
//        cout<<"read"<<endl;
        lastTime = currentTime;
    } else {
        readPos = false;
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
