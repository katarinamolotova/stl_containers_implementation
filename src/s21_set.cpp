#include "s21_set.h"
#define MAX_SIZE_SET 230584300921369395
using namespace s21;

template<class T>
Set<T>::Set() {
    this->root_ = nullptr;
    this->size_ = 0;
    this->nil_ = new Node();
    this->nil_->data = 0;
    this->nil_->size = 0;
}

template<class T>
Set<T>::Set(Set &other) : Set() {
    this->copy(other);
}

template<class T>
Set<T>::Set(Set &&other) : Set() {
    this->merge(other);
}

template<class T>
Set<T>::Set(std::initializer_list<value_type> const &items) : Set() {
    for (auto it = items.begin(); it != items.end(); it++)
        this->insert(*it);
}

template<class T>
Set<T>::~Set() {
    this->clear();
    delete nil_;
}

template<class T>
Set<T>& Set<T>::operator=(Set &other) {
    this->clear();
    this->copy(other);
    return *this;
}

template<class T>
Set<T> Set<T>::operator=(Set &&other) {
    this->clear();
    this->merge(other);
    return *this;
}

template<class T>
void Set<T>::swap(Set& other) {
    Set<T> tmp(std::move(other));
    other = *this;
    this->clear();
    *this = tmp;
}

template<class T>
void Set<T>::transpNode_(Node * delNode, Node * insNode) {
    if (delNode->back == nullptr) {
        this->root_ = insNode;
    } else if (delNode == delNode->back->left) {
        delNode->back->left = insNode;
    } else {
        delNode->back->right = insNode;
        if (insNode != nullptr)
            insNode->back = delNode->back;
    }
    delete delNode;
}

template<class T>
typename Set<T>::Node* Set<T>::findMinNode_(Node* root) {
    return root->left != nil_ ? findMinNode_(root->left) : root;
}

template<class T>
void Set<T>::erase(iterator pos) {
    if (pos.iterator_->left == nil_) {
        transpNode_(pos.iterator_, pos.iterator_->right);
    } else if (pos.iterator_->right == nil_) {
        transpNode_(pos.iterator_, pos.iterator_->left);
    } else {
        Node * tmp = findMinNode_(pos.iterator_->right);
            if (tmp->back != pos.iterator_) {
                transpNode_(tmp, tmp->right);
                tmp->right = pos.iterator_->right;
                tmp->right->back = tmp;
            }
            transpNode_(pos.iterator_, tmp);
            tmp->left = pos.iterator_->left;
            tmp->left->back = tmp;
    }
}

template<class T>
void Set<T>::change(Node * rootThis, Node * rootBack) {
    if (rootBack->left == rootThis->back)
        rootBack->left = nil_;
    if (rootBack->right == rootThis->back)
        rootBack->right = nil_;
}

template<class T>
std::pair<typename Set<T>::iterator, bool> Set<T>::insert(const value_type& value) {
    size_t startSize = this->size_;
    Node* elem = new Node(value, nil_, nil_);
    if (root_ == nullptr)
        root_ = elem;
    else
        insert_tree_elem(root_, elem);
    this->nil_->data++;
    size_++;
    return std::make_pair(this->find(value), startSize < this->size_ );
}

template<class T>
void Set<T>::insert_tree_elem(Node* root, Node* elem) {
    elem->back = root;
    if (elem->data < root->data) {
        if (root->left == nil_) {
            root->left = elem;
            elem->back = root;
        } else {
            insert_tree_elem(root->left, elem);
        }
    } else if (elem->data > root->data) {
        if (root->right == nil_) {
            root->right = elem;
            elem->back = root;
            if (elem->data > nil_->size)
                nil_->back = elem;
        } else {
            insert_tree_elem(root->right, elem);
        }
    } else {
        delete elem;
        this->nil_->data--;
        size_--;
    }
}

template<class T>
void Set<T>::printTree() {
    if (root_ != nullptr) {
        print_tree_elem(this->root_);
        std::cout << std::endl;
    }
}

template<class T>
void Set<T>::print_tree_elem(Node * root) {
    if (root->left != nil_)
        print_tree_elem(root->left);
    std::cout << root->data;
    // std::cout << " адресс " << root << std::endl;
    if (root->right != nil_)
        print_tree_elem(root->right);
}

template<class T>
void Set<T>::merge(Set& other) {
    this->copy(other);
    other.clear();
}

template<class T>
void Set<T>::copy(Set& other) {
    if (other.root_ != nullptr)
        mergeTree(this->root_, other.root_, other.nil_);
}

