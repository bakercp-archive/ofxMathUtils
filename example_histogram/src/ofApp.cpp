// =============================================================================
//
// Copyright (c) 2010-2015 Christopher Baker <http://christopherbaker.net>
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
	gen.seed(rd());

	histogram.setNumBins(250);
	histogram.setRangeMinimum(-2.5);
	histogram.setRangeMaximum(2.5);

//	for (std::size_t i = 0; i < 10000000; ++i)
//	{
//		histogram.update(normal(gen));
//	}

}


void ofApp::update()
{
	histogram.update(normal(gen));
}


void ofApp::draw()
{
    ofBackgroundGradient(ofColor::gray, ofColor::black);
    ofDrawBitmapString("See the console.", 15,15);

	std::size_t numBins = histogram.getNumBins();

	float binWidth = ofGetWidth() * 0.75 / numBins;

	float totalWidth = (numBins * binWidth);

	float totalHeight = ofGetHeight() * 0.75;

	auto minMax = std::minmax_element(histogram.begin(), histogram.end());

	std::size_t minCount = *minMax.first;
	std::size_t maxCount = *minMax.second;

	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofTranslate(-totalWidth / 2, totalHeight / 2);

	for (std::size_t i = 0; i < histogram.getNumBins(); ++i)
	{
		float height = ofMap(histogram.counts()[i], 0, maxCount, 0, totalHeight);

		if (i % 2)
		{
			ofSetColor(255);
		}
		else
		{
			ofSetColor(127);
		}

		ofDrawRectangle(0, 0, binWidth, -height);

		ofTranslate(binWidth, 0);
	}

	ofPopMatrix();

}
