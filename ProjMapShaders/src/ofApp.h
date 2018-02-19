#pragma once

#include "ofMain.h"
#include "ofxQuadWarp.h"
//#include "ofxOMXPlayer.h"
#define nwarpers 10
#define nfbos 10



class ofApp : public ofBaseApp {
    
public:
		
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);


    ofxQuadWarp warper[nwarpers];
    
    ofImage img;
    ofFbo fbo[nfbos];

    ofShader shader;

    ofPoint points[10];
    //ofxOMXPlayer omxPlayer;
};
