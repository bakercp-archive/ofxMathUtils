// =============================================================================
//
// Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
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


#include <vector>
#include <set>


namespace ofx {


template<typename T>
class DataBuffer_
{
public:
    DataBuffer_();
    DataBuffer_(std::size_t maxSize);
    DataBuffer_(const vector<T>& data);
    DataBuffer_(T* data, std::size_t length);
	
	virtual ~DataBuffer_();
    
    void push_back(const T& data,      bool expand = false);
    void push_back(const vector<T>& v, bool expand = false);
    void push_back(T* v, std::size_t length, bool expand = false);
 
    void   setMaxBufferSize(std::size_t _maxBufferSize);
    std::size_t getMaxBufferSize() const;
    
    std::size_t getSize() const;
    
    // buffer statistics
    void calcStats();
    bool statsValid;
    
    T getLast();
    T getFirst();
    
    T getMin();
	T getMax();
    
    std::size_t getMinIndex();
    std::size_t getMaxIndex();
    
    double getSum();
    double getProduct();
    double getMean();
    double getHarmonicMean();
    double getGeometricMean();
    double getVariance();
    double getStdDev();
    double getPopulationVariance();
    double getPopulationStdDev();
    
    double getMedian();

protected:
    std::deque<T> buffer;

private:
    double sum;
    double product;
    double variance;
    double variancePopulation;
    
    double mean;
    double harmMean;
    double geoMean;
    double stdDev;
    double stdDevPopulation;
    
