#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(800, 800);
    ofSetFrameRate(60);

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

//--------------------------------------------------------------
void ofApp::update(){
    //jitter
//    int numVerts = mesh.getNumVertices();
//    for (int i = 0; i < numVerts; i++) {
//        ofVec3f vert = mesh.getVertex(i);
//        
//        float time = ofGetElapsedTimef();
//        float timeScle = 5.0;
//        float displacementScale = 0.75;
//        ofVec3f timeOffSets = offsets[i];
//        
//        vert.x += (ofSignedNoise(time * timeScle * timeOffSets.x)) * displacementScale;
//        vert.y += (ofSignedNoise(time * timeScle * timeOffSets.y)) * displacementScale;
//        vert.z += (ofSignedNoise(time * timeScle * timeOffSets.z)) * displacementScale;
//        mesh.setVertex(i, vert);
//    }
    
    if (orbiting) {
        int numVerts = mesh.getNumVertices();
        for (int i = 0; i < numVerts; i++) {
            ofVec3f vert = mesh.getVertex(i);
            float distance = distances[i];
            float angle = angles[i];
            float elapsedTime = ofGetElapsedTimef() - startOrbitTime;
            
            float speed = ofMap(distance, 0, 200, 1, 0.25, true);
            float rotatedAngle = elapsedTime * speed + angle;
            
            vert.x = distance * cos(rotatedAngle) + meshCentroid.x;
            vert.y = distance * sin(rotatedAngle) + meshCentroid.y;
            
            mesh.setVertex(i, vert);
        }
    }
    
    if (shrinking) {
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
    
    if (mouseDisplacement) {
        ofVec3f mouse(mouseX, ofGetHeight()-mouseY, 0);
        int numVerts = mesh.getNumVertices();
        for (int i = 0; i < numVerts; i++) {
            ofVec3f vertex = meshCopy.getVertex(i);
            float distanceToMouse = mouse.distance(vertex);
            
            float displacement = ofMap(distanceToMouse, 0, 300, 300.0, 0, true);
            
            ofVec3f direction = vertex - mouse;
            direction.normalize();
            
            ofVec3f displacedVertex = vertex + displacement * direction;
            mesh.setVertex(i, displacedVertex);
        }
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    
    easyCam.begin();
        ofPushMatrix();
            ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
            mesh.draw();
        ofPopMatrix();
    easyCam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'o') {
        orbiting = !orbiting;
        startOrbitTime = ofGetElapsedTimef();
        mesh = meshCopy;
    }
    if (key == 'm') {
        mouseDisplacement = !mouseDisplacement;
        mesh = meshCopy;
    }
    if (key == 's') {
        shrinking = !shrinking;
        mesh = meshCopy;
    }
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
