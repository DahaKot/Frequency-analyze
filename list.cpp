//
// Created by daha-kot on 16.04.18.
//
#include "list.h"

Node::Node():
        freq_(1),
        data_(nullptr),
        next_(nullptr) {}

Node::Node(Node &&that) noexcept :
        freq_(that.freq_),
        data_(that.data_),
        next_(that.next_) {}

Node::Node(const char *data, Node *next):
        freq_(1),
        data_(data),
        next_(next) {}

Node::~Node() {
    if (this != nullptr) {
        delete next_;
        delete data_;
        next_ = nullptr;
        data_ = nullptr;
        freq_ = POISON;
    }
}

List::List():
        len_(0),
        head_(nullptr),
        tail_(nullptr) {}

List::~List() {
    if (this != nullptr) {
        if (head_ == tail_) {
            delete head_;
            head_ = nullptr;
            tail_ = nullptr;
        }
        else {
            delete head_;
            head_ = nullptr;
            delete tail_;
            tail_ = nullptr;
        }
        len_ = POISON;
    }
}

void List::Add_Last(const char *elem) {
    if (!Ok()) {
        Dump();
        return ;
    }

    char *new_data = new char[max_wlen];
    for (int i = 0; i < max_wlen; i++) {
        new_data[i] = elem[i];
    }
    Node *temp = new Node(new_data, nullptr);

    if (len_ == 0) {
        head_ = temp;
        tail_ = temp;
    }
    else {
        tail_->next_ = temp;
        tail_ = tail_->next_;
    }

    len_++;

    if (!Ok()) {
        Dump();
        return ;
    }
}

Node *List::Find_elem(const char *data) {
    if (!Ok()) {
        Dump();
        return nullptr;
    }

    if (len_ == 0) {
        return nullptr;
    }

    Node *node = head_;
    while(node != nullptr) {
        if (strcmp(data, node->Get_data()) == 0) {
            return node;
        }
        node = node->next_;
    }

    if (!Ok()) {
        Dump();
        return nullptr;
    }

    return node;
}

bool List::Ok() {
    if (this == nullptr || len_ < 0 ||
        (len_ != 0 && (head_ == nullptr || tail_ == nullptr))) {
        return true;
    }

    if (len_ == 1 && (head_ != tail_)) {
        return true;
    }

    struct Node *list_elem = head_;
    while (list_elem) {
        if (list_elem == head_ || list_elem == tail_ && list_elem->next_ != nullptr
            || (list_elem != head_ && list_elem != tail_
                && (list_elem->next_ == nullptr))){
            return true;
        }

        list_elem = list_elem->next_;
    }

    list_elem = head_;
    struct Node *point1 = list_elem;
    struct Node *point2 = list_elem;
    while (point1 && point2) {
        if (point1 == point2 && point1 != head_) {
            return true;
        }

        point1 = point1->next_;
        point2 = point2->next_;
        if (point2 == nullptr || point1 == nullptr) {
            break;
        }
        else {
            point2 = point2->next_;
        }
    }

    return true;
}

void List::Dump() {
    FILE *Dump_f = fopen("Dump.txt", "w");
    fprintf(Dump_f, "digraph List {\nhead [label = \"List's err on\\nList len = %d\"];\n", len_);

    struct Node *elem = head_;
    int i = 2;

    if (elem == nullptr) {
        fprintf(Dump_f, "}");
        fclose(Dump_f);

        system ("dot -Tpng Dump.txt -o Dump.png");
        system("Dump.png");
        return ;
    }

    fprintf(Dump_f, "node1 [shape=record, label=\"{<name> node1\\n%p|"
            "<data> data:\\ %s|<next> right\\n%p}}\"];\n", elem, elem->Get_data(), elem->next_);
    while (elem) {
        elem = elem->next_;
        if (elem == nullptr) {
            break;
        }
        fprintf(Dump_f, "node%d [shape=record, label=\"{<name> node%d\\n%p|"
                "<data> data:\\ %s|{<next> right\\n%p}}\"];\n", i, i, elem, elem->Get_data(), elem->next_);
        i++;
    }

    fprintf(Dump_f, "edge [color = deepskyblue];\n");
    i = 1;
    while (i < len_ && len_ != 1) {
        fprintf(Dump_f, "\"node%d\":next -> \"node%d\":name;\n", i, i+1);
        i++;
    }

    fprintf(Dump_f, "}");
    fclose(Dump_f);

    system ("dot -Tpng Dump.txt -o Dump.png");
    system("Dump.png");
}

size_t List::Find_most_freq() {
    if (!Ok()) {
        Dump();
        return 0;
    }

    Node *node = head_;
    if (node == nullptr) {
        return 0;
    }
    size_t max = node->Get_freq();

    while(node != nullptr) {
        if (max < node->Get_freq()) {
            max = node->Get_freq();
            head_ = node;
        }
        node = node->next_;
    }

    if (!Ok()) {
        Dump();
        return 0;
    }

    return max;
}