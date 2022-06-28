#ifndef ALGORITHMS_HASHTABLE_HH_
#define ALGORITHMS_HASHTABLE_HH_

#include <string>

namespace algorithms {

class KeyError : public std::exception {
  public:
    KeyError(std::string);
    KeyError(const KeyError &);
    ~KeyError() noexcept;
    const char * what(void) const noexcept;

  private:
    std::string key_;
    std::string *message_;
};

/**
 * @brief Represents a Bucket in the Hash Table.
 * @note Implemented as a basic Doubly Linked List (DLL).
 *
 * @param previous A pointer to the bucket before in the DLL.
 * @param next A pointer to the bucket after in the DLL.
 * @param key A unique string id that represents an index in the Hash Table.
 * @param value The value to store in the Hash Table.
 */
struct Bucket {
    struct Bucket *previous;
    struct Bucket *next;
    std::string key;
    void *value;
};

/**
 * @brief Represents a Hash Table.
 * @note This implementation resolves Hash Collisions by Chaining.
 */
class HashTable {
  public:
    /**
     * @brief Constructor for `HashTable` objects.
     *
     * @param _capacity The maximum number of buckets the Hash Table can store.
     */
    HashTable(unsigned int = 11U);

    /**
     * @brief Copy constructor for `HashTable` objects.
     *
     * @param _exist
     */
    HashTable(const HashTable &);

    /**
     * @brief Destructor for `HashTable` objects.
     */
    ~HashTable() noexcept;

    /**
     * @brief Inserts a value into a bucket in the Hash Table.
     *
     * @param _key A string id that represents an index in the Hash Table.
     * @param _value A C-style void pointer to store the value.
     *
     * @note The argument for `_value` must be type-casted to a void pointer.
     *
     * @return void
     */
    void Insert(std::string, void *);

    /**
     * @brief Gets a value from a bucket in the Hash Table.
     *
     * @param _key A string id that represents an index in the Hash Table.
     *
     * @exception KeyError The `_key` does not exist in the Hash Table.
     *
     * @return std::string
     */
    void * Search(std::string);

    /**
     * @brief Removes a value from a bucket in the Hash Table.
     *
     * @param _key A string id that represents an index in the Hash Table.
     *
     * @exception KeyError The `_key` does not exist in the Hash Table.
     *
     * @return void
     */
    void Delete(std::string);

    /**
     * @brief Represents the maximum count of buckets the Hash Table can hold.
     *
     * @return const unsigned int
     */
    const unsigned int capacity(void) const { return this->capacity_; }

    /**
     * @brief Represents the number of buckets currently in the Hash Table.
     *
     * @return const unsigned int
     */
    const unsigned int count(void) const { return this->count_; }

    /**
     * @brief Gets a backend Bucket structure from the Hash Table. Included
     * for client-side implementations of various function (e.g., PrintTable).
     *
     * @see ./examples/e_hashtable.cc
     *
     * @param _index An integer value between 0 and `HashTable->capacity()`.
     *
     * @return const struct Bucket*
     */
    const struct Bucket * bucket(int _index) const { return this->table_[_index]; }

  protected:
    /**
     * @brief Copies over the existing buckets to a new `HashTable` object
     * with a greater capacity. The capacity of the new Hash Table is the next
     * prime number greater than 2x the capacity of the existing table.
     *
     * @return void
     */
    HashTable * ExpandTable(void);

  private:
    unsigned int capacity_;
    unsigned int count_;
    // Stores all of the key/value pairs of the Hash Table.
    struct Bucket **table_;

    /**
     * @brief Calculates an index to use when storing buckets.
     *
     * @param key A string id that represents an index in the Hash Table.
     *
     * @return unsigned int
     */
    unsigned int Hash(std::string);
};

}  // namespace algorithms

#endif  // !ALGORITHMS_HASHTABLE_HH_
