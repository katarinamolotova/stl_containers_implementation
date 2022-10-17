#ifndef SRC_S21_QUEUE_H_
#define SRC_S21_QUEUE_H_

#include <initializer_list>
#include <stdexcept>

namespace s21 {
template<class T>
class Queue {
 private:
    class Node {
     public:
        Node *next;
        T data;

        Node(T data = T(), Node *next = nullptr) {
            this->data = data;
            this->next = next;
        }
    };

    Node *first_, *last_;
    size_t size_;

    void clear();
    void copy(const Queue &other);

 public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

    Queue();
    Queue(std::initializer_list<value_type> const &items);
    Queue(const Queue &q);
    Queue(Queue &&q);
    ~Queue();
    Queue<value_type> &operator=(Queue &q);

    const_reference front();
    const_reference back();

    bool empty();
    size_type size();

    void push(const_reference value);
    void pop();
    void swap(Queue& other);

    template<class... Args>
    void emplace_back(Args&&... args);
};
}  // namespace s21

#endif  //  SRC_S21_QUEUE_H_
