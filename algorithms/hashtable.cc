#include "hashtable.hh"

#include <string>
#include <iostream>

namespace algorithms {

KeyError::KeyError(std::string _key) {
    this->key_ = _key;
    this->message_ = new std::string(
        "Key '" + this->key_ + "' does not exist in the Hash Table."
    );

    return;
}

KeyError::KeyError(const KeyError &exist) {
    this->key_ = exist.key_;
    this->message_ = exist.message_;

    return;
}

KeyError::~KeyError() noexcept {
    delete this->message_;

    return;
};

const char * KeyError::what(void) const noexcept {
    return this->message_->c_str();
}


static bool IsPrime(int _value) {
    if ((_value == 0) || (_value == 1)) {
        return false;
    }

    for (int i = 2; i < (_value / 2); i++) {
        if ((_value % i) == 0) {
            return false;
        }
    }

    return true;
}

static int GetPrime(int _value) {
    if ((_value % 2) == 0) {
        _value++;
    }

    while (IsPrime(_value) != true) {
        _value += 2;
    }

    return _value;
}

static struct Bucket * CreateBucket(
    struct Bucket *_previous,
    struct Bucket *_next,
    std::string _key,
    void *_value
) {
    struct Bucket *bucket = new struct Bucket();
    bucket->previous = _previous;
    bucket->next = _next;
    bucket->key = _key;
    bucket->value = _value;

    return bucket;
}


HashTable::HashTable(unsigned int _capacity) {
    this->capacity_ = GetPrime(_capacity);
    this->count_ = 0U;
    this->table_ = new struct Bucket *[this->capacity_];

    for (int index = 0; index < this->capacity_; index++) {
        this->table_[index] = nullptr;
    }

    return;
}

HashTable::HashTable(const HashTable &exist) {
    this->capacity_ = exist.capacity_;
    this->count_ = exist.count_;

    for (int index = 0; index < exist.capacity_; index++) {
        this->table_[index] = exist.table_[index];
    }
}

HashTable::~HashTable() noexcept {
    delete[] this->table_;

    return;
}

void HashTable::Insert(std::string _key, void *_value) {
    unsigned int index = this->Hash(_key);
    struct Bucket **bucket = &(this->table_[index]);
    struct Bucket *new_bucket;

    if (*bucket == nullptr) {
        new_bucket = CreateBucket(new_bucket, nullptr, _key, _value);

        *bucket = new_bucket;
        this->count_++;
    }
    else if ((*bucket)->key == _key) {
        (*bucket)->value = _value;
    }
    else {
        while ((*bucket)->next != nullptr) {
            if ((*bucket)->next->key == _key) {
                (*bucket)->next->value = _value;
                break;
            }

            *bucket = (*bucket)->next;
        }

        if ((*bucket)->next == nullptr) {
            new_bucket = CreateBucket(new_bucket, nullptr, _key, _value);
            (*bucket)->next = new_bucket;
            this->count_++;
        }
    }

    if (this->count_ >= (this->capacity_ * (0.75))) {
        *this = *this->ExpandTable();
    }

    return;
}

void * HashTable::Search(std::string _key) {
    unsigned int index = this->Hash(_key);
    struct Bucket **bucket = &(this->table_[index]);

    while (*bucket != nullptr) {
        if ((*bucket)->key == _key) {
            return (*bucket)->value;
        }

        *bucket = (*bucket)->next;
    }

    throw KeyError(_key);
}

void HashTable::Delete(std::string _key) {
    unsigned int index = this->Hash(_key);
    struct Bucket **bucket = &(this->table_[index]);
    struct Bucket **to_delete;

    if (*bucket == nullptr) {
        throw KeyError(_key);
    }
    else if ((*bucket)->key == _key) {
        to_delete = bucket;

        if ((*bucket)->next != nullptr) {
            *bucket = (*bucket)->next;
        }
        else {
            *bucket = nullptr;
        }
    }
    else {
        while (*bucket != nullptr) {
            if ((*bucket)->next->key == _key) {
                to_delete = &(*bucket)->next;
                (*bucket)->next = (*bucket)->next->next;
                break;
            }

            bucket = &(*bucket)->next;
        }
    }

    delete *to_delete;

    return;
}

HashTable * HashTable::ExpandTable(void) {
    HashTable *expanded = new HashTable(this->capacity_ * 2U);
    struct Bucket **bucket;

    for (int index = 0; index < this->capacity_; index++) {
        *bucket = this->table_[index];
        while (*bucket != nullptr) {
            expanded->Insert((*bucket)->key, (*bucket)->value);
            *bucket = (*bucket)->next;
        }
    }

    return expanded;
}

unsigned int HashTable::Hash(std::string _key) {
    unsigned int hash_value = 0U;

    for (const unsigned char *ukey = (const unsigned char *)_key.c_str(); *ukey; ukey++) {
        hash_value = (((hash_value * 3) + *ukey) % this->capacity_);
    }

    return hash_value;
}

}  // namespace algorithms
