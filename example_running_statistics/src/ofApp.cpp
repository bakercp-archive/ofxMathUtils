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
#include <random>


void ofApp::setup()
{
	RunningStatistics rs;

	std::random_device rd;
	std::mt19937 gen(rd());

	std::normal_distribution<> nd;

	for (std::size_t i = 0; i < 1000000; ++i)
	{
		rs.update(nd(gen));
	}

	std::cout << "nd(0, 1)" << std::endl;
	std::cout << "Samples: " << rs.samples() << std::endl;
	std::cout << "mean(): " << rs.mean() << std::endl;
	std::cout << "variance(): " << rs.variance() << std::endl;
	std::cout << "standardDeviation(): " << rs.standardDeviation() << std::endl;
	std::cout << "kurtosis(): " << rs.kurtosis() << std::endl;
	std::cout << "skewness(): " << rs.skewness() << std::endl;
	std::cout << "minimum(): " << rs.minimum() << std::endl;
	std::cout << "maximum(): " << rs.maximum() << std::endl;

	rs.reset();

	std::normal_distribution<> nd2(5, 5);

	for (std::size_t i = 0; i < 1000000; ++i)
	{
		rs.update(nd2(gen));
	}

	std::cout << "nd(5, 5)" << std::endl;
	std::cout << "Samples: " << rs.samples() << std::endl;
	std::cout << "mean(): " << rs.mean() << std::endl;
	std::cout << "variance(): " << rs.variance() << std::endl;
	std::cout << "standardDeviation(): " << rs.standardDeviation() << std::endl;
	std::cout << "kurtosis(): " << rs.kurtosis() << std::endl;
	std::cout << "skewness(): " << rs.skewness() << std::endl;
	std::cout << "minimum(): " << rs.minimum() << std::endl;
	std::cout << "maximum(): " << rs.maximum() << std::endl;

	RunningRegression rr;
}


void ofApp::draw()
{
//	tupleParameter = { 12 }; //std::make_pair<uint64_t, float>(ofGetElapsedTimeMicros(), ofRandom(-0.01, 0.01));


    ofBackgroundGradient(ofColor::gray, ofColor::black);
    ofDrawBitmapString("See the console.", 15,15);

//	cout << accumulator.size() << "/" << accumulator.getCapacity() << endl;
//	cout << runningStats.mean() << "/" << runningStats.standardDeviation() << endl;
}