    T minimum;
    std::size_t minimumIdx;
    T maximum;
    std::size_t maximumIdx;
    
    
    std::size_t maxSize;
    
};

template<typename T>
DataBuffer_<T>::DataBuffer_(): maxSize(1), statsValid(false)
{
}

template<typename T>
DataBuffer_<T>::DataBuffer_(std::size_t _maxSize):
    maxSize(_maxSize),
    statsValid(false)
{
}

template<typename T>
DataBuffer_<T>::DataBuffer_(const vector<T>& data):
    maxSize(1),
    statsValid(false)
{
    push_back(data, true);
}

template<typename T>
DataBuffer_<T>::DataBuffer_(T* data, std::size_t length):
    maxSize(length),
    statsValid(false)
{
    push_back(data, length, true);
}

template<typename T>
DataBuffer_<T>::~DataBuffer_()
{
}


//template<typename T>
//std::deque<T>& DataBuffer_<T>::getBufferRef()
//{
//    return buffer;
//}

template<typename T>
void DataBuffer_<T>::calcStats()
{
    
    if(statsValid)
    {
        return;
    }
    else
    {
        statsValid = true;
    }
    
    sum         = 0.0;
    product     = 0.0;
    variance    = 0.0;
    mean        = 0.0;
    harmMean    = 0.0;
    geoMean     = 0.0;
    stdDev      = 0.0;
    minimum     = 0.0;
    maximum     = 0.0;

    minimumIdx  = 0;
    maximumIdx  = 0;
    
    if(buffer.empty()) return;
    
    bool hasNegativeValues = false;
    
    int    n      = 0;
    double delta  = 0.0;
    double M2     = 0.0;
    double invSum = 0.0;
    
    for(size_t i = 0; i < buffer.size(); ++i)
    {
        T value = buffer[i];
        double invValue = 1.0 / value;
        if(value < 0) hasNegativeValues = true;

        n = n+1;
        
        if(i == 0) {
            sum       = value;
            product   = value;
            invSum    = invValue;
            minimum   = value;
            maximum   = value;
            minimumIdx  = 0;
            maximumIdx  = 0;

        } else {
            sum      += value;
            product  *= value;
            invSum   += invValue;
            
            if(value < minimum) {
                minimum    = value;
                minimumIdx = i;
            }
            
            if(value > maximum) {
                maximum    = value;
                maximumIdx = i;
            }
        }

        
        delta = value - mean;
        mean  = mean + delta/n;
        M2    = M2 + delta * (value - mean);

    }
    
    harmMean           = hasNegativeValues ? -1 : (n / invSum);
    geoMean            = hasNegativeValues ? -1 : pow(product, 1.0 / n);

    variancePopulation = M2 / (n);
    variance           = M2 / (n - 1);

    stdDevPopulation   = sqrt(variancePopulation);
    stdDev             = sqrt(variance);
}

template<typename T>
void DataBuffer_<T>::push_back(const T& data, bool expand)
{
    buffer.push_back(data); // buffer it

    if(buffer.size() > maxSize)
    {
        buffer.erase(buffer.begin()); // remove the last one
    }
    
    statsValid = false;
}

template<typename T>
void DataBuffer_<T>::push_back(const vector<T>& data, bool expand)
{
    for(int i = 0; i < (int)data.size(); i++) push_back(data[i], expand);
}


template<typename T>
void DataBuffer_<T>::push_back(T* data, std::size_t length, bool expand)
{
    for(std::size_t i = 0; i < length; i++) push_back(data[i], expand);
}

template<typename T>
void DataBuffer_<T>::setMaxBufferSize(size_t _maxSize) {
    maxSize = _maxSize;

    // will remove values on next
    while(buffer.size() > maxSize) {
        buffer.erase(buffer.begin()); // remove the last one
        statsValid = false;
    }
}

template<typename T>
std::size_t DataBuffer_<T>::getMaxBufferSize() const
{
    return maxSize;
}

template<typename T>
std::size_t DataBuffer_<T>::getSize() const
{
    return buffer.size();
}


template<typename T>
T DataBuffer_<T>::getLast()
{
    return buffer[getSize()-1];
}

template<typename T>
T DataBuffer_<T>::getFirst()
{
    return buffer[0];
}

template<typename T>
T DataBuffer_<T>::getMin()
{
    calcStats();
    return minimum;
}

template<typename T>
T DataBuffer_<T>::getMax()
{
    calcStats();
    return maximum;
}

template<typename T>
std::size_t DataBuffer_<T>::getMinIndex()
{
    calcStats();
    return minimumIdx;
}

template<typename T>
std::size_t DataBuffer_<T>::getMaxIndex()
{
    calcStats();
    return maximumIdx;
}


template<typename T>
double DataBuffer_<T>::getSum()
{
    calcStats();
    return sum;
}

template<typename T>
double DataBuffer_<T>::getProduct()
{
    calcStats();
    return product;
}

template<typename T>
double DataBuffer_<T>::getMean()
{
    calcStats();
    return mean;
}

template<typename T>
double DataBuffer_<T>::getHarmonicMean(){
    calcStats();
    return harmMean;
}

template<typename T>
double DataBuffer_<T>::getGeometricMean(){
    calcStats();
    return geoMean;
}

template<typename T>
double DataBuffer_<T>::getMedian(){
    // median is not cached
     
    std::deque<T> bufferCopy = buffer;
    size_t size = bufferCopy.size();
    int    n    = size / 2;

    std::nth_element(bufferCopy.begin(), bufferCopy.begin()+n, bufferCopy.end());
    double med = bufferCopy[n];
    
    if(size % 2 != 0) { // odd
        return med;
    } else { // even
        std::nth_element(bufferCopy.begin(), bufferCopy.begin()+(n - 1), bufferCopy.end());
        return (med + bufferCopy[n - 1]) / 2.0;
    }
}

template<typename T>
double DataBuffer_<T>::getVariance(){
    calcStats();
    return variance;
}

template<typename T>
double DataBuffer_<T>::getStdDev(){
    calcStats();
    return stdDev;
}

template<typename T>
double DataBuffer_<T>::getPopulationVariance(){
    calcStats();
    return variancePopulation;
}

template<typename T>
double DataBuffer_<T>::getPopulationStdDev(){
    calcStats();
    return stdDevPopulation;
}

typedef DataBuffer_<char>   ofxCharDataBuffer;
typedef DataBuffer_<float>  ofxFloatDataBuffer;
typedef DataBuffer_<float>  ofxDataBuffer;
typedef DataBuffer_<double> ofxDoubleDataBuffer;
typedef DataBuffer_<int>    ofxIntDataBuffer;
typedef DataBuffer_<long>   ofxLongDataBuffer;

// http://stackoverflow.com/questions/3903538/online-algorithm-for-calculating-absolute-deviation
// http://www.johndcook.com/standard_deviation.html
// http://stackoverflow.com/questions/1058813/on-line-iterator-algorithms-for-estimating-statistical-median-mode-skewnes
// http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
// http://www.codecogs.com/code/statistics/moments/statistics.php //rt
// http://www.codecogs.com/code/statistics/moments/index.php


} // namespace ofx
