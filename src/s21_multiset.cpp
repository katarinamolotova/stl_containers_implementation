#include "s21_multiset.h"

using namespace s21;

template<class T>
MultiSet<T>::MultiSet(std::initializer_list<value_type> const &items)   {
    for (auto it = items.begin(); it != items.end(); it++)
        this->insert(*it);
}

template<class T>
MultiSet<T>::MultiSet(MultiSet &other) : MultiSet() {
    this->copy(other);
}

template<class T>
MultiSet<T>::MultiSet(MultiSet &&other) : MultiSet() {
    this->merge(other);
}

template<class T>
MultiSet<T>::~MultiSet() {
    this->clear();
    if (this->root_ != nullptr)
        delete this->nil_;
}

template<class T>
MultiSet<T>& MultiSet<T>::operator=(MultiSet &other) {
    this->merge(other);
    return *this;
}

template<class T>
void MultiSet<T>::insert_tree_elem(Node* root, Node* elem) {
    elem->back = root;
    if (elem->data <= root->data) {
        if (root->left == this->nil_) {
            root->left = elem;
            elem->back = root;
        } else {
            insert_tree_elem(root->left, elem);
        }
    } else if (elem->data > root->data) {
        if (root->right == this->nil_) {
            root->right = elem;
            elem->back = root;
            if (elem->data >= this->nil_->size)
                this->nil_->back = elem;
        } else {
            insert_tree_elem(root->right, elem);
        }
    } else {
        delete elem;
        this->nil_->data--;
        this->size_--;
    }
}

template<class T>
typename MultiSet<T>::iterator MultiSet<T>::lower_bound(const Key& key) {
    iterator tmp = this->find(key);
    iterator tmp1 = this->end();
    if (tmp == this->begin())
        return tmp;
    while (*tmp == key)
        tmp--;
    return (tmp == tmp1 ) ? tmp : tmp++;
}

template<class T>
typename MultiSet<T>::iterator MultiSet<T>::upper_bound(const Key& key) {
    iterator tmp = this->find(key);
    iterator tmp1 = this->end();
    return (tmp == tmp1 ) ? tmp : tmp++;
}

template<class T>
std::pair<typename MultiSet<T>::iterator, typename MultiSet<T>::iterator>
MultiSet<T>::equal_range(const Key& key) {
    return std::make_pair(this->lower_bound(key), this->upper_bound(key));
}
