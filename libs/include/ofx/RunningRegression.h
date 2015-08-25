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


#include "ofx/RunningStatistics.h"


namespace ofx {


/// \brief Calculate the running Linear Regression in one pass.
/// \sa http://www.johndcook.com/blog/running_regression/
class RunningRegression
{
public:
	/// \brief Create a RunningRegression.
	RunningRegression();

	/// \brief Destroy the RunningRegression.
	~RunningRegression();

	/// \brief Reset the statistics.
	void reset();

	/// \brief Update the regression with a new coordinate.
	/// \param x The x coordiante.
	/// \param y The y coordinate.
	void update(double x, double y);

	/// \returns the number of samples used to calculate the statistics.
	uint64_t samples() const;

	/// \returns the slope of the regresion.
	double slope() const;

	/// \returns the intercept of the regression.
	double intercept() const;

	/// \returns the correlation of the regression.
	double correlation() const;

	friend RunningRegression operator + (const RunningRegression& a,
										const RunningRegression& b);

private:
	RunningStatistics _xStats;

	RunningStatistics _yStats;

	double _sxy;

	uint64_t _n;

};


RunningRegression operator + (const RunningRegression& a, const RunningRegression& b)
{
	RunningRegression combined;

	combined._xStats = a._xStats + b._xStats;
	combined._yStats = a._yStats + b._yStats;
	combined._n = a._n     + b._n;

	double delta_x = b._xStats.mean() - a._xStats.mean();
	double delta_y = b._yStats.mean() - a._yStats.mean();
	combined._sxy = a._sxy + b._sxy + static_cast<double>(a._n * b._n) * delta_x * delta_y / static_cast<double>(combined._n);

	return combined;
}


} // namespace ofx
