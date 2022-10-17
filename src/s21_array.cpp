#include "s21_array.h"
#include <iostream>

using namespace s21;

template <typename T, std::size_t S>
Array<T, S>::Array() {
    this->m_size_ = S;
    this->size_ = S;
    this->arr_ = new T[this->m_size_]();
}

template <typename T, std::size_t S>
Array<T, S>::Array(const Array &other) : Array<T, S>() {
    this->size_ = other.size_;
    for (size_t i = 0; i < this->m_size_; i++ )
        *(this->arr_ + i) = *(other.arr_ + i);
}

template <typename T, std::size_t S>
Array<T, S>::Array(Array &&other) : Array<T, S>(other) {
    other.deletArray_();
}

template <typename T, std::size_t S>
Array<T, S>::Array(std::initializer_list<value_type> const &items) {
    this->arr_ = new T[S]();
    this->size_ = items.size();
    this->m_size_ = S;

    for (auto i = 0, it = items.begin(); it != items.end(); it++, i++)
        this->arr_[i] = *it;
}

template <typename T, std::size_t S>
Array<T, S>::~Array() {
    this->deletArray_();
}

template <typename T, std::size_t S>
Array<T, S>& Array<T, S>::operator=(Array<T, S> &other) {
    this->arr_ = new T[other.m_size_]();
    std::memcpy(this->arr_, other.arr_, other.m_size_ * sizeof(T));
    this->m_size_ = other.m_size_;
    this->size_ = other.size_;
    return *this;
}

template <typename T, std::size_t S>
typename Array<T, S>::reference Array<T, S>::operator[](size_type pos) {
    return this->at(pos);
}

template <typename T, std::size_t S>
typename Array<T, S>::const_reference Array<T, S>::front() {
    return *(this->arr_);
}

template <typename T, std::size_t S>
typename Array<T, S>::const_reference Array<T, S>::back() {
    return *(this->arr_+ (S-1));
}

template <typename T, std::size_t S>
typename Array<T, S>::iterator Array<T, S>::data() {
    return this->arr_;
}

template <typename T, std::size_t S>
typename Array<T, S>::iterator Array<T, S>::begin() {
    return this->arr_;
}

template <typename T, std::size_t S>
typename Array<T, S>::iterator Array<T, S>::end() {
    return this->arr_ + (S-1);
}

template <typename T, std::size_t S>
bool Array<T, S>::empty() {
    return this->size_ == 0;
}

template <typename T, std::size_t S>
typename Array<T, S>::size_type Array<T, S>::size() {
    return this->m_size_;
}

template <typename T, std::size_t S>
typename Array<T, S>::size_type Array<T, S>::max_size() {
    return S;
}

template <typename T, std::size_t S>
void Array<T, S>::fill(const_reference value) {
    for (size_t i = 0; i < this->m_size_; i++)
        this->arr_[i] = value;
}


template <typename T, std::size_t S>
typename Array<T, S>::reference Array<T, S>::at(size_type pos) {
    if (pos >= this->m_size_) {throw std::range_error("Incorrect position");}
    return this->arr_[pos];
}

template <typename T, std::size_t S>
void Array<T, S>::swap(Array& other) {
    Array<T, S> tmp(*this);
    *this = other;
    other = tmp;
}

template <typename T, std::size_t S>
void Array<T, S>::print() {
    for (size_t i = 0; i < m_size_; i++)
        std::cout << this->arr_[i];
}

template <typename T, std::size_t S>
void Array<T, S>::deletArray_() {
    delete[] this->arr_;
    this->size_ = 0;
    this->m_size_ = 0;
    this->arr_ = nullptr;
}
