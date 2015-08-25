// =============================================================================
//
// Copyright (c) 2010-2014 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"


void ofApp::setup()
{
    float a = 0.0;
    float b = 0.0;
    float epsilon = 0.5 * numeric_limits<float>::epsilon();
    
    bool areEqual = ofx::MathUtils::floatEquals(a, b);
    
    bool areEqualEpsilon = ofx::MathUtils::floatEquals(a, b, epsilon);
    
    ofLogNotice("testApp::setup") << a << "==" << b << "==" << (areEqual ? "true" : "false") ;
    ofLogNotice("testApp::setup") << a << "==" << b << "==" << (areEqualEpsilon ? "true" : "false") << " @ epsion = " << epsilon;
}


void ofApp::draw()
{
    ofBackgroundGradient(ofColor::gray, ofColor::black);
    ofDrawBitmapString("See the console.", 15,15);
}