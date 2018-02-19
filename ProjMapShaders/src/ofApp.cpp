#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    // string videoPath = ofToDataPath("video/BigBuckBunny_320x180.mp4", true);
    img.load("quad_warp_kittens.png");
    // //Somewhat like ofFboSettings we may have a lot of options so this is the current model
    // ofxOMXPlayerSettings settings;
    // settings.videoPath = videoPath;
    // settings.useHDMIForAudio = true;    //default true
    // settings.enableTexture = true;      //default true
    // settings.enableLooping = true;      //default true
    // settings.enableAudio = true;        //default true, save resources by disabling
    // //settings.doFlipTexture = true;        //default false
    
    
    // //so either pass in the settings
    // omxPlayer.setup(settings);

    int x[nwarpers];
    int y[nwarpers];
    int w[nwarpers];
    int h[nwarpers];
        
    shader.load("LED_GLES1.vert", "LED_GLES1.frag", "");
    
    ofEnableAlphaBlending();

    for(int i=0; i<nwarpers; i++){
    int k = i * 10;
    x[i] = (ofGetWidth() - 320) * 0.5 + k;       // center on screen.
    y[i] = (ofGetHeight() - 180) * 0.5 + k;     // center on screen.
    w[i] = 320 + k;
    h[i] = 180 + k;
    fbo[i].allocate(w[i], h[i]);
    warper[i].setSourceRect(ofRectangle(0, 0, w[i], h[i]));              // this is the source rectangle which is the size of the image and located at ( 0, 0 )
    warper[i].setTopLeftCornerPosition(ofPoint(x[i], y[i]));             // this is position of the quad warp corners, centering the image on the screen.
    warper[i].setTopRightCornerPosition(ofPoint(x[i] + w[i], y[i]));        // this is position of the quad warp corners, centering the image on the screen.
    warper[i].setBottomLeftCornerPosition(ofPoint(x[i], y[i] + h[i]));      // this is position of the quad warp corners, centering the image on the screen.
    warper[i].setBottomRightCornerPosition(ofPoint(x[i] + w[i], y[i] + h[i])); // this is position of the quad warp corners, centering the image on the screen.
    warper[i].setup();
    warper[i].load(); // reload last saved changes.
    }
   

}

//--------------------------------------------------------------
void ofApp::update()
{
    if(ofGetFrameNum() % 5 != 0) {
        // only update every 5 frames.
        return;
    }
    //     fbos.begin();
    // ofClear(0, 0, 0, 0);
    //     shader.begin();
    //         shader.setUniform1f("time", ofGetElapsedTimef());
    //         shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    //         shader.setUniform2f("mouse", 0.0, 0.0);
    //         ofRect(0, 0, ofGetWidth(), ofGetHeight());
    //     shader.end();
    // fbos.end();
    
    // for(int i=0; i<10; i++) {
    //     // randomise points over the image area.
    //     points[i].x = ofRandom(img.getWidth());
    //     points[i].y = ofRandom(img.getHeight());
    // }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(255);
    
    //======================== draw image into fbo.
    for(int i=0; i<nfbos; i++){
    fbo[i].begin();
    ofClear(0, 0, 0, 0);
        shader.begin();
            shader.setUniform1f("time", ofGetElapsedTimef());
            shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
            shader.setUniform2f("mouse", 0.0, 0.0);
            ofRect(0, 0, ofGetWidth(), ofGetHeight());
        shader.end();
        // img.draw(0,0);
    fbo[i].end();
    }

    // fbo[0].begin();
    // ofClear(0, 0, 0, 0);
        // shader.begin();
        //     shader.setUniform1f("time", ofGetElapsedTimef());
        //     shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
        //     shader.setUniform2f("mouse", 0.0, 0.0);
        //     ofRect(0, 0, ofGetWidth(), ofGetHeight());
        // shader.end();
    // fbo[0].end();
    ofMatrix4x4 mat[nfbos];
    //======================== get our quad warp matrix.
    for(int j=0; j<nfbos; j++){
    mat[j] = warper[j].getMatrix();
    }

    
    //======================== use the matrix to transform our fbo.
    for(int j=0; j<nfbos; j++){
    
    ofPushMatrix();
    ofMultMatrix(mat[j]);
    fbo[j].draw(0, 0);
    ofPopMatrix();
    }
    
    
    //======================== use the matrix to transform points.

    // ofSetLineWidth(2);
    // ofSetColor(ofColor::cyan);
    
    // for(int i=0; i<9; i++) {
    //     int j = i + 1;
        
    //     ofVec3f p1 = mat.preMult(ofVec3f(points[i].x, points[i].y, 0));
    //     ofVec3f p2 = mat.preMult(ofVec3f(points[j].x, points[j].y, 0));
        
    //     ofDrawLine(p1.x, p1.y, p2.x, p2.y);
    // }
    
    //======================== draw quad warp ui.
    for(int i=0; i<nwarpers; i++){
    ofSetColor(ofColor::magenta);
    warper[i].drawQuadOutline();
    
    ofSetColor(ofColor::yellow);
    warper[i].drawCorners();
    
    ofSetColor(ofColor::magenta);
    warper[i].drawHighlightedCorner();
    
    ofSetColor(ofColor::red);
    warper[i].drawSelectedCorner();

    }
    
    //======================== info.
    
    // ofSetColor(ofColor::white);
    // ofDrawBitmapString("to warp the image, drag the corners of the image.", 20, 30);
    // ofDrawBitmapString("press 's' to toggle quad warp UI. this will also disable quad warp interaction.", 20, 50);
    // ofDrawBitmapString("press & hold 1, 2, 3, 4 to snap that point to the mouse", 20, 70);
    // ofDrawBitmapString("when a corner is selected (red), use keyboard arrow keys to nudge the corner position.", 20, 90);
}

void ofApp::exit() {
    for(int i=0; i<nwarpers; i++){
    warper[i].save();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

    if(key == 's' || key == 'S') {
        for(int i=0; i<nwarpers; i++){
        warper[i].toggleShow();
        }
    }
    
    if(key == 'l' || key == 'L') {
        for(int i=0; i<nwarpers; i++){
        warper[i].load();
        }

    }
    
    if(key == 'h' || key == 'H') {
        for(int i=0; i<nwarpers; i++){
        warper[i].save();
        }
    }

    if(key == 'j' || key == 'J') {
        shader.end();
        shader.load("LED_GLES.vert", "LED_GLES.frag", "");
        shader.begin();
    }
        if(key == 't' || key == 'T') {
        shader.end();
        shader.load("LED_GLES1.vert", "LED_GLES1.frag", "");
        shader.begin();
    }
            if(key == 'k' || key == 'K') {
        shader.end();
        shader.load("LED_GLES2.vert", "LED_GLES2.frag", "");
        shader.begin();
    }
}
