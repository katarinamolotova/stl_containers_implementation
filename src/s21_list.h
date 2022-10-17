#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <initializer_list>
#include <stdexcept>

namespace s21 {
template<class T>
class List {
 private:
    class Node {
     public:
        Node *next, *back;
        T data;
        Node(T data = T(), Node *next = nullptr, Node *back = nullptr) {
            this->data = data;
            this->next = next;
            this->back = back;
        }
    };

    class Iterator {
     protected:
        Node* iterator_;

     public:
        Iterator(Node* node) : iterator_(node) {}
        Node* operator++ () { return iterator_ = (iterator_->next != nullptr) ? iterator_->next : iterator_; }
        Node* operator-- () { return iterator_ = (iterator_->back != nullptr) ? iterator_->back : iterator_; }
        Node* operator++ (int) { return iterator_ = (iterator_->next != nullptr)
        ? iterator_->next : iterator_; }
        Node* operator-- (int) { return iterator_ = (iterator_->back != nullptr)
        ? iterator_->back : iterator_; }
        bool operator== (const Iterator& it) { return this->iterator_ == it.iterator_; }
        bool operator!= (const Iterator& it) { return this->iterator_ != it.iterator_; }
        bool operator<= (const Iterator& it) { return this->iterator_ <= it.iterator_; }
        bool operator< (const Iterator& it) { return this->iterator_ < it.iterator_; }
        bool operator> (const Iterator& it) { return this->iterator_ > it.iterator_; }
    };

    Node *head_, *tail_, *iter_;
    size_t size_;

 public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

    class ListIterator;

    class ListConstIterator : public Iterator {
     public:
        ListConstIterator(Node* node) : Iterator(node) {}
        ListConstIterator(ListIterator iter) : ListConstIterator(iter.iterator_) {}
        const_reference operator* () { return this->iterator_->data; }
    };

    class ListIterator : public Iterator {
        friend class ListConstIterator;
     public:
        ListIterator(Node* node) : Iterator(node) {}
        reference operator* () { return this->iterator_->data; }
        value_type* operator-> () { return &this->iterator_->data; }
    };

    using iterator = ListIterator;
    using const_iterator = ListConstIterator;

 private:
    void copy(const List &other);
    void quick_sort(size_type first_node, size_type last_node);
    void set_iter(const_reference value);
    Node* get_node_by_pos(const_iterator pos);
    Node* move_to_index(size_type index);

 public:
    List();
    List(size_type n);
    List(std::initializer_list<value_type> const &items);
    List(const List &l);
    List(List &&l);
    ~List();

    List<T>& operator=(List &l);

    void push_back(const_reference value);
    void pop_back();
    void push_front(const_reference value);
    void pop_front();

    bool empty();
    size_type size();
    size_type max_size();

    const_reference front();
    const_reference back();

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    void clear();
    void erase(iterator pos);
    iterator insert(iterator pos, const_reference value);
    void swap(List& other);
    void merge(List& other);
    void splice(const_iterator pos, List& other);
    void reverse();
    void unique();
    void sort();

    template<class... Args>
    iterator emplace(const_iterator pos, Args&&... args);
    template<class... Args>
    void emplace_back(Args&&... args);
    template<class... Args>
    void emplace_front(Args&&... args);
};
}  // namespace s21

#endif  //  SRC_S21_LIST_H_

