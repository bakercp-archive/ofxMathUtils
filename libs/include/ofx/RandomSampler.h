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


#pragma once


namespace ofx {


/// \brief A class that allows sampling without replacement.
///
/// The RandomSampler will get values between 0 and size - 1.  These values
/// can be used as indicies to sample from for an array collection.
class RandomSampler
{
public:
	/// \brief Create a RandomSampler.
	/// \param size The total number of indicies.
	RandomSampler(std::size_t size = 1);

	/// \brief Reset the RandomSampler.
	void reset() const;;

	/// \returns The next index from the RandomSampler.  If all values have
	///			 been exhausted, the RandomSampler is reset and the next index
	///			 is returned.
	std::size_t next() const;

	/// \brief Set the size of the RandomSampler.
	/// \param size The total number of indicies.
	void setSize(std::size_t size);

	/// \returns The total number of indicies.
	std::size_t getSize() const;

private:
	/// \brief The shuffled collection of indices.
    mutable std::vector<std::size_t> _indicies;

	/// \brief The current iterator to the indices.
    mutable std::vector<std::size_t>::iterator _iterator;
    
};


} // namespace ofx