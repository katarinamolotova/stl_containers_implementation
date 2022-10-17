#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include <initializer_list>
#include <stdexcept>

#define RED true
#define BLACK false

namespace s21 {
class Iterator;

template<class Key, class T>
class Map {
 private:
    class Iterator;
    class Node {
     public:
        Node *left, *right, *parent;
        std::pair<Key, T> data;
        bool color;
        Node(std::pair<Key, T> data = std::pair<Key, T>(), Node *left = nullptr,
                Node *right = nullptr, Node *parent = nullptr, bool color = BLACK) {
            this->data = data;
            this->left = left;
            this->right = right;
            this->parent = parent;
            this->color = color;
        }
    };
    Node* root_;
    Node* nil_;
    size_t size_;

 public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<key_type, mapped_type>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;

    class MapIterator;

    class MapConstIterator : public Iterator {
     public:
        MapConstIterator(Node* node) : Iterator(node) {}
        MapConstIterator(MapIterator iter) : MapConstIterator(iter.iter_) {}
        const_reference operator* () { return this->iter_->data; }
        const value_type* operator-> () { return &this->iter_->data; }
    };

    class MapIterator : public Iterator {
        friend class ListConstIterator;
     public:
        MapIterator(Node* node) : Iterator(node) {}
        reference operator* () { return this->iter_->data; }
        value_type* operator-> () { return &this->iter_->data; }
    };

    using iterator = MapIterator;
    using const_iterator = MapConstIterator;

 private:
    Node* find_node(const key_type& key, Node* root);
    Node* min_node(Node* root);
    Node* max_node(Node* root);
    void insert_tree_elem(Node* root, Node* elem);
    void insert_fixup_color(Node* elem);
    Node* insert_fixup_right_branch(Node* elem);
    Node* insert_fixup_left_branch(Node* elem);

    void copy(Map &m);

    void delete_tree_elem(Node* elem);
    Node* delete_fixup_color(Node* elem);

    void left_rotate(Node* root);
    void right_rotate(Node* root);
    void transplant(Node* delete_node, Node* new_node);

 public:
    Map();
    Map(std::initializer_list<value_type> const &items);
    Map(Map &m);
    Map(Map &&m);
    ~Map();
    Map &operator=(Map &m);

    mapped_type& at(const Key& key);
    mapped_type& operator[](const Key& key);

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    bool empty();
    size_type size();
    size_type max_size();

    void clear();
    std::pair<iterator, bool> insert(const value_type& value);
    std::pair<iterator, bool> insert(const Key& key, const T& obj);
    std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
    void erase(iterator pos);
    void swap(Map& other);
    void merge(Map& other);
    bool contains(const Key& key);

    template<class... Args>
    std::pair<iterator, bool> emplace(Args&&... args);
};

template<class Key, class T>
class Map<Key, T>::Iterator {
 protected:
    Node* iter_;

 private:
    Node* minimum(Node* root);
    Node* maximum(Node* root);
    Node* find_bigger_elem(Node* elem);
    Node* find_smaller_elem(Node* elem);

 public:
    Iterator(Node* node) : iter_(node) {}
    Node* operator++ () { return iter_ = find_bigger_elem(iter_); }
    Node* operator-- () { return iter_ = find_smaller_elem(iter_); }
    Node* operator++ (int) { return iter_ = find_bigger_elem(iter_); }
    Node* operator-- (int) { return iter_ = find_smaller_elem(iter_); }
    bool operator== (const Iterator& it) { return this->iter_ == it.iter_; }
    bool operator!= (const Iterator& it) { return this->iter_ != it.iter_; }
};
}  // namespace s21

#endif  //  SRC_S21_MAP_H_
