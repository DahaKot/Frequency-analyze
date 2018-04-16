//
// Created by daha-kot on 16.04.18.
//

#ifndef HASH_LIST_H
#define HASH_LIST_H

#include <iostream>
#include <cstring>

const int max_wlen = 100;
const int max_alen = 100;
const int two = 2147483648;
const size_t POISON = 9999999999;

int Comparate(const void *l1, const void*l2);

class Node {
public:
    Node();
    ~Node();
    Node(const Node& that) = delete;
    Node(const char *data, Node *next);
    Node(Node&& that) noexcept;
    Node& operator=(const Node& that) = delete;

    inline const char * Get_data() {return data_;};
    inline size_t Get_freq() {return freq_;};
    inline void inc_freq()        {freq_++;};

    Node *next_;

private:
    size_t freq_;
    const char * data_;
};

class List {
public:
    List();
    ~List();
    List(const List& that) = delete;
    List& operator=(const List& that) = delete;

    inline size_t Get_len() {return len_;};
    inline Node * Get_head() {return head_;};

    void Add_Last(const char *elem);
    Node *Find_elem(const char *data);
    bool Ok();
    void Dump();
    size_t Find_most_freq();

private:
    size_t len_;
    Node *head_;
    Node *tail_;
};

#endif //HASH_LIST_H
