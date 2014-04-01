//// =============================================================================
////
//// Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
////
//// Permission is hereby granted, free of charge, to any person obtaining a copy
//// of this software and associated documentation files (the "Software"), to deal
//// in the Software without restriction, including without limitation the rights
//// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//// copies of the Software, and to permit persons to whom the Software is
//// furnished to do so, subject to the following conditions:
////
//// The above copyright notice and this permission notice shall be included in
//// all copies or substantial portions of the Software.
////
//// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//// THE SOFTWARE.
////
//// =============================================================================
//
//#pragma once
//
//template<typename T>
//class ofxDataBuffer_ {
//public:
//
//    enum Mode {
//        FIXED       = 0,
//        CIRCULAR    = 1,
//        PASSTHROUGH = 2
//    };
//
//    ofxDataBuffer_();
//	
//	virtual ~ofxDataBuffer_();
//    
//    void push_back(const T& data,      bool expand = false);
//    
//    void   setMaxBufferSize(size_t _maxBufferSize);
//    size_t getMaxBufferSize();
//    
//    void   clear();  // resets the count.  does not clear or resize the underlying buffer
//    
//    size_t size()  const;
//    bool   empth() const;
//
//    bool  isEmpty() const; // is the count == 0?
//
//    bool isLocked() const;
//    void setLocked(bool locked);
//    
//private:
//    bool _locked;
//    
//    
//    deque<T> buffer;
//    
//};
//
//template<typename T>
//ofxDataBuffer_<T>::ofxDataBuffer_(){
//    maxSize        = 1;
//    statsValid     = false;
//}
//
//template<typename T>
//ofxDataBuffer_<T>::ofxDataBuffer_(size_t _maxSize){
//    maxSize        = _maxSize;
//    statsValid     = false;
//}
//
//template<typename T>
//ofxDataBuffer_<T>::ofxDataBuffer_(const vector<T>& data){
//    maxSize        = data.size();
//    push_back(data,true);
//}
//
//template<typename T>
//ofxDataBuffer_<T>::ofxDataBuffer_(T* data, int length){
//    maxSize        = length;
//    push_back(data,length,true);
//}
//
//template<typename T>
//ofxDataBuffer_<T>::~ofxDataBuffer_(){}
//
//template<typename T>
//void ofxDataBuffer_<T>::push_back(const T& data, bool expand){
//    
//    buffer.push_back(data); // buffer it
//    
//    if(buffer.size() > maxSize) {
//        buffer.erase(buffer.begin()); // remove the last one
//    }
//    
//    statsValid = false;
//}
//
//template<typename T>
//void ofxDataBuffer_<T>::push_back(const vector<T>& data, bool expand) {
//    for(int i = 0; i < (int)data.size(); i++) push_back(data[i], expand);
//}
//
//
//template<typename T>
//void ofxDataBuffer_<T>::push_back(T* data, int length, bool expand) {
//    for(int i = 0; i < length; i++) push_back(data[i], expand);
//}
//
//template<typename T>
//void ofxDataBuffer_<T>::setMaxBufferSize(size_t _maxSize) {
//    maxSize = _maxSize;
//    
//    // will remove values on next
//    while(buffer.size() > maxSize) {
//        buffer.erase(buffer.begin()); // remove the last one
//    }
//}
//
//template<typename T>
//size_t ofxDataBuffer_<T>::getMaxBufferSize() {
//    return maxSize;
//}
//
//template<typename T>
//size_t ofxDataBuffer_<T>::getSize() {
//    return buffer.size();
//}
//
//
//template<typename T>
//T ofxDataBuffer_<T>::getLast(){
//    return buffer[getSize()-1];
//}
//
//template<typename T>
//T ofxDataBuffer_<T>::getFirst(){
//    return buffer[0];
//}
