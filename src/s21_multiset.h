#ifndef SRC_S21_MULTISET_H_
#define SRC_S21_MULTISET_H_

#include "s21_set.h"

namespace s21 {
template <class T>
class MultiSet : public Set<T> {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;
    using Key = value_type;
    using Node = typename Set<T>::Node;


 public:
    using iterator = typename Set<T>::Set<T>::SetIterator;
    using const_iterator = typename Set<T>::SetConstIterator;

    void insert_tree_elem(Node* root, Node* elem) override;
    Node* min_node(Node* root);
    Node* find_bigger_elem(Node* elem);
    Node* max_node(Node* root);
    Node* find_smaller_elem(Node* elem);

    size_type count(const Key& key);  // напилить
    std::pair<iterator, iterator> equal_range(const Key& key);
    iterator lower_bound(const Key& key);
    iterator upper_bound(const Key& key);

    MultiSet() : Set<T>::Set() {}
    MultiSet(MultiSet &other);
    MultiSet(MultiSet &&other);
    MultiSet(std::initializer_list<value_type> const& items);
    MultiSet(const MultiSet &other);
    MultiSet &operator=(MultiSet &other);

    ~MultiSet();
};
}  // namespace s21

#endif  //  SRC_S21_MULTISET_H_
