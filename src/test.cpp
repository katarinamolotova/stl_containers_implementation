#include <gtest/gtest.h>
#include "s21_containers.h"
#include "s21_containersplus.h"
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <vector>
#include <map>
#include <array>
#include <set>

using namespace s21;
using namespace std;

class TestList : public testing::Test {
 protected:
    List<int>* my_list_int;
    List<int>* my_list_empty;
    List<char>* my_list_char;

    list<int>* another_int;
    list<int>* another_empty;
    list<char>* another_char;

    void SetUp() {
        my_list_empty = new List<int>();
        my_list_int = new List<int>(initializer_list<int> {0, 5, 2, -6, 3, 7, 10, 3});
        my_list_char = new List<char>(initializer_list<char> {'a', '1', '-', 'q', '0'});

        another_empty = new list<int>();
        another_int = new list<int>(initializer_list<int> {0, 5, 2, -6, 3, 7, 10, 3});
        another_char = new list<char>(initializer_list<char> {'a', '1', '-', 'q', '0'});
    }

    void TearDown() {
        delete my_list_int;
        delete my_list_empty;
        delete my_list_char;

        delete another_int;
        delete another_empty;
        delete another_char;
    }
};

TEST_F(TestList, constructor_default) {
    EXPECT_EQ(another_empty->size(), my_list_empty->size());
    EXPECT_EQ(another_empty->empty(), my_list_empty->empty());
    EXPECT_EQ(another_empty->back(), my_list_empty->back());
    EXPECT_EQ(another_empty->front(), my_list_empty->front());
    EXPECT_EQ(*another_empty->begin(), *my_list_empty->begin());
    EXPECT_EQ(*another_empty->end(), *my_list_empty->end());
}

TEST_F(TestList, constructor_size) {
    list<int> another(5);
    List<int> my_list(5);
    EXPECT_EQ(another.size(), my_list.size());
    EXPECT_EQ(another.empty(), my_list.empty());
    EXPECT_EQ(another.back(), my_list.back());
    EXPECT_EQ(another.front(), my_list.front());
    EXPECT_EQ(*another.begin(), *my_list.begin());
    EXPECT_EQ(*another.end(), *my_list.end());
    auto it_a = another.begin();
    for (auto it = my_list.begin(); it != my_list.end(); it++, it_a++) {
        EXPECT_EQ(*it, *it_a);
    }
}

TEST_F(TestList, constructor_intialization) {
    EXPECT_EQ(another_int->size(), my_list_int->size());
    EXPECT_EQ(another_int->empty(), my_list_int->empty());
    EXPECT_EQ(another_int->back(), my_list_int->back());
    EXPECT_EQ(another_int->front(), my_list_int->front());
    auto it_a = another_int->begin();
    for (auto it = my_list_int->begin(); it != my_list_int->end(); it++, it_a++) {
        EXPECT_EQ(*it, *it_a);
    }
}

TEST_F(TestList, constructor_copy) {
    list<char> another_copy(*another_char);
    List<char> my_list_copy(*my_list_char);
    EXPECT_EQ(another_copy.size(), my_list_copy.size());
    EXPECT_EQ(my_list_copy.size(), my_list_char->size());
    for (auto it = my_list_char->begin(), it_c = my_list_copy.begin();
        it != my_list_char->end(); it++, it_c++) {
        EXPECT_EQ(*it, *it_c);
    }
}

TEST_F(TestList, constructor_move) {
    list<char> another_move(move(*another_char));
    List<char> my_list_move(move(*my_list_char));
    EXPECT_EQ(my_list_char->empty(), another_char->empty());
    EXPECT_EQ(another_move.size(), my_list_move.size());
    auto it_a = another_move.begin();
    for (auto it = my_list_move.begin(); it != my_list_move.end(); it++, it_a++) {
        EXPECT_EQ(*it, *it_a);
    }
}

TEST_F(TestList, operator_equal) {
    list<char> another_eq = { '4' };
    another_eq = *another_char;
    List<char> my_list_eq = { '4' };
    my_list_eq = *my_list_char;
    EXPECT_EQ(another_eq.size(), my_list_eq.size());
    EXPECT_EQ(my_list_eq.size(), my_list_char->size());
    for (auto it = my_list_char->begin(), it_e = my_list_eq.begin();
        it != my_list_char->end(); it++, it_e++)
        EXPECT_EQ(*it, *it_e);
}

TEST_F(TestList, operator_equal_empty) {
    *another_int = *another_empty;
    *my_list_int = *my_list_empty;
    EXPECT_EQ(another_int->size(), my_list_int->size());
    EXPECT_EQ(another_int->empty(), my_list_int->empty());
}

TEST_F(TestList, push_back1) {
    list<int> another(3);
    List<int> my_list(3);
    another.push_back(10);
    my_list.push_back(10);
    EXPECT_EQ(another.back(), my_list.back());
    EXPECT_EQ(another.size(), my_list.size());
}

TEST_F(TestList, push_back2) {
    another_empty->push_back(10);
    my_list_empty->push_back(10);
    EXPECT_EQ(another_empty->back(), my_list_empty->back());
    EXPECT_EQ(another_empty->front(), my_list_empty->front());
    EXPECT_EQ(*another_empty->begin(), *my_list_empty->begin());
    EXPECT_EQ(*another_empty->end(), *my_list_empty->end());
    EXPECT_EQ(another_empty->size(), my_list_empty->size());
}

TEST_F(TestList, push_front1) {
    list<int> another(3);
    List<int> my_list(3);
    another.push_front(10);
    my_list.push_front(10);
    EXPECT_EQ(another.front(), my_list.front());
    EXPECT_EQ(another.size(), my_list.size());
}

TEST_F(TestList, push_front2) {
    another_empty->push_front(10);
    my_list_empty->push_front(10);
    EXPECT_EQ(another_empty->back(), my_list_empty->back());
    EXPECT_EQ(another_empty->front(), my_list_empty->front());
    EXPECT_EQ(*another_empty->begin(), *my_list_empty->begin());
    EXPECT_EQ(*another_empty->end(), *my_list_empty->end());
    EXPECT_EQ(another_empty->size(), my_list_empty->size());
}

TEST_F(TestList, pop_front) {
    another_int->pop_front();
    my_list_int->pop_front();
    EXPECT_EQ(another_int->front(), my_list_int->front());
    EXPECT_EQ(another_int->size(), my_list_int->size());
}

TEST_F(TestList, pop_front_exception) {
    EXPECT_THROW(my_list_empty->pop_front(), out_of_range);
}

TEST_F(TestList, pop_back) {
    another_int->pop_back();
    my_list_int->pop_back();
    EXPECT_EQ(another_int->back(), my_list_int->back());
    EXPECT_EQ(another_int->size(), my_list_int->size());
}

TEST_F(TestList, pop_back_exception) {
    EXPECT_THROW(my_list_empty->pop_back(), out_of_range);
}

TEST_F(TestList, max_size) {
    EXPECT_EQ(another_empty->max_size(), my_list_empty->max_size());
}

