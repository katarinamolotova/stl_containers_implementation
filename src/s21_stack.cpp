#include "s21_stack.h"

using namespace s21;

template<class value_type>
Stack<value_type>::Stack() {
    this->size_ = 0;
    this->top_ = nullptr;
}

template <class value_type>
Stack<value_type>::Stack(std::initializer_list<value_type> const &items) : Stack() {
    for (auto it = items.begin(); it != items.end(); it++)
        this->push(*it);
}

template<class value_type>
Stack<value_type>::Stack(const Stack &s) : Stack() {
    this->copy(s);
}

template<class value_type>
Stack<value_type>::Stack(Stack &&s) : Stack(s) {
    s.clear();
}

template<class value_type>
Stack<value_type>::~Stack() {
    this->clear();
}

template<class value_type>
Stack<value_type>& Stack<value_type>::operator=(Stack<value_type> &s) {
    this->copy(s);
    return *this;
}

template<class value_type>
typename Stack<value_type>::const_reference Stack<value_type>::top() {
    if (this->top_ == nullptr)
        throw std::out_of_range("Error: Stack is empty");
    return this->top_->data;
}

template<class value_type>
bool Stack<value_type>::empty() {
    return (this->size_ == 0);
}

template<class value_type>
typename Stack<value_type>::size_type Stack<value_type>::size() {
    return this->size_;
}

template<class value_type>
void Stack<value_type>::push(const_reference value) {
    Node* node = new Node(value, this->top_);
    this->top_ = node;
    this->size_++;
}

template<class value_type>
void Stack<value_type>::pop() {
    if (this->top_ != nullptr) {
        Node* node = this->top_->back;
        delete this->top_;
        this->top_ = node;
        this->size_--;
    }
}

template<class value_type>
void Stack<value_type>::swap(Stack& other) {
    Stack<value_type> new_stack(other);
    other = *this;
    *this = new_stack;
}

template<class value_type>
void Stack<value_type>::clear() {
    size_type const_size = this->size_;
    for (size_type i = 0; i < const_size; i++)
        this->pop();
}

template<class value_type>
void Stack<value_type>::copy(const Stack &other) {
    this->clear();
    Stack<value_type> temp_stack;
    temp_stack.half_copy(other);
    this->half_copy(temp_stack);
}

template<class value_type>
void Stack<value_type>::half_copy(const Stack &other) {
    Node* temp_node = other.top_;
    for (size_type i = 0; i < other.size_; i++) {
        this->push(temp_node->data);
        temp_node = temp_node->back;
    }
}

template<class value_type>
template<class... Args>
void Stack<value_type>::emplace_front(Args&&... args) {
    return this->push(value_type(std::forward<Args>(args)...));
}
