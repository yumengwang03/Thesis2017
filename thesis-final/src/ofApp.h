#pragma once

#include "ofMain.h"
#include "videoPlayer.h"
#include "bigPixels.h"
#include "fingerMesh.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void timerAll(int index, int duration);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    int currentVideo;
    ofSoundPlayer storyPlayer1;
    ofSoundPlayer storyPlayer2;
    ofSoundPlayer storyPlayer3;
    
    int startTimeAll;
    
    int clipNum;
    
    struct clip {
        string title;
        bool isPlaying;
        int duration;
    };
    
    vector<clip> playOrder;
    
    clip playClip;

    
    BigPixels bigPixels;
    FingerMesh fingerMesh;
    
		
};