TEST_F(TestList, clear) {
    another_int->clear();
    my_list_int->clear();
    EXPECT_EQ(another_int->size(), my_list_int->size());
    EXPECT_EQ(another_int->empty(), my_list_int->empty());
    EXPECT_EQ(another_int->back(), my_list_int->back());
    EXPECT_EQ(another_int->front(), my_list_int->front());
    EXPECT_EQ(*another_int->begin(), *my_list_int->begin());
    EXPECT_EQ(*another_int->end(), *my_list_int->end());
}

TEST_F(TestList, erase) {
    another_int->erase(++another_int->begin());
    my_list_int->erase(++my_list_int->begin());
    auto it_a = another_int->begin();
    for (auto it = my_list_int->begin(); it != my_list_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestList, erase_end) {
    EXPECT_THROW(my_list_int->erase(my_list_int->end()), out_of_range);
}

TEST_F(TestList, insert) {
    another_int->insert(++another_int->begin(), -1);
    my_list_int->insert(++my_list_int->begin(), -1);
    auto it_a = another_int->begin();
    for (auto it = my_list_int->begin(); it != my_list_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestList, insert_end) {
    another_int->insert(another_int->end(), -1);
    my_list_int->insert(my_list_int->end(), -1);
    auto it_a = another_int->begin();
    for (auto it = my_list_int->begin(); it != my_list_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestList, insert_empty_end) {
    another_empty->insert(another_empty->end(), -1);
    my_list_empty->insert(my_list_empty->end(), -1);
    auto it_a = another_empty->begin();
    for (auto it = my_list_empty->begin(); it != my_list_empty->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestList, swap) {
    list<char> another_swap = { '5', ';', ' ', 'a', '=' };
    List<char> my_swap = { '5', ';', ' ', 'a', '=' };
    my_list_char->swap(my_swap);
    another_char->swap(another_swap);
    auto it_a = another_char->begin();
    for (auto it = my_list_char->begin(); it != my_list_char->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
    auto it_s = another_swap.begin();
    for (auto it = my_swap.begin(); it != my_swap.end(); it++, it_s++)
        EXPECT_EQ(*it, *it_s);
}

TEST_F(TestList, merge) {
    list<int> another_merge = { 1, 3, -6, 0, 4 };
    List<int> my_merge = { 1, 3, -6, 0, 4 };
    my_list_int->merge(my_merge);
    another_int->merge(another_merge);
    auto it_a = another_int->begin();
    for (auto it = my_list_int->begin(); it != my_list_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
    EXPECT_EQ(another_merge.empty(), my_merge.empty());
    EXPECT_EQ(another_merge.size(), my_merge.size());
}

TEST_F(TestList, splice) {
    list<int> another_splice = { 1, 2, 3, 4, 5 };
    List<int> my_splice = { 1, 2, 3, 4, 5 };
    my_list_int->splice(++my_list_int->begin(), my_splice);
    another_int->splice(++another_int->begin(), another_splice);
    auto it_a = another_int->begin();
    for (auto it = my_list_int->begin(); it != my_list_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
    EXPECT_EQ(another_splice.empty(), my_splice.empty());
    EXPECT_EQ(another_int->size(), my_list_int->size());
}

TEST_F(TestList, reverse) {
    my_list_int->reverse();
    another_int->reverse();
    auto it_a = another_int->begin();
    for (auto it = my_list_int->begin(); it != my_list_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestList, reverse_empty) {
    my_list_empty->reverse();
    another_empty->reverse();
    EXPECT_EQ(my_list_empty->size(), another_empty->size());
    EXPECT_EQ(my_list_empty->empty(), another_empty->empty());
}

TEST_F(TestList, unique) {
    my_list_int->unique();
    another_int->unique();
    auto it_a = another_int->begin();
    for (auto it = my_list_int->begin(); it != my_list_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestList, unique2) {
    list<int> another_unique = { 2, 2, 2, 2, 2 };
    List<int> my_unique = { 2, 2, 2, 2, 2 };
    another_unique.unique();
    my_unique.unique();
    auto it_a = another_unique.begin();
    for (auto it = my_unique.begin(); it != my_unique.end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
    EXPECT_EQ(another_unique.size(), my_unique.size());
}

TEST_F(TestList, unique_empty) {
    my_list_empty->unique();
    another_empty->unique();
    EXPECT_EQ(my_list_empty->size(), another_empty->size());
    EXPECT_EQ(my_list_empty->empty(), another_empty->empty());
}

TEST_F(TestList, sort_int) {
    another_int->sort();
    my_list_int->sort();
    auto it_a = another_int->begin();
    for (auto it = my_list_int->begin(); it != my_list_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestList, sort_char) {
    another_char->sort();
    my_list_char->sort();
    auto it_a = another_char->begin();
    for (auto it = my_list_char->begin(); it != my_list_char->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestList, sort_empty) {
    another_empty->sort();
    my_list_empty->sort();
    EXPECT_EQ(my_list_empty->size(), another_empty->size());
    EXPECT_EQ(my_list_empty->empty(), another_empty->empty());
}

TEST_F(TestList, emplace_zero_elem) {
    another_int->emplace(++another_int->begin());
    my_list_int->emplace(++my_list_int->begin());
    auto it_a = another_int->begin();
    for (auto it = my_list_int->begin(); it != my_list_int->end(); it++, it_a++)
    EXPECT_EQ(*it, *it_a);
}

TEST_F(TestList, emplace_one_elem) {
    another_int->emplace(++another_int->begin(), 19);
    my_list_int->emplace(++my_list_int->begin(), 19);
    auto it_a = another_int->begin();
    for (auto it = my_list_int->begin(); it != my_list_int->end(); it++, it_a++)
    EXPECT_EQ(*it, *it_a);
}

TEST_F(TestList, emplace_back_zero_elem) {
    another_int->emplace_back();
    my_list_int->emplace_back();
    EXPECT_EQ(my_list_int->back(), another_int->back());
}

TEST_F(TestList, emplace_back_one_elem) {
    another_int->emplace_back(19);
    my_list_int->emplace_back(19);
    EXPECT_EQ(my_list_int->back(), another_int->back());
}

TEST_F(TestList, emplace_front_zero_elem) {
    another_int->emplace_front();
    my_list_int->emplace_front();
    EXPECT_EQ(my_list_int->front(), another_int->front());
}

TEST_F(TestList, emplace_front_one_elem) {
    another_int->emplace_front(19);
    my_list_int->emplace_front(19);
    EXPECT_EQ(my_list_int->front(), another_int->front());
}

class TestStack : public testing::Test {
 protected:
    Stack<int>* my_stack_int;
    Stack<int>* my_stack_empty;
    Stack<char>* my_stack_char;

    stack<int>* another_int;
    stack<int>* another_empty;
    stack<char>* another_char;

    void SetUp() {
        my_stack_empty = new Stack<int>();
        my_stack_int = new Stack<int>(initializer_list<int> {0, 1, 2, 3, 4, 5, 6});
        my_stack_char = new Stack<char>(initializer_list<char> {'a', 'b', 'c', 'd', 'e'});

        another_empty = new stack<int>();
        another_int = new stack<int>(initializer_list<int> {0, 1, 2, 3, 4, 5, 6});
        another_char = new stack<char>(initializer_list<char> {'a', 'b', 'c', 'd', 'e'});
    }

    void TearDown() {
        delete my_stack_int;
        delete my_stack_empty;
        delete my_stack_char;

        delete another_int;
        delete another_empty;
        delete another_char;
    }
};

TEST_F(TestStack, constructor_empty) {
    EXPECT_EQ(my_stack_empty->size(), another_empty->size());
    EXPECT_EQ(my_stack_empty->empty(), another_empty->empty());
}

TEST_F(TestStack, constructor_initialization) {
    EXPECT_EQ(my_stack_int->size(), another_int->size());
    EXPECT_EQ(my_stack_int->empty(), another_int->empty());
    EXPECT_EQ(my_stack_int->top(), another_int->top());
}

TEST_F(TestStack, constructor_copy) {
    Stack<char> my_stack_copy(*my_stack_char);
    stack<char> another_copy(*another_char);
    EXPECT_EQ(my_stack_copy.top(), my_stack_char->top());
    EXPECT_EQ(my_stack_copy.top(), another_copy.top());
}

TEST_F(TestStack, constructor_move) {
    Stack<char> my_stack_move(move(*my_stack_char));
    stack<char> another_move(move(*another_char));
    EXPECT_EQ(my_stack_char->empty(), another_char->empty());
    EXPECT_EQ(my_stack_move.top(), another_move.top());
    EXPECT_EQ(my_stack_move.size(), another_move.size());
}

TEST_F(TestStack, operator_eq) {
    stack<char> another_eq;
    another_eq = *another_char;
    Stack<char> my_stack_eq;
    my_stack_eq = *my_stack_char;
    EXPECT_EQ(another_eq.size(), my_stack_eq.size());
    EXPECT_EQ(my_stack_eq.size(), my_stack_char->size());
    EXPECT_EQ(my_stack_eq.top(), my_stack_char->top());
    EXPECT_EQ(my_stack_eq.top(), another_eq.top());
}

TEST_F(TestStack, operator_eq_empty) {
    *my_stack_int = *my_stack_empty;
    *another_int = *another_empty;
    EXPECT_EQ(my_stack_int->empty(), another_int->empty());
}

TEST_F(TestStack, top) {
    EXPECT_EQ(my_stack_char->top(), another_char->top());
    EXPECT_EQ(my_stack_int->top(), another_int->top());
}

TEST_F(TestStack, top_empty) {
    EXPECT_THROW(my_stack_empty->top(), out_of_range);
}

TEST_F(TestStack, push) {
    my_stack_int->push(-5);
    another_int->push(-5);
    EXPECT_EQ(my_stack_int->top(), another_int->top());
    EXPECT_EQ(my_stack_int->size(), another_int->size());
}

TEST_F(TestStack, pop) {
    my_stack_int->pop();
    another_int->pop();
    EXPECT_EQ(my_stack_int->top(), another_int->top());
    EXPECT_EQ(my_stack_int->size(), another_int->size());
}

TEST_F(TestStack, swap) {
    stack<char> another_swap(initializer_list<char> { '1', '2', '3', '4', '5' });
    Stack<char> my_stack_swap = { '1', '2', '3', '4', '5' };
    my_stack_char->swap(my_stack_swap);
    another_char->swap(another_swap);
    EXPECT_EQ(my_stack_swap.top(), another_swap.top());
    EXPECT_EQ(my_stack_char->top(), another_char->top());
}

TEST_F(TestStack, swap_empty) {
    my_stack_empty->swap(*my_stack_int);
    another_empty->swap(*another_int);
    EXPECT_EQ(another_int->empty(), my_stack_int->empty());
    EXPECT_EQ(my_stack_empty->top(), another_empty->top());
}

TEST_F(TestStack, emplace_front_zero_elem) {
    my_stack_int->emplace_front();
    EXPECT_EQ(my_stack_int->top(), 0);
}

TEST_F(TestStack, emplace_front_one_elem) {
    my_stack_int->emplace_front(10);
    EXPECT_EQ(my_stack_int->top(), 10);
}

class TestQueue : public testing::Test {
 protected:
    Queue<int>* my_queue_int;
    Queue<int>* my_queue_empty;
    Queue<char>* my_queue_char;

    queue<int>* another_int;
    queue<int>* another_empty;
    queue<char>* another_char;

    void SetUp() {
        my_queue_empty = new Queue<int>();
        my_queue_int = new Queue<int>(initializer_list<int> {0, 1, 2, 3, 4, 5, 6});
        my_queue_char = new Queue<char>(initializer_list<char> {'a', 'b', 'c', 'd', 'e'});

        another_empty = new queue<int>();
        another_int = new queue<int>(initializer_list<int> {0, 1, 2, 3, 4, 5, 6});
        another_char = new queue<char>(initializer_list<char> {'a', 'b', 'c', 'd', 'e'});
    }

    void TearDown() {
        delete my_queue_int;
        delete my_queue_empty;
        delete my_queue_char;

        delete another_int;
        delete another_empty;
        delete another_char;
    }
};

TEST_F(TestQueue, constructor_empty) {
    EXPECT_EQ(my_queue_empty->size(), another_empty->size());
    EXPECT_EQ(my_queue_empty->empty(), another_empty->empty());
}

TEST_F(TestQueue, constructor_initialization) {
    EXPECT_EQ(my_queue_int->size(), another_int->size());
    EXPECT_EQ(my_queue_int->empty(), another_int->empty());
    EXPECT_EQ(my_queue_int->front(), another_int->front());
    EXPECT_EQ(my_queue_int->back(), another_int->back());
}

TEST_F(TestQueue, constructor_copy) {
    Queue<char> my_queue_copy(*my_queue_char);
    EXPECT_EQ(my_queue_copy.front(), my_queue_char->front());
    EXPECT_EQ(my_queue_copy.back(), my_queue_char->back());
    EXPECT_EQ(my_queue_copy.size(), my_queue_char->size());
}

TEST_F(TestQueue, constructor_move) {
    Queue<char> my_queue_move(move(*my_queue_char));
    queue<char> another_move(move(*another_char));
    EXPECT_EQ(my_queue_char->empty(), another_char->empty());
    EXPECT_EQ(my_queue_move.front(), another_move.front());
    EXPECT_EQ(my_queue_move.back(), another_move.back());
    EXPECT_EQ(my_queue_move.size(), another_move.size());
}

TEST_F(TestQueue, operator_eq) {
    Queue<char> my_queue_eq;
    my_queue_eq = *my_queue_char;
    EXPECT_EQ(my_queue_eq.size(), my_queue_char->size());
    EXPECT_EQ(my_queue_eq.back(), my_queue_char->back());
    EXPECT_EQ(my_queue_eq.front(), my_queue_char->front());
}

TEST_F(TestQueue, operator_eq_empty) {
    *my_queue_int = *my_queue_empty;
    EXPECT_EQ(my_queue_int->empty(), my_queue_empty->empty());
}

TEST_F(TestQueue, front) {
    EXPECT_EQ(my_queue_int->front(), another_int->front());
}

TEST_F(TestQueue, front_empty) {
    EXPECT_THROW(my_queue_empty->front(), out_of_range);
}

TEST_F(TestQueue, back) {
    EXPECT_EQ(my_queue_int->back(), another_int->back());
}

TEST_F(TestQueue, back_empty) {
    EXPECT_THROW(my_queue_empty->back(), out_of_range);
}

TEST_F(TestQueue, push) {
    my_queue_int->push(-100);
    another_int->push(-100);
    EXPECT_EQ(my_queue_int->back(), another_int->back());
    EXPECT_EQ(my_queue_int->front(), another_int->front());
    EXPECT_EQ(my_queue_int->size(), another_int->size());
}

TEST_F(TestQueue, pop) {
    my_queue_int->pop();
    another_int->pop();
    EXPECT_EQ(my_queue_int->back(), another_int->back());
    EXPECT_EQ(my_queue_int->front(), another_int->front());
    EXPECT_EQ(my_queue_int->size(), another_int->size());
}

TEST_F(TestQueue, swap) {
    queue<char> another_swap(initializer_list<char> { '1', '2', '3', '4', '5' });
    Queue<char> my_queue_swap = { '1', '2', '3', '4', '5' };
    my_queue_char->swap(my_queue_swap);
    another_char->swap(another_swap);
    EXPECT_EQ(my_queue_swap.back(), another_swap.back());
    EXPECT_EQ(my_queue_swap.front(), another_swap.front());
    EXPECT_EQ(my_queue_swap.size(), another_swap.size());
    EXPECT_EQ(my_queue_char->back(), another_char->back());
    EXPECT_EQ(my_queue_char->front(), another_char->front());
    EXPECT_EQ(my_queue_char->size(), another_char->size());
}

TEST_F(TestQueue, swap_empty) {
    my_queue_empty->swap(*my_queue_int);
    another_empty->swap(*another_int);
    EXPECT_EQ(my_queue_int->empty(), another_int->empty());
    EXPECT_EQ(my_queue_empty->back(), another_empty->back());
    EXPECT_EQ(my_queue_empty->front(), another_empty->front());
    EXPECT_EQ(my_queue_empty->size(), another_empty->size());
}


TEST_F(TestQueue, emplace_back_zero_elem) {
    my_queue_int->emplace_back();
    EXPECT_EQ(my_queue_int->back(), 0);
}

TEST_F(TestQueue, emplace_back_one_elem) {
    my_queue_int->emplace_back(19);
    EXPECT_EQ(my_queue_int->back(), 19);
}

class TestMap : public testing::Test {
 protected:
    Map<int, int>* my_map_int;
    Map<int, int>* my_map_empty;
    Map<char, int>* my_map_char;

    map<int, int>* another_int;
    map<int, int>* another_empty;
    map<char, int>* another_char;

    void SetUp() {
        my_map_empty = new Map<int, int>();
        my_map_int = new Map<int, int>(initializer_list<pair<int, int>> {
            make_pair(2, 5), make_pair(-6, 4), make_pair(8, 1), make_pair(5, -3),
            make_pair(0, 2)});
        my_map_char = new Map<char, int>(initializer_list<pair<char, int>> {
            make_pair('a', 5), make_pair('w', 4), make_pair('3', 1), make_pair('l', -3),
            make_pair(';', 2)});

        another_empty = new map<int, int>();
        another_int = new map<int, int>(initializer_list<pair<const int, int>> {
            make_pair(2, 5), make_pair(-6, 4), make_pair(8, 1), make_pair(5, -3),
            make_pair(0, 2)});
        another_char = new map<char, int>(initializer_list<pair<const char, int>> {
            make_pair('a', 5), make_pair('w', 4), make_pair('3', 1), make_pair('l', -3),
            make_pair(';', 2)});
    }

    void TearDown() {
        delete my_map_int;
        delete my_map_empty;
        delete my_map_char;

        delete another_int;
        delete another_empty;
        delete another_char;
    }
};

TEST_F(TestMap, constructor_empty) {
    EXPECT_EQ(my_map_empty->size(), another_empty->size());
    EXPECT_EQ(my_map_empty->empty(), another_empty->empty());
}

TEST_F(TestMap, constructor_initialization) {
    EXPECT_EQ(my_map_int->size(), another_int->size());
    EXPECT_EQ(my_map_int->empty(), another_int->empty());
    auto it_a = another_int->begin();
    for (auto it = my_map_int->begin(); it != my_map_int->end(); it++, it_a++) {
        EXPECT_EQ(it->first, it_a->first);
    }
}

TEST_F(TestMap, constructor_copy) {
    map<char, int> another_copy(*another_char);
    Map<char, int> my_map_copy(*my_map_char);
    EXPECT_EQ(my_map_copy.size(), another_copy.size());
    EXPECT_EQ(my_map_copy.size(), my_map_char->size());
    for (auto it = my_map_char->begin(), it_c = my_map_copy.begin();
        it != my_map_char->end(); it++, it_c++)
        EXPECT_EQ(it->first, it_c->first);
}

TEST_F(TestMap, constructor_move) {
    map<char, int> another_move(move(*another_char));
    Map<char, int> my_map_move(move(*my_map_char));
    EXPECT_EQ(my_map_char->empty(), another_char->empty());
    EXPECT_EQ(my_map_move.size(), another_move.size());
    auto it_a = another_move.begin();
    for (auto it = my_map_move.begin(); it != my_map_move.end(); it++, it_a++)
        EXPECT_EQ(it->first, it_a->first);
}

TEST_F(TestMap, operator_eq) {
    *another_empty = *another_int;
    *my_map_empty = *my_map_int;
    EXPECT_EQ(my_map_empty->size(), another_empty->size());
    EXPECT_EQ(my_map_empty->size(), my_map_int->size());
    for (auto it = my_map_int->begin(), it_e = my_map_empty->begin();
        it != my_map_int->end(); it++, it_e++)
        EXPECT_EQ(it->first, it_e->first);
}

TEST_F(TestMap, operator_eq_empty) {
    *another_int = *another_empty;
    *my_map_int = *my_map_empty;
    EXPECT_EQ(my_map_int->empty(), another_int->empty());
}

TEST_F(TestMap, operator_brackets_contains) {
    int another = another_int->operator[](0);
    int my = my_map_int->operator[](0);
    EXPECT_EQ(my, another);
}

TEST_F(TestMap, operator_brackets_non_contains) {
    int another = another_int->operator[](-11);
    int my = my_map_int->operator[](-11);
    EXPECT_EQ(my, another);
}

TEST_F(TestMap, operator_brackets_contains_input) {
    another_int->operator[](0) = 10;
    my_map_int->operator[](0) = 10;
    int another = another_int->operator[](0);
    int my = my_map_int->operator[](0);
    EXPECT_EQ(my, another);
}

TEST_F(TestMap, at) {
    EXPECT_EQ(my_map_int->at(0), another_int->at(0));
}

TEST_F(TestMap, at_non_contains) {
    EXPECT_THROW(my_map_int->at(-10), out_of_range);
}

TEST_F(TestMap, max_size) {
    EXPECT_EQ(my_map_int->max_size(), another_int->max_size());
}

TEST_F(TestMap, clear) {
    my_map_int->clear();
    another_int->clear();
    EXPECT_EQ(my_map_int->empty(), another_int->empty());
}

TEST_F(TestMap, clear_empty) {
    my_map_empty->clear();
    another_empty->clear();
    EXPECT_EQ(my_map_empty->empty(), another_empty->empty());
}

TEST_F(TestMap, insert_pair_true) {
    pair<Map<char, int>::MapIterator, bool> my = my_map_char->insert(make_pair('>', 10));
    pair<map<const char, int>::iterator, bool> another = another_char->insert(make_pair('>', 10));
    EXPECT_EQ(my.first->first, another.first->first);
    EXPECT_EQ(my.first->second, another.first->second);
    EXPECT_EQ(my.second, another.second);
}

TEST_F(TestMap, insert_pair_false) {
    pair<Map<char, int>::MapIterator, bool> my = my_map_char->insert(make_pair('3', 10));
    pair<map<const char, int>::iterator, bool> another = another_char->insert(make_pair('3', 10));
    EXPECT_EQ(my.first->first, another.first->first);
    EXPECT_EQ(my.first->second, another.first->second);
    EXPECT_EQ(my.second, another.second);
}

TEST_F(TestMap, insert_key_and_elem) {
    pair<Map<char, int>::MapIterator, bool> my = my_map_char->insert('>', 10);
    EXPECT_EQ(my.first->first, '>');
    EXPECT_EQ(my.first->second, 10);
    EXPECT_EQ(my.second, true);
}

TEST_F(TestMap, insert_or_assign) {
    pair<Map<char, int>::MapIterator, bool> my = my_map_char->insert_or_assign('3', 10);
    EXPECT_EQ(my.first->first, '3');
    EXPECT_EQ(my.first->second, 10);
    EXPECT_EQ(my.second, false);
}

TEST_F(TestMap, erase) {
    another_int->erase(++another_int->begin());
    my_map_int->erase(++my_map_int->begin());
    auto it_a = another_int->begin();
    for (auto it = my_map_int->begin(); it != my_map_int->end(); it++, it_a++)
        EXPECT_EQ(it->first, it_a->first);
}

TEST_F(TestMap, erase_right_elem) {
    map<int, int> another_map = {make_pair(2, 5), make_pair(-6, 4), make_pair(8, 1),
            make_pair(5, -3), make_pair(0, 2), make_pair(10, 5),
            make_pair(-10, 4), make_pair(20, 1), make_pair(13, -3)};
    Map<int, int> my_map = {make_pair(2, 5), make_pair(-6, 4), make_pair(8, 1),
             make_pair(5, -3), make_pair(0, 2), make_pair(10, 5),
             make_pair(-10, 4), make_pair(20, 1), make_pair(13, -3)};
    auto another = another_map.begin();
    auto my = my_map.begin();
    for (int i = 0; i < 3; i++, --my, --another) {}
    another_map.erase(another);
    my_map.erase(my);
    auto it_a = another_map.begin();
    for (auto it = my_map.begin(); it != my_map.end(); it++, it_a++)
        EXPECT_EQ(it->first, it_a->first);
}

TEST_F(TestMap, erase_throw) {
    EXPECT_THROW(my_map_int->erase(my_map_int->end()), out_of_range);
}

TEST_F(TestMap, swap) {
    Map<int, int> my_swap = { make_pair(0, 1), make_pair(-2, 2), make_pair(5, 8) };
    map<int, int> another_swap = { make_pair(0, 1), make_pair(-2, 2), make_pair(5, 8) };
    my_map_int->swap(my_swap);
    another_int->swap(another_swap);
    auto it_a = another_int->begin();
    for (auto it = my_map_int->begin(); it != my_map_int->end(); it++, it_a++)
        EXPECT_EQ(it->first, it_a->first);
    auto it_s = another_swap.begin();
    for (auto it = my_swap.begin(); it != my_swap.end(); it++, it_s++)
        EXPECT_EQ(it->first, it_s->first);
}

TEST_F(TestMap, swap_empty) {
    my_map_empty->swap(*my_map_int);
    another_empty->swap(*another_int);
    auto it_a = another_empty->begin();
    for (auto it = my_map_empty->begin(); it != my_map_empty->end(); it++, it_a++)
        EXPECT_EQ(it->first, it_a->first);
}

TEST_F(TestMap, merge) {
    Map<int, int> my_merge = { make_pair(0, 1), make_pair(-2, 2), make_pair(5, 8) };
    Map<int, int> result = { make_pair(-2, 2), make_pair(2, 5), make_pair(-6, 4),
                            make_pair(8, 1), make_pair(5, -3),  make_pair(0, 2) };
    my_map_int->merge(my_merge);
    for (auto it = my_map_int->begin(), it_a = result.begin();
        it != my_map_int->end(); it++, it_a++)
        EXPECT_EQ(it->first, it_a->first);
    EXPECT_EQ(my_map_int->size(), result.size());
    EXPECT_EQ(my_merge.empty(), true);
}

TEST_F(TestMap, contains) {
    EXPECT_EQ(my_map_int->contains(0), true);
    EXPECT_EQ(my_map_int->contains(-10), false);
    EXPECT_EQ(my_map_empty->contains(-10), false);
}

class TestVector : public testing::Test {
 protected:
    Vector<int>* my_vector_int;
    Vector<int>* my_vector_empty;
    Vector<char>* my_vector_char;

    vector<int>* another_int;
    vector<int>* another_empty;
    vector<char>* another_char;

    void SetUp() {
        my_vector_empty = new Vector<int>();
        my_vector_int = new Vector<int>(initializer_list<int> {1, 2, 3, 4, 8, 7});
        my_vector_char = new Vector<char>(initializer_list<char> {'f', 'a', 'f', 'g', 'g'});

        another_empty = new vector<int>();
        another_int = new vector<int>(initializer_list<int> {1, 2, 3, 4, 8, 7});
        another_char = new vector<char>(initializer_list<char> {'f', 'a', 'f', 'g', 'g'});
    }

    void TearDown() {
        delete my_vector_int;
        delete my_vector_empty;
        delete my_vector_char;

        delete another_int;
        delete another_empty;
        delete another_char;
    }
};

TEST_F(TestVector, constructor_empty) {
    EXPECT_EQ(my_vector_empty->size(), another_empty->size());
    EXPECT_EQ(my_vector_empty->empty(), another_empty->empty());
}

TEST_F(TestVector, constructor_initialization) {
    EXPECT_EQ(my_vector_int->size(), another_int->size());
    EXPECT_EQ(my_vector_int->empty(), another_int->empty());
    auto it_a = another_int->begin();
    for (auto it = my_vector_int->begin(); it != my_vector_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestVector, constructor_copy) {
    vector<char> another_copy(*another_char);
    Vector<char> vector_copy(*my_vector_char);
    EXPECT_EQ(vector_copy.size(), another_copy.size());
    EXPECT_EQ(vector_copy.size(), my_vector_char->size());
    for (auto it = my_vector_char->begin(), it_c = vector_copy.begin();
        it != my_vector_char->end(); it++, it_c++)
        EXPECT_EQ(*it, *it_c);
}

TEST_F(TestVector, constructor_move) {
    vector<char> another_move(move(*another_char));
    Vector<char> vector_move(move(*my_vector_char));
    EXPECT_EQ(my_vector_char->empty(), another_char->empty());
    EXPECT_EQ(vector_move.size(), another_move.size());
    auto it_a = another_move.begin();
    for (auto it = vector_move.begin(); it != vector_move.end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestVector, insert) {
    auto my_iter = my_vector_int->begin();
    auto another_iter = another_int->begin();
    my_iter += 3;
    another_iter +=3;
    my_vector_int->insert(my_iter, 777);
    another_int->insert(another_iter, 777);
    auto it_a = another_int->begin();
    for (auto it = my_vector_int->begin(); it != my_vector_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestVector, operatorEquals) {
    Vector<char> vector_move = *my_vector_char;
    auto it_a = vector_move.begin();
    for (auto it = my_vector_char->begin(); it != my_vector_char->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestVector, at) {
    for (size_t i = 0; i < another_int->size(); i++)
        EXPECT_EQ(my_vector_int->at(i), another_int->at(i));
}

TEST_F(TestVector, front) {
    EXPECT_EQ(my_vector_int->front(), another_int->front());
    EXPECT_EQ(my_vector_char->front(), another_char->front());
}

TEST_F(TestVector, back) {
    EXPECT_EQ(my_vector_int->back(), another_int->back());
    EXPECT_EQ(my_vector_char->back(), another_char->back());
}

TEST_F(TestVector, data) {
    EXPECT_EQ(*my_vector_int->data(), *another_int->data());
    EXPECT_EQ(*my_vector_char->data(), *another_char->data());
}

TEST_F(TestVector, begin) {
    EXPECT_EQ(*my_vector_int->begin(), *another_int->begin());
    EXPECT_EQ(*my_vector_char->begin(), *another_char->begin());
}

TEST_F(TestVector, empty) {
    EXPECT_EQ(my_vector_int->empty(), another_int->empty());
    EXPECT_EQ(my_vector_char->empty(), another_char->empty());
    EXPECT_EQ(my_vector_empty->empty(), another_empty->empty());
}

TEST_F(TestVector, size) {
    EXPECT_EQ(my_vector_int->size(), another_int->size());
    EXPECT_EQ(my_vector_char->size(), another_char->size());
    EXPECT_EQ(my_vector_empty->size(), another_empty->size());
}

TEST_F(TestVector, max_size) {
    EXPECT_EQ(my_vector_int->max_size(), another_int->max_size());
    EXPECT_EQ(my_vector_empty->max_size(), another_empty->max_size());
}

TEST_F(TestVector, reserve) {
    my_vector_int->reserve(15); another_int->reserve(15);
    my_vector_char->reserve(15); another_char->reserve(15);
    my_vector_empty->reserve(15); another_empty->reserve(15);
    EXPECT_EQ(my_vector_int->capacity(), another_int->capacity());
    EXPECT_EQ(my_vector_char->capacity(), another_char->capacity());
    EXPECT_EQ(my_vector_empty->capacity(), another_empty->capacity());
}

TEST_F(TestVector, capacity) {
    EXPECT_EQ(my_vector_int->capacity(), another_int->capacity());
    EXPECT_EQ(my_vector_char->capacity(), another_char->capacity());
    EXPECT_EQ(my_vector_empty->capacity(), another_empty->capacity());
}

TEST_F(TestVector, shrink_to_fit) {
    my_vector_char->pop_back(); another_char->pop_back();
    EXPECT_EQ(my_vector_char->capacity(), another_char->capacity());
    my_vector_char->shrink_to_fit(); another_char->shrink_to_fit();
    EXPECT_EQ(my_vector_char->capacity(), another_char->capacity());
}

TEST_F(TestVector, erase) {
    auto my_iter = my_vector_int->begin();
    auto another_iter = another_int->begin();
    my_iter += 3;
    another_iter +=3;

    my_vector_int->erase(my_iter);
    another_int->erase(another_iter);

    another_iter = another_int->begin();
    for (my_iter = my_vector_int->begin(); my_iter != my_vector_int->end(); my_iter++, another_iter++)
        EXPECT_EQ(*my_iter, *another_iter);
}

TEST_F(TestVector, insert_iterator) {
    auto my_iter = my_vector_int->begin();
    auto another_iter = another_int->begin();
    my_iter += 3;
    another_iter +=3;
    my_iter = my_vector_int->insert(my_iter, 10);
    another_iter = another_int->insert(another_iter, 10);

    another_iter = another_int->begin();
    for (my_iter = my_vector_int->begin(); my_iter != my_vector_int->end(); my_iter++, another_iter++)
        EXPECT_EQ(*my_iter, *another_iter);
}

TEST_F(TestVector, push_back) {
    my_vector_int->push_back(10);
    another_int->push_back(10);
    EXPECT_EQ(my_vector_int->size(), another_int->size());
    auto another_iter = another_int->begin();
    for (auto my_iter = my_vector_int->begin(); my_iter != my_vector_int->end(); my_iter++, another_iter++)
        EXPECT_EQ(*my_iter, *another_iter);
}

TEST_F(TestVector, pop_back) {
    my_vector_int->pop_back(); another_int->pop_back();
    EXPECT_EQ(my_vector_int->capacity(), another_int->capacity());
    my_vector_char->pop_back(); another_char->pop_back();
    EXPECT_EQ(my_vector_char->capacity(), another_char->capacity());
}

TEST_F(TestVector, swap) {
    Vector<int> my_vector_int_other = {12, 13, 14, 15};
    vector<int> another_int_other = {12, 13, 14, 15};
    my_vector_int->swap(my_vector_int_other);
    another_int->swap(another_int_other);
    auto another_iter = another_int->begin();
    for (auto my_iter = my_vector_int->begin(); my_iter != my_vector_int->end(); my_iter++, another_iter++)
        EXPECT_EQ(*my_iter, *another_iter);
}

class TestMultiset : public testing::Test {
 protected:
    MultiSet<int>* my_multiset_int;
    multiset<int>* another_int;

    void SetUp() {
        my_multiset_int = new MultiSet<int>(initializer_list<int> {2, -3, 0, 2, 1, 2, 2, 0, -4, 5, 2, 6});
        another_int = new multiset<int>(initializer_list<int> {2, -3, 0, 2, 1, 2, 2, 0, -4, 5, 2, 6});
    }

    void TearDown() {
        delete another_int;
    }
};

TEST_F(TestMultiset, insert) {
    my_multiset_int->insert(-19);
    another_int->insert(-19);
    auto it = my_multiset_int->begin();
    for (auto it_a = another_int->begin(); it_a != another_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestMultiset, equal_range) {
    pair<MultiSet<int>::iterator, MultiSet<int>::iterator> my =
        my_multiset_int->equal_range(2);
    pair<multiset<int>::iterator, multiset<int>::iterator> another =
        another_int->equal_range(2);
    EXPECT_EQ(*my.first, *another.first);
    EXPECT_EQ(*my.second, *another.second);
}

TEST_F(TestMultiset, lower_bound) {
    EXPECT_EQ(*my_multiset_int->lower_bound(0), *another_int->lower_bound(0));
}

TEST_F(TestMultiset, lower_bound_min) {
    EXPECT_EQ(*my_multiset_int->lower_bound(-4), *another_int->lower_bound(-4));
}

TEST_F(TestMultiset, upper_bound) {
    EXPECT_EQ(*my_multiset_int->upper_bound(0), *another_int->upper_bound(0));
}

TEST_F(TestMultiset, upper_bound_max) {
    EXPECT_EQ(*my_multiset_int->upper_bound(6), *another_int->upper_bound(6));
}

TEST_F(TestMultiset, equal_range_not_existing_key) {
    pair<MultiSet<int>::iterator, MultiSet<int>::iterator> my =
        my_multiset_int->equal_range(10);
    pair<multiset<int>::iterator, multiset<int>::iterator> another =
        another_int->equal_range(10);
    EXPECT_EQ(*my.first, *another.first);
    EXPECT_EQ(*my.second, *another.second);
}

TEST_F(TestMultiset, lower_bound_not_existing_key) {
    EXPECT_EQ(*my_multiset_int->lower_bound(10), *another_int->lower_bound(10));
}

TEST_F(TestMultiset, upper_bound_not_existing_key) {
    EXPECT_EQ(*my_multiset_int->upper_bound(10), *another_int->upper_bound(10));
}

TEST_F(TestMultiset, emplace_one_elem) {
    my_multiset_int->emplace(2);
    another_int->emplace(2);
    auto it = my_multiset_int->begin();
    for (auto it_a = another_int->begin(); it_a != another_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

class TestSet : public testing::Test {
 protected:
    Set<int>* my_set_int;
    Set<int>* my_set_empty;
    Set<char>* my_set_char;

    set<int>* another_int;
    set<int>* another_empty;
    set<char>* another_char;

    void SetUp() {
        my_set_empty = new Set<int>();
        my_set_int = new Set<int>(initializer_list<int> {1, 0, -2, 3, 6, -3, 4});
        my_set_char = new Set<char>(initializer_list<char> {'a', '2', 'c', 'D', '-'});

        another_empty = new set<int>();
        another_int = new set<int>(initializer_list<int> {1, 0, -2, 3, 6, -3, 4});
        another_char = new set<char>(initializer_list<char> {'a', '2', 'c', 'D', '-'});
    }

    void TearDown() {
        delete another_int;
        delete another_empty;
        delete another_char;
    }
};

TEST_F(TestSet, constructor_empty) {
    EXPECT_EQ(my_set_empty->size(), another_empty->size());
    EXPECT_EQ(my_set_empty->empty(), another_empty->empty());
}

TEST_F(TestSet, constructor_initialization) {
    EXPECT_EQ(my_set_int->size(), another_int->size());
    EXPECT_EQ(my_set_int->empty(), another_int->empty());
    auto it_a = another_int->begin();
    for (auto it = my_set_int->begin(); it != my_set_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestSet, constructor_copy) {
    set<char> another_copy(*another_char);
    Set<char> my_set_copy(*my_set_char);
    EXPECT_EQ(my_set_copy.size(), another_copy.size());
    EXPECT_EQ(my_set_copy.size(), my_set_char->size());
    for (auto it = my_set_char->begin(), it_c = my_set_copy.begin();
        it != my_set_char->end(); it++, it_c++)
        EXPECT_EQ(*it, *it_c);
}

TEST_F(TestSet, constructor_move) {
    set<char> another_move(move(*another_char));
    Set<char> my_set_move(move(*my_set_char));
    EXPECT_EQ(my_set_char->empty(), another_char->empty());
    EXPECT_EQ(my_set_move.size(), another_move.size());
    auto it_a = another_move.begin();
    for (auto it = my_set_move.begin(); it != my_set_move.end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestSet, operator_eq) {
    *another_empty = *another_int;
    *my_set_empty = *my_set_int;
    EXPECT_EQ(my_set_empty->size(), another_empty->size());
    EXPECT_EQ(my_set_empty->size(), my_set_int->size());
    for (auto it = my_set_int->begin(), it_e = my_set_empty->begin();
        it != my_set_int->end(); it++, it_e++)
        EXPECT_EQ(*it, *it_e);
}

TEST_F(TestSet, iterator_begin) {
    EXPECT_EQ(*my_set_int->begin(), *another_int->begin());
}

TEST_F(TestSet, iterator_end) {
    EXPECT_EQ(*my_set_int->end(), *another_int->end());
}

TEST_F(TestSet, iterator_begin_empty) {
    EXPECT_EQ(*my_set_empty->begin(), *another_empty->begin());
}

 TEST_F(TestSet, iterator_minus_minus_begin) {
     auto my = my_set_int->begin();
     auto another = another_int->begin();
    --my, --another;
     EXPECT_EQ(*my, *another);
 }

TEST_F(TestSet, max_size) {
    EXPECT_EQ(my_set_empty->max_size(), another_empty->max_size());
}

TEST_F(TestSet, clear) {
    another_int->clear();
    my_set_int->clear();
    EXPECT_EQ(my_set_int->size(), another_int->size());
    EXPECT_EQ(my_set_int->empty(), another_int->empty());
}

TEST_F(TestSet, clear_empty) {
    another_empty->clear();
    my_set_empty->clear();
    EXPECT_EQ(my_set_empty->empty(), another_empty->empty());
}

TEST_F(TestSet, insert) {
    pair<set<int>::iterator, bool> another = another_int->insert(10);
    pair<Set<int>::SetIterator, bool> my = my_set_int->insert(10);
    EXPECT_EQ(*my.first, *another.first);
    EXPECT_EQ(my.second, another.second);
}

TEST_F(TestSet, insert_existing_elem) {
    pair<set<int>::iterator, bool> another = another_int->insert(0);
    pair<Set<int>::SetIterator, bool> my = my_set_int->insert(0);
    EXPECT_EQ(*my.first, *another.first);
    EXPECT_EQ(my.second, another.second);
}

TEST_F(TestSet, swap) {
    Set<char> my_swap = { 'r', '0', '=', '+', 'q', 'F' };
    set<char> another_swap = { 'r', '0', '=', '+', 'q', 'F' };
    my_set_char->swap(my_swap);
    another_char->swap(another_swap);
    auto it_a = another_char->begin();
    for (auto it = my_set_char->begin(); it != my_set_char->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
    auto it_s = another_swap.begin();
    for (auto it = my_swap.begin(); it != my_swap.end(); it++, it_s++)
        EXPECT_EQ(*it, *it_s);
}

TEST_F(TestSet, swap_empty) {
    my_set_int->swap(*my_set_empty);
    another_int->swap(*another_empty);
    EXPECT_EQ(my_set_int->empty(), another_int->empty());
    auto it_a = another_empty->begin();
    for (auto it = my_set_empty->begin(); it != my_set_empty->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestSet, merge_without_repeat) {
    Set<int> my_merge = { 5, -9, 7, 2, 11, -8 };
    set<int> another_merge = { 5, -9, 7, 2, 11, -8 };
    my_set_int->merge(my_merge);
    another_int->merge(another_merge);
    EXPECT_EQ(my_merge.empty(), another_merge.empty());
    auto it_a = another_int->begin();
    for (auto it = my_set_int->begin(); it != my_set_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestSet, merge_with_repeat) {
    Set<int> my_merge = { 1, 0, 2, 3, 6, 3, -4 };
    set<int> another_merge = { 1, 0, 2, 3, 6, 3, -4 };
    my_set_int->merge(my_merge);
    another_int->merge(another_merge);
    auto it_a = another_int->begin();
    for (auto it = my_set_int->begin(); it != my_set_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestSet, merge_empty) {
    my_set_empty->merge(*my_set_int);
    another_empty->merge(*another_int);
    EXPECT_EQ(my_set_int->empty(), another_int->empty());
    auto it_a = another_empty->begin();
    for (auto it = my_set_empty->begin(); it != my_set_empty->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestSet, find_true) {
    EXPECT_EQ(*my_set_int->find(0), *another_int->find(0));
}

TEST_F(TestSet, find_false) {
    EXPECT_EQ(*my_set_int->find(10), *another_int->find(10));
}

TEST_F(TestSet, contains_true) {
    EXPECT_EQ(my_set_int->contains(0), 1);
}

TEST_F(TestSet, contains_false) {
    EXPECT_EQ(my_set_int->contains(10), 0);
}

TEST_F(TestSet, contains_empty) {
    EXPECT_EQ(my_set_empty->contains(10), 0);
}

TEST_F(TestSet, emplace_zero_elem) {
    pair<Set<int>::SetIterator, bool> my = my_set_int->emplace();
    pair<set<int>::iterator, bool> another = another_int->emplace();
    EXPECT_EQ(*my.first, *another.first);
    EXPECT_EQ(my.second, another.second);
}

TEST_F(TestSet, emplace_one_elem) {
    pair<Set<int>::SetIterator, bool> my = my_set_int->emplace(10);
    pair<set<int>::iterator, bool> another = another_int->emplace(10);
    EXPECT_EQ(*my.first, *another.first);
    EXPECT_EQ(my.second, another.second);
}

class TestArray : public testing::Test {
 protected:
    Array<int, 10>* my_array_int;
    Array<int, 10>* my_array_empty;
    Array<char, 10>* my_array_char;

    array<int, 10>* another_int;
    array<int, 10>* another_empty;
    array<char, 10>* another_char;

    void SetUp() {
        my_array_empty = new Array<int, 10>();
        my_array_int = new Array<int, 10>(initializer_list<int> {0, 1, 2, 3, 4, 5, 6});
        my_array_char = new Array<char, 10>(initializer_list<char> {'a', 'b', 'c', 'd', 'e'});

        another_empty = new array<int, 10>();
        another_int = new array<int, 10> ({0, 1, 2, 3, 4, 5, 6});
        another_char = new array<char, 10> ({'a', 'b', 'c', 'd', 'e'});
    }

    void TearDown() {
        delete my_array_int;
        delete my_array_empty;
        delete my_array_char;

        delete another_int;
        delete another_empty;
        delete another_char;
    }
};

TEST_F(TestArray, constructor_initialization) {
    auto it_a = my_array_int->begin();
    for (auto it = another_int->begin(); it != another_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestArray, constructor_copy) {
    Array<int, 10> copy_my_array_int(*my_array_int);
    array<int, 10> copy_another_it(*another_int);
    auto it_a = copy_my_array_int.begin();
    for (auto it = copy_another_it.begin(); it != copy_another_it.end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestArray, constructor_move) {
    Array<int, 10> move_my_array_int(move(*my_array_int));
    array<int, 10> move_another_it(move(*another_int));
    auto it_a = move_my_array_int.begin();
    for (auto it = move_another_it.begin(); it != move_another_it.end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestArray, operator_eq) {
    array<int, 10> another_int_swap = {3, 3, 3, 3, 3, 3, 3};
    Array<int, 10> my_array_int_swap = (initializer_list<int> {3, 3, 3, 3, 3, 3, 3});

    *my_array_int = my_array_int_swap;
    *another_int = another_int_swap;

    auto it_a = my_array_int->begin();
    for (auto it = another_int->begin(); it != another_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestArray, at) {
    EXPECT_EQ(my_array_int->at(3), another_int->at(3));
    EXPECT_EQ(my_array_char->at(3), another_char->at(3));
}

TEST_F(TestArray, front) {
    EXPECT_EQ(my_array_int->front(), another_int->front());
    EXPECT_EQ(my_array_char->front(), another_char->front());
}

TEST_F(TestArray, back) {
    EXPECT_EQ(my_array_int->back(), another_int->back());
    EXPECT_EQ(my_array_char->back(), another_char->back());
}

TEST_F(TestArray, data) {
    EXPECT_EQ(*my_array_int->data(), *another_int->data());
    EXPECT_EQ(*my_array_char->data(), *another_char->data());
}

TEST_F(TestArray, begin) {
    EXPECT_EQ(*(another_int->begin()), *(my_array_int->begin()));
    EXPECT_EQ(*(another_char->begin()), *(my_array_char->begin()));
}

TEST_F(TestArray, empty) {
    EXPECT_EQ(another_int->empty(), my_array_int->empty());
    EXPECT_EQ(another_empty->empty(), my_array_empty->empty());
    EXPECT_EQ(another_char->empty(), my_array_char->empty());
}

TEST_F(TestArray, size) {
    EXPECT_EQ(another_int->size(), my_array_int->size());
    EXPECT_EQ(another_empty->size(), my_array_empty->size());
    EXPECT_EQ(another_empty->size(), my_array_empty->size());
}

TEST_F(TestArray, max_size) {
    EXPECT_EQ(another_int->max_size(), my_array_int->max_size());
    EXPECT_EQ(another_empty->max_size(), my_array_empty->max_size());
    EXPECT_EQ(another_empty->max_size(), my_array_empty->max_size());
}

TEST_F(TestArray, swap) {
    array<int, 10> another_int_swap = {3, 3, 3, 3, 3, 3, 3};
    Array<int, 10> my_array_int_swap = (initializer_list<int> {3, 3, 3, 3, 3, 3, 3});

    another_int->swap(another_int_swap);
    my_array_int->swap(my_array_int_swap);

    auto it_a = my_array_int->begin();
    for (auto it = another_int->begin(); it != another_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

TEST_F(TestArray, fill) {
    my_array_int->fill(10);
    another_int->fill(10);
    auto it_a = my_array_int->begin();
    for (auto it = another_int->begin(); it != another_int->end(); it++, it_a++)
        EXPECT_EQ(*it, *it_a);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
