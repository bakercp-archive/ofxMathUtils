/*==============================================================================
 
 Copyright (c) 2010, 2011, 2012 Christopher Baker <http://christopherbaker.net>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ==============================================================================*/

#pragma once


class ofxRandomSampler
{
public: 
    ofxRandomSampler(std::size_t size = 0):
        _index(0),
        _size(0),
        _vals(0)
    {
        setSize(size);
    }
    
    virtual ~ofxRandomSampler() {
        delete[] _vals;
    }
    
    void reset() {
    	for(size_t i = 0; i <_size; i++) {
			_vals[i] = i;
		}

        // Fisher-Yates shuffle
		for (int i = _size; i > 0; --i)
        {
            std::size_t rnd = i * rand() / (RAND_MAX + 1.0f);
			assert(rnd >=0 && rnd < i);
			swap(_vals[i-1], _vals[rnd]);
		}

		_index = 0;
    }
    
    std::size_t next()
    {
		if (_index == _size)
        {
            reset(); // re-init
			return next();
		} else {
			return _vals[_index++];
		}
    }
    
    void setSize(std::size_t size)
    {
        delete [] _vals;
        _size = size;
        _vals = new std::size_t[size];
        reset();
    }
    
    std::size_t getSize() const
    {
        return _size;
    }
    
private:
    std::size_t  _index;
    std::size_t  _size;
    std::size_t* _vals;
};
