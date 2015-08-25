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


namespace ofx {


/// \brief Compute basic 1D statistics in a single pass.
/// \sa http://www.johndcook.com/blog/skewness_kurtosis/
/// \sa https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
/// \sa http://prod.sandia.gov/techlib/access-control.cgi/2008/086212.pdf
class RunningStatistics
{
public:
	/// \brief Create a RunningStatistics object.
	RunningStatistics();

	/// \brief Destroy the RunningStatistics object.
	~RunningStatistics();

	/// \brief Reset the RunningStatistics.
	void reset();

	/// \brief Update the statistics with a new value.
	/// \param value The value to add.
	void update(double value);

	/// \returns the number of samples used to calculate the statistics.
	uint64_t samples() const;

	/// \returns the arithmetic mean.
	/// \sa https://en.wikipedia.org/wiki/Arithmetic_mean
	double mean() const;

	/// \returns the variance.
	/// \sa https://en.wikipedia.org/wiki/Variance
	double variance() const;

	/// \returns the standard deviation.
	/// \sa https://en.wikipedia.org/wiki/Standard_deviation
	double standardDeviation() const;

	/// \returns the skewness.
	/// \sa https://en.wikipedia.org/wiki/Skewness
	double skewness() const;

	/// \returns the kurtosis.
	/// \sa https://en.wikipedia.org/wiki/Kurtosis
	double kurtosis() const;

	/// \returns the maximum value;
	double maximum() const;

	/// \returns the minimum value;
	double minimum() const;

	friend RunningStatistics operator + (const RunningStatistics& a, const RunningStatistics& b);

private:
	/// \brief Number of samples.
	uint64_t _n;

	/// \brief The mean.
	double _M1;

	/// \brief M2 term.
	double _M2;

	/// \brief M3 term.
	double _M3;

	/// \brief M4 term.
	double _M4;

	/// \brief The maximum value.
	double _maximum;

	/// \brief The minimum value.
	double _minimum;
};


RunningStatistics operator + (const RunningStatistics& a, const RunningStatistics& b)
{
	RunningStatistics combined;

	combined._n = a._n + b._n;

	double delta = b._M1 - a._M1;
	double delta2 = delta*delta;
	double delta3 = delta*delta2;
	double delta4 = delta2*delta2;

	combined._M1 = (a._n * a._M1 + b._n * b._M1) / combined._n;
	combined._M2 = a._M2 + b._M2 + delta2 * a._n * b._n / combined._n;

	combined._M3 = a._M3 + b._M3 + delta3 * a._n * b._n * (a._n - b._n) / (combined._n * combined._n);
	combined._M3 += 3.0 * delta * (a._n * b._M2 - b._n * a._M2) / combined._n;

	combined._M4 = a._M4 + b._M4 + delta4 * a._n * b._n * (a._n * a._n - a._n * b._n + b._n * b._n) / (combined._n * combined._n * combined._n);
	combined._M4 += 6.0 * delta2 * (a._n * a._n * b._M2 + b._n * b._n * a._M2 ) / (combined._n * combined._n) + 4.0 * delta * (a._n * b._M3 - b._n * a._M3) / combined._n;
	
	return combined;
}


} // namespace ofx
