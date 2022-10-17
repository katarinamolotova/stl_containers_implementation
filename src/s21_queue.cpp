#include "s21_queue.h"

using namespace s21;

template<class value_type>
Queue<value_type>::Queue() {
    this->size_ = 0;
    this->first_ = nullptr;
    this->last_ = nullptr;
}

template <class value_type>
Queue<value_type>::Queue(std::initializer_list<value_type> const &items) : Queue() {
    for (auto it = items.begin(); it != items.end(); it++)
        this->push(*it);
}

template<class value_type>
Queue<value_type>::Queue(const Queue &q) : Queue() {
    this->copy(q);
}

template<class value_type>
Queue<value_type>::Queue(Queue &&q) : Queue(q) {
    q.clear();
}

template<class value_type>
Queue<value_type>::~Queue() {
    this->clear();
}

template<class value_type>
Queue<value_type>& Queue<value_type>::operator=(Queue<value_type> &q) {
    this->copy(q);
    return *this;
}

template<class value_type>
typename Queue<value_type>::const_reference Queue<value_type>::front() {
    if (this->first_ == nullptr)
        throw std::out_of_range("Error: Queue is empty");
    return this->first_->data;
}

template<class value_type>
typename Queue<value_type>::const_reference Queue<value_type>::back() {
    if (this->last_ == nullptr)
        throw std::out_of_range("Error: Queue is empty");
    return this->last_->data;
}

template<class value_type>
bool Queue<value_type>::empty() {
    return (this->size_ == 0);
}

template<class value_type>
typename Queue<value_type>::size_type Queue<value_type>::size() {
    return this->size_;
}

template<class value_type>
void Queue<value_type>::push(const_reference value) {
    Node* node = new Node(value, nullptr);
    if (this->first_ == nullptr)
        this->first_ = node;
    if (this->last_ != nullptr)
        this->last_->next = node;
    this->last_ = node;
    this->size_++;
}

template<class value_type>
void Queue<value_type>::pop() {
    if (this->first_ != nullptr) {
        Node* node = this->first_->next;
        delete this->first_;
        this->first_ = node;
        this->size_--;
        if (size_ < 2)
            this->last_ = node;
    }
}

template<class value_type>
void Queue<value_type>::swap(Queue& other) {
    Queue<value_type> new_queue(other);
    other = *this;
    *this = new_queue;
}

template<class value_type>
void Queue<value_type>::clear() {
    size_type const_size = this->size_;
    for (size_type i = 0; i < const_size; i++)
        this->pop();
}

template<class value_type>
void Queue<value_type>::copy(const Queue &other) {
    this->clear();
    Node *node = other.first_;
    for (size_type i = 0; i < other.size_; i++) {
        this->push(node->data);
        node = node->next;
    }
}

template<class value_type>
template<class... Args>
void Queue<value_type>::emplace_back(Args&&... args) {
    return this->push(value_type(std::forward<Args>(args)...));
}
