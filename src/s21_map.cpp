#include "s21_map.h"
#include "s21_rb_tree.cpp"

#define MAX_SIZE_MAP 230584300921369395

using namespace s21;

template<class key_type, class mapped_type>
Map<key_type, mapped_type>::Map() {
    this->root_ = nullptr;
    this->size_ = 0;
    this->nil_ = new Node();
}

template<class key_type, class mapped_type>
Map<key_type, mapped_type>::Map(std::initializer_list<value_type> const &items) : Map() {
    for (auto it = items.begin(); it != items.end(); it++)
        this->insert(*it);
}

template<class key_type, class mapped_type>
Map<key_type, mapped_type>::Map(Map &m) : Map() {
    this->copy(m);
}

template<class key_type, class mapped_type>
Map<key_type, mapped_type>::Map(Map &&m) : Map(m) {
    m.clear();
}

template<class key_type, class mapped_type>
Map<key_type, mapped_type>::~Map() {
    this->clear();
    delete nil_;
}

template<class key_type, class mapped_type>
Map<key_type, mapped_type>& Map<key_type, mapped_type>::operator=(Map &m) {
    this->copy(m);
    return *this;
}

template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::mapped_type&
Map<key_type, mapped_type>::at(const key_type& key) {
    if (!this->contains(key))
        throw std::out_of_range("Error: This key doesn't exist");
    return this->operator[](key);
}

template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::mapped_type&
Map<key_type, mapped_type>::operator[](const key_type& key) {
    if (!this->contains(key))
        this->insert(key, mapped_type());
    return this->find_node(key, this->root_)->data.second;
}
template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::iterator
Map<key_type, mapped_type>::begin() {
    return (!this->empty()) ? min_node(root_) : nil_;
}

template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::iterator
Map<key_type, mapped_type>::end() {
    return this->nil_;
}

template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::const_iterator
Map<key_type, mapped_type>::begin() const {
    return (!this->empty()) ? min_node(this->root_) : this->nil_;
}

template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::const_iterator
Map<key_type, mapped_type>::end() const {
    return this->nil_;
}

template<class key_type, class mapped_type>
bool Map<key_type, mapped_type>::empty() {
    return (this->size_ == 0);
}

template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::size_type
Map<key_type, mapped_type>::size() {
    return this->size_;
}

template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::size_type
Map<key_type, mapped_type>::max_size() {
    return MAX_SIZE_MAP;
}

template<class key_type, class mapped_type>
void Map<key_type, mapped_type>::copy(Map& other) {
    this->clear();
    for (auto it = other.begin(); it != other.end(); it++)
        this->insert(*it);
}

template<class key_type, class mapped_type>
void Map<key_type, mapped_type>::clear() {
    size_type start_size = this->size_;
    for (size_type i = 0; i < start_size; i++)
        this->erase(this->begin());
}

template<class key_type, class mapped_type>
void Map<key_type, mapped_type>::swap(Map& other) {
    Map<key_type, mapped_type> new_map(other);
    other = *this;
    *this = new_map;
}

template<class key_type, class mapped_type>
void Map<key_type, mapped_type>::merge(Map& other) {
    for (auto it = other.begin(); it != other.end(); it++)
        this->insert(*it);
    other.clear();
}

template<class key_type, class mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::insert(const value_type& value) {
    size_type start_size = this->size_;
    Node* elem = new Node(value, nil_, nil_, nullptr, (root_ == nullptr) ? BLACK : RED);
    if (this->empty())
        root_ = elem;
    else
        insert_tree_elem(root_, elem);
    size_++;
    (start_size == this->size_) ? delete elem : insert_fixup_color(elem);
    nil_->parent = max_node(root_);
    nil_->data.first = this->size_;
    return std::make_pair(find_node(value.first, this->root_), start_size < this->size_);
}

template<class key_type, class mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::insert(const key_type& key, const mapped_type& obj) {
    return this->insert(std::make_pair(key, obj));
}

template<class key_type, class mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::insert_or_assign(const key_type& key, const mapped_type& obj) {
    size_type start_size = this->size_;
    if (contains(key))
        this->at(key) = obj;
    else
        this->insert(std::make_pair(key, obj));
    return std::make_pair(find_node(key, this->root_), start_size < this->size_);
}

template<class key_type, class mapped_type>
bool Map<key_type, mapped_type>::contains(const key_type& key) {
    return (find_node(key, root_) != nil_);
}

template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::Node* Map<key_type, mapped_type>::min_node(Node* root) {
    if (root->left != nil_)
        root = min_node(root->left);
    return root;
}

template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::Node* Map<key_type, mapped_type>::max_node(Node* root) {
    if (root->right != nil_)
        root = max_node(root->right);
    return root;
}

template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::Node* Map<key_type, mapped_type>::
find_node(const key_type& key, Node* root) {
    Node* res = nil_;
    if (root_ != nullptr && root != nullptr) {
        if (key < root->data.first)
            res = find_node(key, root->left);
        else if (key > root->data.first)
            res = find_node(key, root->right);
        else
            res = root;
    }
    return res;
}

template<class key_type, class mapped_type>
void Map<key_type, mapped_type>::erase(iterator pos) {
    if (pos == this->end())
        throw std::out_of_range("Error: out of range");
    Node* elem = find_node(pos->first, this->root_);
    delete_tree_elem(elem);
    delete elem;
    this->size_--;
}

template<class key_type, class mapped_type>
template<class... Args>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
        Map<key_type, mapped_type>::emplace(Args&&... args) {
    return this->insert(value_type(std::forward<Args>(args)...));
}

//  Iterator
template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::Node*
Map<key_type, mapped_type>::Iterator::minimum(Node *root) {
    if (root->left->left != nullptr)
        root = minimum(root->left);
    return root;
}

template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::Node*
Map<key_type, mapped_type>::Iterator::maximum(Node* root) {
    if (root->right->right != nullptr)
        root = maximum(root->right);
    return root;
}

template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::Node*
Map<key_type, mapped_type>::Iterator::find_bigger_elem(Node* elem) {
    if (elem->right == nullptr) {
        elem = elem->parent;
    } else if (elem->right->right != nullptr) {
        elem = minimum(elem->right);
    } else {
        Node* start_node = elem;
        Node* p = elem->parent;
        while (p != nullptr && elem == p->right) {
            elem = p;
            p = p->parent;
        }
        elem = (p == nullptr) ? start_node->right : p;
    }
    return elem;
}

template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::Node*
Map<key_type, mapped_type>::Iterator::find_smaller_elem(Node* elem) {
    if (elem->left == nullptr) {
        elem = elem->parent;
    } else if (elem->left->left != nullptr) {
        elem = maximum(elem->left);
    } else {
        Node* start_node = elem;
        Node* p = elem->parent;
        while (p != nullptr && elem == p->left) {
            elem = p;
            p = p->parent;
        }
        elem = (p == nullptr) ? start_node->left : p;
    }
    return elem;
}
