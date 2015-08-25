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


#include "ofx/RunningRegression.h"


namespace ofx {


RunningRegression::RunningRegression()
{
	reset();
}


RunningRegression::~RunningRegression()
{
}


void RunningRegression::reset()
{
	_xStats.reset();
	_yStats.reset();
	_sxy = 0.0;
	_n = 0;
}


void RunningRegression::update(double x, double y)
{
	_sxy += (_xStats.mean() - x) * (_yStats.mean() - y) * static_cast<double>(_n) / static_cast<double>(_n + 1);

	_xStats.update(x);
	_yStats.update(y);
	
	_n++;
}


uint64_t RunningRegression::samples() const
{
	return _n;
}


double RunningRegression::slope() const
{
	double _sxx = _xStats.variance() * (_n - 1.0);

	return _sxy / _sxx;
}


double RunningRegression::intercept() const
{
	return _yStats.mean() - slope() * _xStats.mean();
}


double RunningRegression::correlation() const
{
	double t = _xStats.standardDeviation() * _yStats.standardDeviation();

	return _sxy / ((_n - 1) * t);
}


} // namespace ofx
