#include "s21_map.h"

using namespace s21;

template<class key_type, class mapped_type>
void Map<key_type, mapped_type>::insert_fixup_color(Node* elem) {
    while (elem != root_ && elem->parent->color == RED) {
        if (elem->parent == elem->parent->parent->right)
            elem = insert_fixup_right_branch(elem);
        else
            elem = insert_fixup_left_branch(elem);
    }
    root_->color = BLACK;
}

template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::Node* Map<key_type, mapped_type>::insert_fixup_left_branch(Node* elem) {
    Node* uncle = elem->parent->parent->right;
    if (uncle->color == RED) {
        uncle->color = BLACK;
        elem->parent->color = BLACK;
        elem->parent->parent->color = RED;
        elem = elem->parent->parent;
    } else {
        if (elem == elem->parent->right) {
            elem = elem->parent;
            left_rotate(elem);
        }
        elem->parent->color = BLACK;
        elem->parent->parent->color = RED;
        right_rotate(elem->parent->parent);
    }
    return elem;
}

template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::Node* Map<key_type, mapped_type>::insert_fixup_right_branch(Node* elem) {
    Node* uncle = elem->parent->parent->left;
    if (uncle->color == RED) {
        uncle->color = BLACK;
        elem->parent->color = BLACK;
        elem->parent->parent->color = RED;
        elem = elem->parent->parent;
    } else {
        if (elem == elem->parent->left) {
            elem = elem->parent;
            right_rotate(elem);
        }
        elem->parent->color = BLACK;
        elem->parent->parent->color = RED;
        left_rotate(elem->parent->parent);
    }
    return elem;
}

template<class key_type, class mapped_type>
void Map<key_type, mapped_type>::left_rotate(Node* root) {
    Node* new_root = root->right;
    root->right = new_root->left;
    if (new_root->left != nil_)
        new_root->left->parent = root;
    new_root->parent = root->parent;
    if (root->parent == nullptr)
        root_ = new_root;
    else if (root == root->parent->left)
        root->parent->left = new_root;
    else
        root->parent->right = new_root;
    new_root->left = root;
    root->parent = new_root;
}

template<class key_type, class mapped_type>
void Map<key_type, mapped_type>::right_rotate(Node* root) {
    Node* new_root = root->left;
    root->left = new_root->right;
    if (new_root->right != nil_)
        new_root->right->parent = root;
    new_root->parent = root->parent;
    if (root->parent == nullptr)
        root_ = new_root;
    else if (root == root->parent->right)
        root->parent->right = new_root;
    else
        root->parent->left = new_root;
    new_root->right = root;
    root->parent = new_root;
}

template<class key_type, class mapped_type>
void Map<key_type, mapped_type>::insert_tree_elem(Node* root, Node* elem) {
    if (elem->data.first < root->data.first) {
        if (root->left == nil_) {
            root->left = elem;
            elem->parent = root;
        } else {
            insert_tree_elem(root->left, elem);
        }
    } else if (elem->data.first > root->data.first) {
        if (root->right == nil_) {
            root->right = elem;
            elem->parent = root;
        } else {
            insert_tree_elem(root->right, elem);
        }
    } else {
        this->size_--;
    }
}

template<class key_type, class mapped_type>
void Map<key_type, mapped_type>::transplant(Node* delete_node, Node* new_node) {
    if (delete_node->parent == nullptr)
        root_ = new_node;
    else if (delete_node == delete_node->parent->left)
        delete_node->parent->left = new_node;
    else
        delete_node->parent->right = new_node;
    new_node->parent = delete_node->parent;
}

template<class key_type, class mapped_type>
void Map<key_type, mapped_type>::delete_tree_elem(Node *elem) {
    Node* child;
    Node* sup_node = elem;
    bool start_color = sup_node->color;
    if (elem->left == nil_) {
        child = elem->right;
        transplant(elem, elem->right);
    } else if (elem->right == nil_) {
        child = elem->left;
        transplant(elem, elem->left);
    } else {
        sup_node = min_node(elem->right);
        start_color = sup_node->color;
        child = sup_node->right;
        if (sup_node->parent == elem) {
            child->parent = sup_node;
        } else {
            transplant(sup_node, sup_node->right);
            sup_node->right = elem->right;
            sup_node->right->parent = sup_node;
        }
        transplant(elem, sup_node);
        sup_node->left = elem->left;
        sup_node->left->parent = sup_node;
        sup_node->color = elem->color;
    }
    if (start_color == BLACK) {
        while (child != root_ && child->color == BLACK)
            child = delete_fixup_color(child);
        child->color = BLACK;
    }
}

template<class key_type, class mapped_type>
typename Map<key_type, mapped_type>::Node* Map<key_type, mapped_type>::delete_fixup_color(Node* elem) {
    Node* brother  = elem->parent->right;
    if (brother->color == RED) {
        brother->color = BLACK;
        elem->parent->color = RED;
        left_rotate(elem->parent);
        brother = elem->parent->right;
    }
    if (brother->left->color == BLACK && brother->right->color == BLACK) {
        brother->color = RED;
        elem = elem->parent;
    } else {
        if (brother->right->color == BLACK) {
            brother->left->color = BLACK;
            brother->color = RED;
            right_rotate(brother);
            brother = elem->parent->right;
        }
        brother->color = elem->parent->color;
        elem->parent->color = BLACK;
        brother->right->color = BLACK;
        left_rotate(elem->parent);
        elem = root_;
    }
    return elem;
}
