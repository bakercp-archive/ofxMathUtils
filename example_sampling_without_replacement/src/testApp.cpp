#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    vector<int> myInts;
    
    for(int i = 0; i < 10; i++) {
        myInts.push_back(i);
    }
    
    ofxRandomSampler sampler;

    for (int i = 0; i < 100; i++)
    {
        cout << sampler.next() << endl;
    }

    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    ofDrawBitmapString("See the console.", 15,15);
}