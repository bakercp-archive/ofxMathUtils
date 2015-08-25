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


#include "ofx/RunningHistogram.h"
#include <cmath>


namespace ofx {


RunningHistogram::RunningHistogram(std::size_t numBins,
								   double rangeMinimum,
								   double rangeMaximum):
	_numBins(numBins),
	_rangeMinimum(std::min(rangeMinimum, rangeMaximum)),
	_rangeMaximum(std::max(rangeMaximum, rangeMinimum))
{
	reset();
}


RunningHistogram::~RunningHistogram()
{
}


void RunningHistogram::reset()
{
	_n = 0;
	_counts.resize(_numBins);
	std::fill(_counts.begin(), _counts.end(), 0);
}


void RunningHistogram::update(double value)
{
	if (value >= _rangeMinimum && value < _rangeMaximum)
	{
		double normalizedValue = (value - _rangeMinimum) / (_rangeMaximum - _rangeMinimum);
		++_counts[std::round(normalizedValue * (_numBins - 1))];
		_n++;
	}
}


uint64_t RunningHistogram::samples() const
{
	return _n;
}


void RunningHistogram::setNumBins(std::size_t numBins)
{
	_numBins = numBins;
	reset();
}


std::size_t RunningHistogram::getNumBins() const
{
	return _numBins;
}


void RunningHistogram::setRangeMinimum(double rangeMinimum)
{
	_rangeMinimum = rangeMinimum;

	if (_rangeMinimum > _rangeMaximum)
	{
		std::swap(_rangeMinimum, _rangeMaximum);
	}

	reset();
}


double RunningHistogram::getRangeMinimum() const
{
	return _rangeMinimum;
}


void RunningHistogram::setRangeMaximum(double rangeMaximum)
{
	_rangeMaximum = rangeMaximum;

	if (_rangeMinimum > _rangeMaximum)
	{
		std::swap(_rangeMinimum, _rangeMaximum);
	}

	reset();
}


double RunningHistogram::getRangeMaximum() const
{
	return _rangeMaximum;
}


const std::vector<std::size_t>& RunningHistogram::counts() const
{
	return _counts;
}


std::vector<std::size_t>::const_iterator RunningHistogram::begin() const
{
	return _counts.begin();
}


std::vector<std::size_t>::const_iterator RunningHistogram::end() const
{
	return _counts.end();
}


} // namespace ofx