template<class T>
void Set<T>::mergeTree(Node * rootThis, Node * rootOther, Node * nil_) {
    if (rootOther->left != nil_)
        mergeTree(rootThis, rootOther->left, nil_);
    if (rootOther->right != nil_)
        mergeTree(rootThis, rootOther->right, nil_);
    this->insert(rootOther->data);
}

template<class T>
bool Set<T>::empty() {
    return this->size_ == 0;
}

template<class T>
typename Set<T>::size_type Set<T>::size() {
    return this->size_;
}

template<class T>
typename Set<T>::size_type Set<T>::max_size() {
    return MAX_SIZE_SET;
}

template<class T>
typename Set<T>::SetIterator Set<T>::find(const Key& key) {
    return (this->root_ != nullptr) ? findNode_(this->root_, key) : this->root_;
}

template<class T>
typename Set<T>::Node* Set<T>::findNode_(Node* root, const Key& key) {
    Node * tmp = root;
    if (root->data != key) {
        if (root->left != nullptr)
            tmp = findNode_(root->left, key);
        if (root->right != nullptr && tmp->data != key)
            tmp = findNode_(root->right, key);
    }
    return tmp;
}

template<class T>
bool Set<T>::contains(const Key& key) {
    return (this->root_ != nullptr) ? containsFind(this->root_, key) : false;
}

template<class T>
bool Set<T>::containsFind(Node * root, Key key) {
    bool flag = 0;
    if (root->data != key && flag != 1) {
        if (root->left != nil_)
            flag = containsFind(root->left, key);
        if (root->right != nil_ && flag != 1)
            flag = containsFind(root->right, key);
    } else {
        flag = 1;
    }
    return flag;
}

// // Iterator's
template<class T>
typename Set<T>::SetIterator Set<T>::begin() {
    return (this->size_ == 0) ? this->nil_ : this->run(this->root_, 0);
}

template<class T>
typename Set<T>::SetIterator Set<T>::end() {
    return this->nil_;
}

template<class T>
typename Set<T>::SetIterator Set<T>::run(Node * root, size_type direction) {
    iterator tmp = root;
    if (root != nullptr) {
        if (direction == 0) {
            if (root->left != nil_)
               tmp = this->run(root->left, direction);
        } else if (direction == 1) {
            if (root->right != nil_)
                tmp = this->run(root->right, direction);
        }
    }
    return tmp;
}

template<class T>
void Set<T>::clear() {
    if (root_ != nullptr) {
        cleaner(this->root_);
    }
    size_ = 0;
    root_ = nullptr;
}

template<class T>
void Set<T>::cleaner(Node * root) {
    if (root->left != nil_)
        cleaner(root->left);
    if (root->right != nil_)
        cleaner(root->right);
    delete root;
    root->left = nullptr;
    root->back = nullptr;
    root->right = nullptr;
    root->size = 0;
    root->data = 0;
}

template<class T>
typename Set<T>::Node* Set<T>::Iterator::min_node(Node* root) {
    return root->left->left != nullptr ? min_node(root->left) : root;
}

template<class T>
typename Set<T>::Node* Set<T>::Iterator::find_bigger_elem(Node* elem) {
    if (elem->right == nullptr) {
        elem = elem->back;
    } else if (elem->right->right != nullptr) {
        elem = min_node(elem->right);
    } else {
        Node* start_node = elem;
        Node* back = elem->back;
        while (back != nullptr && elem == back->right) {
            elem = back;
            back = back->back;
        }
        elem = (back == nullptr) ? start_node->right : back;
    }
    return elem;
}

template<class T>
typename Set<T>::Node* Set<T>::Iterator::max_node(Node* root) {
    return root->right->right != nullptr ? max_node(root->right) : root;
}

template<class T>
typename Set<T>::Node* Set<T>::Iterator::find_smaller_elem(Node* elem) {
    if (elem->left == nullptr) {
        elem = elem->back;
    } else if (elem->left->left != nullptr) {
        elem = max_node(elem->left);
    } else {
        Node* start_node = elem;
        Node* back = elem->back;
        while (back != nullptr && elem == back->left) {
            elem = back;
            back = back->back;
        }
        elem = (back == nullptr) ? start_node->left : back;
    }
    return elem;
}

template<class T>
template<typename ...Args>
std::pair<typename Set<T>::iterator, bool>
        Set<T>::emplace(Args&&... args) {
    return this->insert(value_type(std::forward<Args>(args)...));
}
