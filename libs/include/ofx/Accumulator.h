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


#include "ofEvents.h"


namespace ofx {


/// \brief An accumulator for a given type.
///
/// An accumulator is a FIFO structure with a fixed capacity.
///
/// It emits AccumulatorEvents on changes to its contents.
///
/// \tparam T The accumulated type.
template<typename T>
class Accumulator
{
public:
	/// \brief A typedef for the Accumulator's iterator.
	typedef typename std::deque<T>::const_iterator const_iterator;

	/// \brief Create an accumulator for the given type.
	/// \param capacity set the capacity of the accumulator.
    Accumulator(std::size_t capacity = DEFAULT_CAPACITY);

	/// \brief Destroy the Accumulator.
	~Accumulator();

	/// \brief Set the capacity of the Accumulator.
	///
	/// Setting the capacity to will clear the Accumulator.
	///
	/// \param capacity The new capacity of the Accumulator.
    void setCapacity(std::size_t capacity);

	/// \returns the current capacity of the Accumulator.
    std::size_t getCapacity() const;

	/// \returns true if the Accumulator is empty.
	bool empty() const;

	/// \returns true if the Accumulator is full.
	bool full() const;

	/// \returns the number of elements in the Accumulator.
    std::size_t size() const;

	/// \brief Push a value into the Accumulator.
	///
	/// If the additional value causes the Accumulator to exceed its capacity
	/// the oldest value will be removed from the Accumulator.
	///
	/// \param value The value to push into the Accumulator.
    void push(const T& value);

	/// \brief Remove all values from the Accumulator.
    void clear();

	/// \brief Get the iterator to the beginning of the Accumulator data.
	const_iterator begin() const;

	/// \brief Get the iterator to the end of the Accumulator data.
	const_iterator end() const;

	/// \brief Called when a value is added to the Accumulator.
	ofEvent<const T> onPushed;

	/// \brief Called when a value is removed to the Accumulator.
	ofEvent<const T> onPopped;

	/// \brief Called whtn the Accumulator is cleared.
	ofEvent<void> onCleared;

	/// \brief Called when the Accumulator's capacity was changed.
	ofEvent<std::size_t> onCapacityChanged;

    /// \brief Register a class to receive notifications for all events.
    /// \param listener a pointer to the listener class.
    /// \param order the event order.
    template<class ListenerClass>
    void registerAllEvents(ListenerClass* listener, int priority = OF_EVENT_ORDER_AFTER_APP)
    {
        ofAddListener(onPushed, listener, &ListenerClass::onPushed, priority);
        ofAddListener(onPopped, listener, &ListenerClass::onPopped, priority);
        ofAddListener(onCleared, listener, &ListenerClass::onCleared, priority);
        ofAddListener(onCapacityChanged, listener, &ListenerClass::onCapacityChanged, priority);
    }

    /// \brief Unregister a class to receive notifications for all events.
    /// \param listener a pointer to the listener class.
	/// \param order the event order.
    template<class ListenerClass>
    void unregisterAllEvents(ListenerClass* listener, int priority = OF_EVENT_ORDER_AFTER_APP)
    {
		ofRemoveListener(onPushed, listener, &ListenerClass::onPushed, priority);
		ofRemoveListener(onPopped, listener, &ListenerClass::onPopped, priority);
		ofRemoveListener(onCleared, listener, &ListenerClass::onCleared, priority);
		ofRemoveListener(onCapacityChanged, listener, &ListenerClass::onCapacityChanged, priority);
    }

    enum
    {
		/// \brief The default capacity for the accumulator.
        DEFAULT_CAPACITY = 1
    };

private:
	/// \brief The callback for ofParameter listeners.
	/// \param value The callback value.
	void onParameter(T& value);

	/// \brief Pop a value out of the Accumulator.
	void pop();

	/// \brief The capacity of the accumulator.
    std::size_t _capacity;

	/// \brief The container for the accumulator.
	std::deque<T> _accumulator;

	friend class ofParameter<T>;
};


template<typename T>
Accumulator<T>::Accumulator(std::size_t capacity): _capacity(capacity)
{
}


template<typename T>
Accumulator<T>::~Accumulator()
{
}


template<typename T>
void Accumulator<T>::setCapacity(std::size_t capacity)
{
	clear();
	_capacity = capacity;
	ofNotifyEvent(onCapacityChanged, _capacity, this);
}


template<typename T>
std::size_t Accumulator<T>::getCapacity() const
{
    return _capacity;
}


template<typename T>
std::size_t Accumulator<T>::size() const
{
    return _accumulator.size();
}


template<typename T>
bool Accumulator<T>::empty() const
{
    return _accumulator.empty();
}


template<typename T>
bool Accumulator<T>::full() const
{
	return _accumulator.size() == _capacity;
}


//template<typename T>
//void Accumulator<T>::attach(ofParameter<T>& parameter, int priority)
//{
//	parameter.addListener(this, &Accumulator<T>::onParameter, priority);
//}
//
//
//template<typename T>
//void Accumulator<T>::detatch(ofParameter<T>& parameter, int priority)
//{
//	parameter.removeListener(this, &Accumulator<T>::onParameter, priority);
//}


template<typename T>
void Accumulator<T>::push(const T& value)
{
	while (_capacity <= _accumulator.size())
	{
		pop();
	}

	_accumulator.push_back(value);
	ofNotifyEvent(onPushed, value, this);
}


template<typename T>
void Accumulator<T>::onParameter(T& value)
{
	push(value);
}


template<typename T>
void Accumulator<T>::pop()
{
    const T front = _accumulator.front();
	_accumulator.pop_front();
    ofNotifyEvent(onPopped, front, this);
}


template<typename T>
void Accumulator<T>::clear()
{
    _accumulator.clear();
    ofNotifyEvent(onCleared, this);
}



template<typename T>
typename Accumulator<T>::const_iterator Accumulator<T>::begin() const
{
	return _accumulator.begin();
}


template<typename T>
typename Accumulator<T>::const_iterator Accumulator<T>::end() const
{
	return _accumulator.end();
}


} // namespace ofx
