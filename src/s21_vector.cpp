#include "s21_vector.h"
using namespace s21;

template <typename T>
Vector<T>::Vector() : Vector<T>(0) { }

template <typename T>
Vector<T>::Vector(const Vector &other) : Vector<T> (other.m_size_) {
    this->m_size_ = other.m_size_;
    this->size_ = other.size_;
    std::memcpy(this->arr_, other.arr_, other.size_ * sizeof(T));
}

template <typename T>
Vector<T>::Vector(Vector &&other) : Vector<T> (other) {
    other.clearVector();
}

template <typename T>
Vector<T>::Vector(size_type n) {
    this->m_size_ = (n == 0) ? 0 : n * 2;
    this->m_capacity_ = m_carpt * (sizeof(int)/sizeof(T));
    this->size_ = n;
    this->arr_ = new T[m_size_ + 1]();
}

template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const &items) {
    this->arr_ = new T[items.size() * 2];
    this->size_ = items.size();
    this->m_size_ = items.size() * 2 + 1;
    this->m_size_ = items.size();
    this->m_capacity_ =  m_carpt * (sizeof(int)/sizeof(T));

    for (auto i = 0, it = items.begin(); it != items.end(); it++, i++)
        this->arr_[i] = *it;
}

template <typename T>
Vector<T>::~Vector() {
    clearVector();
}

template <typename T>
void Vector<T>::clearVector() {
    delete[] this->arr_;
    this->size_ = 0;
    this->m_size_ = 0;
    this->m_capacity_ = 0;
    this->arr_ = nullptr;
}

template <typename T>
void Vector<T>::erase(iterator pos) {
    auto position = (this->begin() - pos);
    if (position < 0) {position *= -1;}
    if (position <= this->size()) {
        memmove(this->arr_ + position, this->arr_ + position + 1, (m_size_ - position + 1) * sizeof(T));
        --this->size_;
    }
}

template <typename T>
template<typename ...Args>
typename Vector<T>::iterator Vector<T>::emplace(const_iterator pos, Args&&... args) {
    return this->insert(pos, (value_type(std::forward<Args>(args)...)));
}

template <typename T>
template<typename ...Args>
void Vector<T>::emplace_back(Args&&... args) {
    this->insert(this->end(), (value_type(std::forward<Args>(args)...)));
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, const_reference value) {
    int position = (this->begin() - pos);
    if (position < 0) {position *= -1;}
    // this->checkSize(position + 1);
    this->checkSize(position);
    if (size_ >= m_size_) {this->addMemory(this->size_ * 2);}
    memmove(this->arr_ + position, this->arr_ + position - 1, (m_size_ - position) * sizeof(T));
    this->arr_[position] = value;
    this->size_++;
    return this->arr_ + position;
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() {  // получить доступ к первому элементу
    return this->arr_[0];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() {
    return this->arr_[size_ - 1];
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
    return this->at(pos);
}

template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
    if (pos >= size_) {throw std::range_error("Incorrect position");}
    return this->arr_[pos];
}

template <typename T>
void Vector<T>::push_back(const_reference value) {
    if (size_ >= m_size_) {this->addMemory(this->size_ * 2);}
    this->arr_[this->size_] = value;
    this->size_++;
}

template <typename T>
void Vector<T>::pop_back() {
    this->checkSize(0);
    this->arr_[this->size_ - 1] = T();
    this->size_--;
}

template <typename T>
bool Vector<T>::empty() {
    return (this->size_ == 0);
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() {
    return this->size_;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() {
    return this->m_size_;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::max_size() {
    return this->m_capacity_;
}

template <typename T>
void Vector<T>::clear() {
    for (auto i = this->m_size_; i > 0; i--)
        this->pop_back;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    this->checkSize(0);
    this->m_size_ -= (this->m_size_ - this->size_);
    this->transMemory();
}

template <typename T>
void Vector<T>::swap(Vector& other) {
    Vector<T> tmp(*this);
    *this = other;
    other = tmp;
}
template <typename T>
void Vector<T>::reserve(size_type size) {
    if (size > this->m_size_)
        this->addMemory(size);
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> &other) {
    this->arr_ = new T[other.m_size_];
    std::memcpy(this->arr_, other.arr_, other.m_size_ * sizeof(T));
    this->m_size_ = other.m_size_;
    this->size_ = other.size_;
    return *this;
}

template <typename T>
void Vector<T>::checkSize(size_type pos) {
    if (this->size_ < 0 || this->size_ > m_capacity_ ||  this->size_ < pos)
        throw std::range_error("Incorrect size");
}

template <typename T>
void Vector<T>::addMemory(size_type value) {
    this->checkSize(0);
    this->m_size_ = value;
    this->transMemory();
}

template <typename T>
void Vector<T>::transMemory() {
    T* tmp = this->arr_;
    this->arr_ = new T[this->m_size_ + 1]();
    std::memcpy(this->arr_, tmp, this->size_ * sizeof(T));
    delete[] tmp;
}

template <typename T>
void Vector<T>::printVector() {
    for (size_t i = 0; i < this->size_; i++)
        std::cout << this->arr_[i];
}
