#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include <cstddef>
#include <iostream>
#include <initializer_list>


namespace s21 {
class Iterator;

template <class T>
class Set {
 public:
    class Iterator;
    class Node {
     public:
        Node *left, *right, *back;
        T data, size;

        explicit Node(T data = T(), Node *left = nullptr, Node *right = nullptr, Node *back = nullptr) {
            this->data = data;
            this->left = left;
            this->right = right;
            this->back = back;
        }
    };

    Node *root_;
    Node *nil_;
    size_t size_;

 public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;
    using Key = value_type;

    class SetIterator;

    class SetConstIterator : public Iterator {
     public:
        SetConstIterator(Node* node) : Iterator(node) {}
        SetConstIterator(SetIterator iterator) : SetConstIterator(iterator.iterator_) {}
        const_reference operator* () { return this->iterator_->data; }
        const value_type* operator-> () { return &this->iterator_->data; }
    };

    class SetIterator : public Iterator {
     public:
        SetIterator(Node* node) : Iterator(node) {}
        reference operator* () { return this->iterator_->data; }
        value_type* operator-> () { return &this->iterator_->data; }
    };

 public:
    using iterator = SetIterator;
    using const_iterator = SetConstIterator;

 public:
    Set();
    Set(std::initializer_list<value_type> const &items);
    Set(const Set &other);
    Set(Set &other);
    Set(Set &&other);
    Set operator=(Set &&other);

    ~Set();

    iterator begin();
    iterator end();
    Set &operator=(Set &other);

    bool empty();
    size_type size();
    size_type max_size();

    template<typename ...Args>
    std::pair<iterator, bool> emplace(Args&&... args);

    void printTree();
    void clear();
    std::pair<iterator, bool> insert(const value_type& value);
    void erase(iterator pos);
    void swap(Set& other);
    void merge(Set& other);
    iterator find(const Key& key);
    bool contains(const Key& key);
    iterator run(Node * root, size_type direction);

 protected:
    virtual void insert_tree_elem(Node* root, Node* elem);
    void copy(Set& other);
    void cleaner(Node * root);
    bool containsFind(Node * root, Key key);
    void mergeTree(Node * rootThis, Node * rootOther, Node * nil_);
    void print_tree_elem(Node * root);
    void change(Node * rootThis, Node * rootBack);
    void eraseTreeElem(iterator pos);
    void transpNode_(Node * delNode, Node * insNode);
    Node* findMinNode_(Node* root);
    Node* findNode_(Node* root, const Key& key);
    int findMaxSize(Node* root);
};

template <class T>
class Set<T>::Iterator {
    friend class Set;
 protected:
    Node* iterator_;

 public:
    Iterator(Node* node) : iterator_(node) {}
    reference operator* () { return this->iterator_->data;}
    Node* operator++ () { return iterator_ = (iterator_ != nullptr)
        ? find_bigger_elem(iterator_) : iterator_->back; }
    Node* operator-- () { return iterator_ = (iterator_ != nullptr)
        ? find_smaller_elem(iterator_) : iterator_->back; }
    Node* operator++ (int) { return iterator_ = (iterator_ != nullptr)
        ? find_bigger_elem(iterator_) : iterator_->back; }
    Node* operator-- (int) { return iterator_ = (iterator_ != nullptr)
        ? find_smaller_elem(iterator_) : iterator_->back; }
    bool operator== (Iterator& it) { return this->iterator_ == it.iterator_; }
    bool operator== (const Iterator& it) { return this->iterator_ == it.iterator_; }
    bool operator!= (const Iterator& it) { return this->iterator_ != it.iterator_; }

    Node* min_node(Node* root);
    Node* find_bigger_elem(Node* elem);
    Node* max_node(Node* root);
    Node* find_smaller_elem(Node* elem);
};
};  // namespace s21

#endif  // SRC_S21_SET_H_
