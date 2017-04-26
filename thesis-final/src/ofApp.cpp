#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    currentVideo = 1;
    
    storyPlayer1.load("definition.wav");
    storyPlayer2.load("definition.wav");
    storyPlayer3.load("definition.wav");
    storyPlayer1.setVolume(1.0f);
    storyPlayer2.setVolume(1.0f);
    storyPlayer3.setVolume(1.0f);
    
    startTimeAll = 0;
    
    clipNum = 3;
    
    for (int i = 0; i < clipNum; i++) {
        playOrder.push_back(playClip);
        if (i == 0) {
            playOrder[i].isPlaying = true;
        } else {
            playOrder[i].isPlaying = false;
        }
    }
    
    
    playOrder[0].title = "fingermesh_clip";
    playOrder[0].duration = 5 * 1000;
    
    playOrder[1].title = "bigPixels_clip";
    playOrder[1].duration = 7 * 1000;
    
    playOrder[2].title = "bigPixels_clip3";
    playOrder[2].duration = 4 * 1000;
    
    
    bigPixels.setup();
    fingerMesh.setup();
    

}

//--------------------------------------------------------------
void ofApp::update(){
    ofSoundUpdate();
    
    if (playOrder[0].isPlaying) {
        fingerMesh.update();
        timerAll(0, playOrder[0].duration);
        cout<<"clip 0"<<endl;
    } else if(playOrder[1].isPlaying) {
        bigPixels.update();
        timerAll(1, playOrder[1].duration);
        cout<<"clip 1"<<endl;
    } else if(playOrder[2].isPlaying) {
//        bigPixels2.update();
        timerAll(2, playOrder[2].duration);
        cout<<"clip 2"<<endl;
    }

}


//--------------------------------------------------------------
void ofApp::draw(){
    switch (currentVideo) {
        case 1:
            if (!storyPlayer1.isPlaying()) {
                storyPlayer1.play();
            }
            break;
        case 2:
            if (!storyPlayer2.isPlaying()) {
                storyPlayer2.play();
            }
            break;
        case 3:
            if (!storyPlayer3.isPlaying()) {
                storyPlayer3.play();
            }
            break;
        default:
            break;
    }
    
    
    
    if (playOrder[0].isPlaying) {
        fingerMesh.draw();
    } else if(playOrder[1].isPlaying) {
        bigPixels.draw();
    } else if(playOrder[2].isPlaying) {
//        bigPixels2.draw();
    }
}

//--------------------------------------------------------------
void ofApp::timerAll(int index, int duration){
    int currentTimeAll = ofGetElapsedTimeMillis();
    
    if (currentTimeAll - startTimeAll >= duration) {
        playOrder[index].isPlaying = false;
        playOrder[index + 1].isPlaying = true;
        startTimeAll = currentTimeAll;
        
        if(index == clipNum - 1) {
            playOrder[0].isPlaying = true;
        }
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
//    storyPlayer1.play();
    
    if (currentVideo > 0 && currentVideo <= 3) {
        currentVideo ++;
    }

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
