#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
 
    float a = 0.0;
    float b = 0.0;
    float epsilon = 2*numeric_limits<float>::epsilon();
    
    bool areEqual = ofxFloatEquals(a,b);
    
    bool areEqualEpsilon = ofxFloatEquals(a,b,epsilon);
    
    ofLogNotice("testApp::setup") << a << "==" << b << "==" << (areEqual ? "true" : "false") ;
    ofLogNotice("testApp::setup") << a << "==" << b << "==" << (areEqualEpsilon ? "true" : "false") << " @ epsion = " << epsilon;
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    ofDrawBitmapString("See the console.", 15,15);
}