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


#include <cstdint>
#include <cstddef>
#include <vector>


namespace ofx {


/// \brief A simple running histogram with equally sized bins.
class RunningHistogram
{
public:
	/// \brief A typedef for a const_iterator.
	typedef std::vector<std::size_t>::const_iterator const_iterator;

	/// \brief Create a RunningHistogram object.
	///
	/// The bin boundaries will be calculated from the numBins, rangeMinimum and
	/// rangeMaximum.  Values outside of the range will be ignored.
	///
	/// \param numBins The number of bins in the histogram.
	/// \param rangeMinimum The minimum range of the histogram.
	/// \param rangeMaximum The maximum range of the histogram.
	RunningHistogram(std::size_t numBins = 10,
					 double rangeMinimum = 0.0,
					 double rangeMaximum = 1.0);

	/// \brief Destroy the RunningHistogram object.
	~RunningHistogram();

	/// \brief Reset the RunningHistogram.
	void reset();

	/// \brief Update the histogram with a new value.
	/// \param value The value to add.
	void update(double value);

	/// \returns the number of samples used to calculate the statistics.
	uint64_t samples() const;
	
	/// \brief Set the number of bins in the histogram.
	///
	/// This will reset the histogram.
	///
	/// \param numBins The number of bins.
	void setNumBins(std::size_t numBins);

	/// \returns the number of bins in the histogram.
	std::size_t getNumBins() const;

	/// \brief Set the minimum range of the histogram.
	///
	/// If the minimum is larger than the maximum, the values will be swapped.
	///
	/// This will reset the histogram.
	///
	/// \param minimum The minimum range of the histogram.
	void setRangeMinimum(double minimumRange);

	/// \returns The minimum bound of the histogram.
	double getRangeMinimum() const;

	/// \brief Set the maximum bound of the histogram.
	///
	/// If the maximum is smaller than the minimum, the values will be swapped.
	///
	/// This will reset the histogram.
	///
	/// \param maximum The maximum bound of the histogram.
	void setRangeMaximum(double rangeMaximum);

	/// \returns The maximum bound of the histogram.
	double getRangeMaximum() const;

	/// \returns the counts.
	const std::vector<std::size_t>& counts() const;

	/// \returns An iterator to the counts.
	std::vector<std::size_t>::const_iterator begin() const;

	/// \returns An end iterator to the counts.
	std::vector<std::size_t>::const_iterator end() const;

private:
	/// \brief The number of bins in the histogram.
	size_t _numBins;

	/// \brief The minimum bound of the histogram.
	double _rangeMinimum;

	/// \brief The maximum bound of the histogram.
	double _rangeMaximum;

	/// \brief Number of samples.
	uint64_t _n;

	/// \brief The counts.
	std::vector<std::size_t> _counts;

};


} // namespace ofx
