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


/// \sa http://www.johndcook.com/blog/skewness_kurtosis/
template<typename T>
class RunningStatistics
{
public:
	void reset();

	/// \returns the number of samples used to calculate the statistics.
	uint64_t samples();

	double mean() const;
	double variance() const;
	double standardDeviation() const;
	double skewness() const;
	double kurtosis() const;

	void attach(Accumulator<T>& accumulator, int priority = OF_EVENT_ORDER_AFTER_APP);
	void detatch(Accumulator<T>& accumulator, int priority = OF_EVENT_ORDER_AFTER_APP);

private:
	void onPushed(const void* sender, const T& value);
	void onPopped(const void* sender, const T& value);
	void onCleared(const void* sender);
	void onCapacityChanged(const void* sender, std::size_t& size);

	/// \brief A pointer to the accumulator.
	Accumulator<T>* _accumulator = nullptr;

	/// \brief Number of samples.
	uint64_t _n;

	/// \brief Va
	double _M1 = 0.0;
	double _M2 = 0.0;
	double _M3 = 0.0;
	double _M4 = 0.0;

	/// \brief Allow access the private callbacks.
	friend class Accumulator<T>;
};


template<typename T>
void RunningStatistics<T>::reset()
{
	_n = 0;

	_M1 = _M2 = _M3 = _M4 = 0.0;
}


template<typename T>
double RunningStatistics<T>::mean() const
{
	return _M1;
}


template<typename T>
double RunningStatistics<T>::variance() const
{
	return _M2 / (_n - 1.0);
}


template<typename T>
double RunningStatistics<T>::standardDeviation() const
{
	return sqrt(variance());
}


template<typename T>
double RunningStatistics<T>::skewness() const
{
	return sqrt(double(_n)) * _M3/ pow(_M2, 1.5);
}


template<typename T>
double RunningStatistics<T>::kurtosis() const
{
	return double(_n) * _M4 / (_M2 * _M2) - 3.0;
}


template<typename T>
void RunningStatistics<T>::attach(Accumulator<T>& accumulator, int priority)
{
	accumulator.registerAllEvents(this, priority);
	_accumulator = &accumulator;
}


template<typename T>
void RunningStatistics<T>::detatch(Accumulator<T>& accumulator, int priority)
{
	accumulator.unregisterAllEvents(this, priority);
	_accumulator = nullptr;
}


template<typename T>
void RunningStatistics<T>::onPushed(const void* sender, const T& value)
{
	if (sender == _accumulator)
	{
		double delta, delta_n, delta_n2, term1;

		double x = value;

		uint64_t n1 = _n;
		_n++;
		delta = x - _M1;
		delta_n = delta / _n;
		delta_n2 = delta_n * delta_n;
		term1 = delta * delta_n * n1;
		_M1 += delta_n;
		_M4 += term1 * delta_n2 * (_n*_n - 3*_n + 3) + 6 * delta_n2 * _M2 - 4 * delta_n * _M3;
		_M3 += term1 * delta_n * (_n - 2) - 3 * delta_n * _M2;
		_M2 += term1;
	}
}


template<typename T>
void RunningStatistics<T>::onPopped(const void* sender, const T& value)
{
	if (sender == _accumulator)
	{

	}
}


template<typename T>
void RunningStatistics<T>::onCleared(const void* sender)
{
	if (sender == _accumulator)
	{
		reset();
	}
}


template<typename T>
void RunningStatistics<T>::onCapacityChanged(const void* sender, std::size_t& size)
{
	if (sender == _accumulator)
	{
		reset();
	}
}


} // namespace ofx
