#ifndef SRC_S21_ARRAY_H_
#define SRC_S21_ARRAY_H_

#include <cstddef>
#include <cstring>
#include <initializer_list>
#include <cmath>

namespace s21 {
template <class T, std::size_t S>
class Array {
 private:
    size_t m_size_;
    size_t size_;
    T *arr_;

 public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;
    using const_iterator = const T *;
    using iterator = T *;

    Array();
    Array(std::initializer_list<value_type> const &items);
    Array(const Array &a);
    Array(Array &&a);

    ~Array();

    Array<T, S> &operator=(Array &other);
    reference operator[](size_type pos);

    void print();
    void deletArray_();
    reference at(size_type pos);

    const_reference front();
    const_reference back();
    iterator data();

    T& operator++ (int) { return *arr_++;}
    T& operator-- (int) { return *arr_--;}
    T& operator++ () { return *++arr_;}
    T& operator-- () { return *--arr_;}

    iterator begin();
    iterator end();
    bool empty();
    size_type size();
    size_type max_size();
    void swap(Array& other);
    void fill(const_reference value);
};
};  // namespace s21

#endif  // SRC_S21_ARRAY_H_
