#include <iostream>

#include "hashtable.hh"

using namespace algorithms;

/**
 * @brief Prints the contents of the table to Standard Output (stdout).
 *
 * @param table Pointer/Reference to a algorithms::HashTable object.
 *
 * @return void
 */
static void PrintTable(const HashTable &_table) {
    for (int index = 0; index < _table.capacity(); index++) {
        std::cout << index << " ---> ";
        for (
          struct Bucket *bucket = _table.bucket(index);
          bucket != nullptr;
          bucket = bucket->next
        ) {
            std::cout << bucket->key;
            while (bucket->next != nullptr) {
                std::cout << " ---> " << bucket->next->key;
                bucket = bucket->next;
            }
        }
        std::cout << std::endl;
    }

    return;
}

int main(int argc, const char **argv) {
    // Constructing a new HashTable object.
    HashTable headers = HashTable();

    // Inserting values into the Hash Table.
    headers.Insert("authorization", (void *) "access_token");
    headers.Insert("content-type", (void *) "application/json");
    headers.Insert("user-agent", (void *) "Bot (mycpplib, 1.0.0)");
    headers.Insert("content", (void *) "Hello, World!");
    headers.Insert("color", (void *) "0x323232");
    headers.Insert("first_name", (void *) "Nicolas");
    headers.Insert("surname", (void *) "Gonzalez");
    headers.Insert("hw", (void *) "Hello, World! (again)");
    headers.Insert("player_score", (void *) 170);
    headers.Insert("lives_left", (void *) 2);
    headers.Insert("id", (void *) 1);
    headers.Insert("is_winning", (void *) true);

    // Searching the Hash Table for a specific key.
    std::cout << (
        (bool) headers.Search("is_winning") == true
          ? "I am winning!"
          : "I am losing..."
    ) << std::endl;

    // Updating a value in the Hash Table.
    headers.Insert("is_winning", (void *) false);

    // Checking the updated value.
    std::cout << (
        (bool) headers.Search("is_winning") == true
          ? "I am winning!"
          : "I am losing..."
    ) << std::endl;

    // Deleting an Element from the Hash Table.
    std::cout << (char *) headers.Search("content") << std::endl;
    headers.Delete("content");

    const char *content;
    try {
        content = (const char *) headers.Search("content");
    }
    catch (const KeyError &error) {
        std::cout << error.what() << std::endl;
    }

    // Printing all the keys from the Hash Table.
    PrintTable(headers);

    // Printing information about the Hash Table.
    std::cout << "Elements in 'headers': " << headers.count() << std::endl;
    std::cout << "Capacity of 'headers': " << headers.capacity() << std::endl;

    return 0;
}
