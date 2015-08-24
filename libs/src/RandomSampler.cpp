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



#include "ofx/RandomSampler.h"
#include <algorithm>
#include <random>


namespace ofx {


RandomSampler::RandomSampler(std::size_t size)
{
	setSize(size);
}

	
void RandomSampler::reset() const
{
	std::shuffle(_indicies.begin(), _indicies.end());
	_iterator = _indicies.begin();
}


std::size_t RandomSampler::next() const
{
	if (_iterator == _indicies.end())
	{
		reset();
		return next();
	}
	else
	{
		return *_iterator++;
	}
}


void RandomSampler::setSize(std::size_t size)
{
	// Require size > 0.
	assert(size > 0);

	// Resize the indices for new size.
	_indicies.resize(size);

	// Fill with indicies 0 ... n.
	std::iota(_indicies.begin(), _indicies.end(), 0);

	// Reset the sampler.
	reset();
}


std::size_t RandomSampler::getSize() const
{
	return _indicies.size();
}


} // namespace ofx
