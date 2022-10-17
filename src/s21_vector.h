#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

// #include
#include <stdexcept>
#include <cstring>
#include <initializer_list>
#include <cmath>
#include <iostream>
#define m_carpt 2305843009213693951
namespace s21 {
template <class T>
class Vector {
 private:
    size_t m_size_;
    size_t size_;
    size_t m_capacity_;
    T *arr_;

 public:
    class Iterator;
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

 public:
  class VectorIterator;
  class VectorConstantIterator;

  class VectorIterator : public Iterator {
    friend class VectorConstantIterator;
   public:
    VectorIterator() : Iterator() {}
    VectorIterator(value_type * name) : Iterator(name) {}
    VectorIterator(VectorConstantIterator iterator) : Iterator(iterator.iter_) {}
  };

  class VectorConstantIterator : public Iterator {
    friend class VectorIterator;
   public:
    VectorConstantIterator() : Iterator() {}
    VectorConstantIterator(value_type * name) : Iterator(name) {}
    VectorConstantIterator(VectorIterator iterator) : Iterator(iterator.iter_) {}
  };

  class Iterator {
   protected:
    T* iter_;

   public:
    Iterator(value_type * name) : iter_(name) {}
    Iterator() : iter_(nullptr) {}

    T& operator++ (int) { return *iter_++;}
    T& operator-- (int) { return *iter_--;}
    T& operator++ () { return *++iter_;}
    T& operator-- () { return *--iter_;}
    T& operator+= (int n) { for (int i = 0; i < n; i++, this->iter_++); return *iter_;}
    T& operator-= (int n) { for (int i = 0; i < n; i++, this->iter_--); return *iter_;}
    bool operator!= (const Iterator& it) { return this->iter_ != it.iter_; }

    T& operator- (size_type n) {
      for (size_type i = 0; i < n; i++)
        iter_--;
      return *iter_;
    }

    T& operator+ (size_type n) {
      for (size_type i = 0; i < n; i++)
        iter_++;
      return *iter_;
    }

    size_type operator- (Iterator & other) { return (other.iter_ - this->iter_);}

    T& operator* () { return *iter_ ;}
    bool operator== (Iterator & other ) { return iter_ == other.iter_ ;}
  };

    using iterator = VectorIterator;
    using const_iterator = VectorConstantIterator;

 public:
    iterator data() { return arr_;}
    iterator begin() { return arr_;}
    iterator end() {return arr_ + size_; }

    iterator insert(iterator pos, const_reference value);
    void erase(iterator pos);

    Vector(std::initializer_list<value_type> const &items);
    Vector();
    explicit Vector(size_type n);
    Vector(const Vector &other);
    Vector(Vector &&other);

    ~Vector();

    reference operator[](size_type pos);
    Vector<T>& operator=(Vector<T> &other);

    template<typename ...Args>
    iterator emplace(const_iterator pos, Args&&... args);

    template<typename ...Args>
    void emplace_back(Args&&... args);

    void reserve(size_type size);
    void swap(Vector& other);
    bool empty();
    void shrink_to_fit();
    reference at(size_type pos);
    const_reference front();
    const_reference back();
    void clear();
    void push_back(const_reference value);
    void pop_back();
    size_type capacity();
    size_type max_size();
    size_type size();
    void checkSize(size_type pos);
    void addMemory(size_type value);
    void transMemory();
    void clearVector();
    void printVector();
};
};  // namespace s21

#endif  // SRC_S21_VECTOR_H_
