/* Written by: William Chen
 * Date: 18/07/2019
 * 
 * Description: This class will be used to filter
 *  a series of data using a ring buffer.
*/

#ifndef FILTER_H
#define FILTER_H

#include "RingBuffer.h"

template <typename T>
class Filter {
private:
    RingBuffer<T> *_buffer;
    T *_coefficients;
    int _size;
public:
    Filter();
    Filter(T *coefficients, int size);
    ~Filter();
    
    void push(T newVal);
    T value();
};

template <typename T>
Filter<T>::Filter() {
    _size = 1;
    _coefficients = new T[_size];
    _buffer = new RingBuffer<T>(_size);
    
    _buffer->insert(0);
    _coefficients[0] = 1;
}

template <typename T>
Filter<T>::Filter(T *coefficients, int size) {
    _coefficients = new T[size];
    _buffer = new RingBuffer<T>(size);
    _size = size;
    
    // Initialize buffer and coefficient arrays
    for (int i = 0; i < size; i++) {
        _buffer->insert(0);
        _coefficients[i] = coefficients[i];
    }
}

template <typename T>
Filter<T>::~Filter() {
    if (_buffer != NULL)
        delete _buffer;
    
    if (_coefficients != NULL)
        delete[] _coefficients;
}

template<typename T>
void Filter<T>::push(T newVal) {
    _buffer->insert(newVal);
}

template<typename T>
T Filter<T>::value() {
    T val = 0;
    
    for (int i = 0; i < _size; i++) {
        //std::cout << _coefficients[i] << " " << _buffer->peek(i) << std::endl;
        val += (T) _coefficients[i] * _buffer->peek(i);
    }
    
    return val;
}

#endif // FILTER_H