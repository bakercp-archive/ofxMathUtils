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


#include "ofx/RunningStatistics.h"
#include <cmath>
#include <limits>
#include <algorithm>


namespace ofx {


RunningStatistics::RunningStatistics()
{
	reset();
}


RunningStatistics::~RunningStatistics()
{
}


void RunningStatistics::reset()
{
	_n = 0;
	_M1 = 0.0;
	_M2 = 0.0;
	_M3 = 0.0;
	_M4 = 0.0;
	_maximum = std::numeric_limits<double>::lowest();
	_minimum = std::numeric_limits<double>::max();
}


void RunningStatistics::update(double value)
{
	uint64_t n1 = _n;

	_n++;

	double delta = value - _M1;
	double delta_n = delta / _n;
	double delta_n2 = delta_n * delta_n;
	double term1 = delta * delta_n * n1;

	_M1 += delta_n;
	_M4 += term1 * delta_n2 * (_n * _n - 3 * _n + 3) + 6 * delta_n2 * _M2 - 4 * delta_n * _M3;
	_M3 += term1 * delta_n * (_n - 2) - 3 * delta_n * _M2;
	_M2 += term1;

	_minimum = std::min(_minimum, value);
	_maximum = std::max(_maximum, value);
}


uint64_t RunningStatistics::samples() const
{
	return _n;
}


double RunningStatistics::mean() const
{
	return _M1;
}


double RunningStatistics::variance() const
{
	return _M2 / (_n - 1.0);
}


double RunningStatistics::standardDeviation() const
{
	return std::sqrt(variance());
}


double RunningStatistics::skewness() const
{
	return std::sqrt(double(_n)) * _M3/ pow(_M2, 1.5);
}


double RunningStatistics::kurtosis() const
{
	return static_cast<double>(_n) * _M4 / (_M2 * _M2) - 3.0;
}


double RunningStatistics::maximum() const
{
	return _maximum;
}


double RunningStatistics::minimum() const
{
	return _minimum;
}


} // namespace ofx
