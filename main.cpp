#include <iostream>
#include <cstring>
#include "cmake-build-debug/list.h"

//std::string
//templates
//Destructors!

class Hashtable {
public:
    Hashtable();
    explicit Hashtable(size_t (*func) (const char *));
    ~Hashtable();
    void Find_and_Paste(const char *word);
    Node * Find_elem(const char *word);
    void Print_Stat(FILE *out);
    void Print_Top(FILE *out);

private:
    List *arr_;                        //array with List pointers
    size_t (*hash_count_) (const char *);
};

Hashtable::Hashtable():
    arr_(new List [max_alen]),
    hash_count_(nullptr) {}

Hashtable::Hashtable(size_t (*func) (const char *)):
    arr_(new List [max_alen]),
    hash_count_(func) {}

Hashtable::~Hashtable() {
    delete(arr_);
    arr_ = nullptr;
    hash_count_ = nullptr;
}

void Hashtable::Find_and_Paste(const char *word) {
    Node *elem = Find_elem(word);
    if (!elem) {
        size_t index = hash_count_(word);
        index %= max_alen;
        (arr_[index]).Add_Last(word);
    }
    else {
        elem->inc_freq();
    }
}

Node * Hashtable::Find_elem(const char *word) {
    size_t h = hash_count_(word);
    h %= max_alen;

    return arr_[h].Find_elem(word);
}

void Hashtable::Print_Stat(FILE *out) {
    for (int i = 0; i < max_alen; i++) {
        fprintf(out, "%d, %d\n", i, (int) arr_[i].Get_len());
    }
}

void Hashtable::Print_Top(FILE *out) {
    qsort(arr_, max_alen, sizeof(List), Comparate);

    for (int i = 0; i < max_alen; i++) {
        const char *word;
        if (arr_[i].Get_head() != nullptr) {
            word = arr_[i].Get_head()->Get_data();
        }
        else {
            word = "Kotik";
        }
        fprintf(out, "%d. %s\n", i, word);
    }
}

int Comparate(const void *l1, const void *l2) {
    List *L1 = (List *) l1;
    List *L2 = (List *) l2;

    return (int) -(L1->Find_most_freq() - L2->Find_most_freq());
}

size_t H0 (const char *word);
size_t H1 (const char *word);
size_t H2 (const char *word);
size_t H3 (const char *word);
size_t H4 (const char *word);
size_t H5 (const char *word);

int main() {
    FILE *in = fopen("Norm.txt", "r");

    auto *word = new char[max_wlen];
    auto *Dict = new Hashtable(H4);

    while(fscanf(in, "%s", word) != EOF) {          //fill Dict with words
        Dict->Find_and_Paste(word);
    }
    fclose(in);

    FILE *out = fopen("TestTable.csv", "a");
    Dict->Print_Stat(out);
    fclose(out);

    std::cout << "I'm fine" << std::endl;

    FILE *top = fopen("TestTop.txt", "w");
    Dict->Print_Top(top);
    fclose(top);

    delete word;

    return 0;
}

//hash functions
size_t H0 (const char *word) {
    if (word == nullptr) {
        return POISON;
    }

    return 1;
}

size_t H1 (const char *word) {
    if (word == nullptr) {
        return POISON;
    }

    return (size_t) word[0];
}

size_t H2 (const char *word) {
    if (word == nullptr) {
        return POISON;
    }

    return strlen(word);
}

size_t H3 (const char *word) {
    if (word == nullptr) {
        return POISON;
    }

    size_t sum = word[0];

    for (int i = 1; word[i] != 0; i++) {
        sum += word[i];
    }

    return sum;
}

size_t H4 (const char *word) {
    if (word == nullptr) {
        return POISON;
    }

    size_t gnu_hash = word[0];

    for (int i = 1; word[i] != 0; i++) {
        gnu_hash = gnu_hash*33 + word[i];
    }

    return gnu_hash;
}

size_t H5 (const char *word) {
    if (word == nullptr) {
        return POISON;
    }

    size_t h = 0;
    size_t h_c = h;

    for (int i = 0; word[i] != 0; i++) {
        h = h << 1 + ((h_c & two) >> 31);
        h = h ^ (word[i]);
        h_c = h;
    }

    return h;
}